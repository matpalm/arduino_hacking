
// Check battery voltage on 32u4
// Tested with "Adafruit feather 32u4" radio module

#define VBATPIN A9

void setup() {
  Serial.begin(115200);
}

void loop() {
  float measuredvbat = analogRead(VBATPIN);
  measuredvbat *= 2;    // we divided by 2, so multiply back
  measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
  measuredvbat /= 1024; // convert to voltage
  Serial.print("VBat: " ); Serial.println(measuredvbat);
  delay(500);
}
