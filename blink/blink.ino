// smoke test; just blinks onboard red led &
// writes "blink" to serial port

// tested with 
//  Adafruit HUZZAH ESP8266  (pin=0)
//  Adafruit Feather 32u4    (pin=13)

int PIN = 13;  // 32u4
//int PIN = 13;  // Huzzah

void setup() {
  Serial.begin(115200);
  pinMode(PIN, OUTPUT);
}

void loop() {
  digitalWrite(PIN, HIGH);
  delay(800);
  digitalWrite(PIN, LOW);
  delay(200);
  Serial.println("blink!");
}
