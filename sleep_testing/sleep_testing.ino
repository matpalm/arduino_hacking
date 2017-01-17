void setup() {
  Serial.begin(115200);
  Serial.println();  
  Serial.println(ESP.getResetReason());
  Serial.println();
  delay(100);
  ESP.deepSleep(10*1000000, WAKE_RF_DEFAULT); // 10s
}

void loop() {
}

