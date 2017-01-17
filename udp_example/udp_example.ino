// ESP8266 listen for UDP packets and based on "command" switch some red/green/blue LEDS on/off

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid     = "ERROR";
const char* password = "PASSWORD";

WiFiClient client;
WiFiUDP port;
char buffer[255];
int i = 0;

const int INFO = 0;
const int R = 2;
const int G = 16;
const int B = 15;

void setup() {
  pinMode(INFO, OUTPUT);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT); 
  Serial.begin(115200);
  delay(100);
  Serial.println();

  // connect to wifi and blink INFO led until connected
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED) {
    // While waiting for wifi blink to show progress....
    delay(50);
    digitalWrite(INFO, HIGH);
    delay(50);
    digitalWrite(INFO, LOW);
  }
  Serial.print("Connected ");
  Serial.println(WiFi.localIP());

  // start listening
  port.begin(9999);

  // turn off all LEDs
  digitalWrite(INFO, LOW);
  digitalWrite(R, LOW);
  digitalWrite(G, LOW);
  digitalWrite(B, LOW);
}

void parsePacket() {
  int packetSize = port.parsePacket();
  if (packetSize==0) return;  

  int len = port.read(buffer, 255);
  if (len > 0) buffer[len] = 0;
  String cmd = String(buffer);
  
  if (cmd == "red") {
    digitalWrite(R, HIGH);
    digitalWrite(G, LOW);
    digitalWrite(B, LOW);
  } else if (cmd == "green") {
    digitalWrite(R, LOW);
    digitalWrite(G, HIGH);
    digitalWrite(B, LOW);
  } else if (cmd == "blue") {
    digitalWrite(R, LOW);
    digitalWrite(G, LOW);
    digitalWrite(B, HIGH);
  } else {
    Serial.print("UNKNOWN COMMAND [");
    Serial.print(cmd);
    Serial.println("]");    
  }
}

void loop() {
  parsePacket();
  delay(500);
}

