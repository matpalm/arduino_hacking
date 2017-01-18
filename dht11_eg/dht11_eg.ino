// feather huzzah test for two DHT11 temp & humidity sensors
// see http://osoyoo.com/2015/03/21/dht11-temperature-and-humidity-sensor/
// note: command requires a 10K pullup resistor for VCC

#include <dht.h>
dht DHT;

int PINS[] = { 0, 2 };

void setup() {
  Serial.begin(115200);
  Serial.println();
  // Serial.println(ESP.getResetReason());
}

void loop() {

  for (int i=0; i<2; ++i) {
    Serial.print("pin ");
    Serial.print(PINS[i]);

    DHT.read11(PINS[i]);

    Serial.print(" humidty ");
    Serial.print(DHT.humidity);  // double
    Serial.print("%");

    Serial.print(" temp ");
    Serial.print(DHT.temperature);  // double
    Serial.println('C');
  }

  // either deep sleep or delay
  ESP.deepSleep(5*1000000, WAKE_RF_DEFAULT); // 5s
  //delay(2000);
}
