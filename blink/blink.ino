// feather huzzah smoke test; just blinks onboard red led & 
// writes "blink" to serial port

void setup() {
  Serial.begin(115200);
  pinMode(0, OUTPUT);
}

void loop() {
  digitalWrite(0, HIGH);
  delay(200);
  digitalWrite(0, LOW);
  delay(200);
  Serial.println("blink!");
}
