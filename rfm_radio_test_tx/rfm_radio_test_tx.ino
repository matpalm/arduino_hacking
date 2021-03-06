// rfm69hcw feather 32u4 radio test
// transmission RX
// forked from radio head examples

#include <SPI.h>
#include <RH_RF69.h>

#define RF69_FREQ 915.0

#define RFM69_CS      8
#define RFM69_INT     7
#define RFM69_RST     4
#define LED           13

RH_RF69 rf69(RFM69_CS, RFM69_INT);

uint8_t node = 14;
uint16_t sequence_number = 0; 

void setup() 
{
  Serial.begin(115200);
  //while (!Serial) { delay(1); } // wait until serial console is open, remove if not tethered to computer

  pinMode(LED, OUTPUT);     
  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, LOW);

  Serial.println("Feather RFM69 TX Test!");
  Serial.println();

  // manual reset
  digitalWrite(RFM69_RST, HIGH);
  delay(10);
  digitalWrite(RFM69_RST, LOW);
  delay(10);
  
  if (!rf69.init()) {
    Serial.println("RFM69 radio init failed");
    while (1);
  }
  Serial.println("RFM69 radio init OK!");
  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM (for low power module)
  // No encryption
  if (!rf69.setFrequency(RF69_FREQ)) {
    Serial.println("setFrequency failed");
  }

  // If you are using a high power RF69 eg RFM69HW, you *must* set a Tx power with the
  // ishighpowermodule flag set like this:
  rf69.setTxPower(20, true);  // range from 14-20 for power, 2nd arg must be true for 69HCW

  // The encryption key has to be the same as the one in the server
  uint8_t key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  rf69.setEncryptionKey(key);
  
  pinMode(LED, OUTPUT);

  Serial.print("RFM69 radio @");  Serial.print((int)RF69_FREQ);  Serial.println(" MHz");
}

struct packet {
  uint8_t node;
  uint16_t sequence_number;
  float sequence_number_as_float;
};

void loop() {
  delay(500);  // Wait 1 second between transmits, could also 'sleep' here!

  packet p;
  p.node = node;
  p.sequence_number = sequence_number;
  p.sequence_number_as_float = (float)sequence_number / 3;
  
  uint8_t buf[sizeof(packet)];
  memcpy(&buf, &p, sizeof(packet));
  
  Serial.print("Sending ");
  Serial.print(sequence_number);
  Serial.print(" ");
  Serial.print(p.sequence_number_as_float);
  Serial.println();
  
  rf69.send(buf, 7);
  rf69.waitPacketSent();

  sequence_number++;
  
  //Blink(LED, 50, 3); //blink LED 3 times, 50ms between blinks
}

void Blink(byte PIN, byte DELAY_MS, byte loops) {
  for (byte i=0; i<loops; i++)  {
    digitalWrite(PIN,HIGH);
    delay(DELAY_MS);
    digitalWrite(PIN,LOW);
    delay(DELAY_MS);
  }
}
