#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN        D4
#define RST_PIN       D3
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

#define btn_PIN     D8

// -- LED setup -------
int red_light_pin   = D0;
int green_light_pin = D1;
int blue_light_pin  = D2;

//-- RFID Values ------
String SecureID;
String MasterID = "D9 DF 57 C1";
bool NewCard = false;

void setup() {
  Serial.begin(9600);
  RGBSetup();
  RFIDSetup();
  BUTTONSetup();
}

void loop() {
  RFIDLoop();
  NewCardChanger();
}
