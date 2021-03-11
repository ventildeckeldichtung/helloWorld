#include <SPI.h>
#include <MFRC522.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#define serial1  7
#define serial2  8
#define SS_PIN 10
#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.
SoftwareSerial mySoftwareSerial(serial1, serial2); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void setup() {
  Serial.begin(9600); // Initialize serial communications with the PC
  mySoftwareSerial.begin(9600);
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  Serial.println("Scan PICC to see UID and type...");
  pinMode(serial1, INPUT);
  pinMode(serial2, OUTPUT);
  Serial.println(F("Initializing DFPlayer ..."));
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
  }
  else
  {
    Serial.println(F("DFPlayer Mini online."));
  }

  myDFPlayer.volume(10);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3
}
long old_code = 0;
void loop() {
  //read the current card
  long code=0;
  if(mfrc522.PICC_IsNewCardPresent()&& mfrc522.PICC_ReadCardSerial()){
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
      code=((code+mfrc522.uid.uidByte[i])*10); 
    }
    //only update the old code if a difrent card was read,
    if(code != old_code){  
      old_code = code; 
      Serial.print("Die Kartennummer lautet:");
      Serial.println(old_code);
     }

  }

}
