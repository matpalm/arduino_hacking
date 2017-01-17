// feather huzzah test for TMP36 temp sensor.

// note: tutes show that voltage calc requires / 3.3 but this isn't required for huzzah.

// TMP36 left pin   -> 3.3V
// TMP36 middle pin -> ADC 
// TMP36 right pin  -> GND

#define ADC 0

void setup() {
  Serial.begin(115200);
  // Serial.println(ESP.getResetReason());
}

void loop() {
  int raw_reading = analogRead(ADC);
  float voltage = (float)raw_reading / 1024;
  float temp = (voltage - 0.5) * 100 ;

  Serial.print("temp ");
  Serial.println(temp);

  // either deep sleep or delay for 1s
  //ESP.deepSleep(1*1000000, WAKE_RF_DEFAULT); // 1s
  delay(1000);
}
