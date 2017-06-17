// feather huzzah test for two DHT11 temp & humidity sensors.
// sends data via UDP to a server.
// see http://osoyoo.com/2015/03/21/dht11-temperature-and-humidity-sensor/
// note: command requires a 10K pullup resistor for VCC
// optionally include a TMP36 for sanity

#include <dht.h>
dht DHT;

int DHT_PINS[] = { 0, 2 };

void setup() {
  Serial.begin(115200);
  Serial.println();
}

void loop() {

  for (int i=0; i<2; ++i) {
    Serial.print("DHT11: pin ");
    Serial.print(DHT_PINS[i]);

    DHT.read11(DHT_PINS[i]);

    Serial.print(" humidty ");
    Serial.print(DHT.humidity);  // double
    Serial.print("%");

    Serial.print(" temp ");
    Serial.print(DHT.temperature);  // double
    Serial.println('C');
  }

  // optional TMP36 check also...
  int raw_reading = analogRead(0);
  float voltage = (float)raw_reading / 1024;
  float temp = (voltage - 0.5) * 100 ;
  Serial.print("TMP36: temp ");
  Serial.println(temp);

  // sleep
  delay(3000);
}
