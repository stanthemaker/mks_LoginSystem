#include <SPI.h>
#include <MFRC522.h>
#include "button.h"
#define RST_PIN         49
#define SS_PIN          53

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
    Serial.begin(9600);     // Initialize serial communications with the PC
    while (!Serial);        // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
    SPI.begin();            // Init SPI bus
    mfrc522.PCD_Init();     // Init MFRC522
    setPins();
    //pinMode(31, OUTPUT);
    pinMode(13, OUTPUT);
//    Serial.println("Start code");
}
void loop() {
  update();
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
      return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
      return;
  }

  tone(13, 2093, 100);
  String uid;
  for (int i = 0; i < 4; ++i) {
    String s = String(mfrc522.uid.uidByte[i], HEX);
    if (s.length() == 1)
      s = "0" + s;
    if (s.length() == 0)
      s = "00";
    uid += s;
  }
  mfrc522.PICC_HaltA();                         // 讓卡片進入停止模式
  mfrc522.PCD_StopCrypto1();
  bool purpose_list[12] = {false};
  String purpose;
  for (int i = 0; i < 12; ++i) {
    if (ledLightup[i]) { //lightup means the purpose has been selected
        purpose += ( " " + String(i)); 
    }
  }
//  byte result = 0; 
//  for(int i=0; i<12; i++){ //converting bool arraoy to bytes form
//    if(ledLightup[i]){
//       result |= (1 << i)
//    }
//  } 
  reset();
  Serial.println(uid + purpose);
  delay(1500);

}
