void RFIDSetup() {
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Hold your card to the reader...");
  Serial.println();
}

void RFIDLoop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  //Serial.print("Message : ");
  //content.toUpperCase();

  if (ttime - lastTtimeOpen >= openInterval) {
    bool run = false;
    lastTtimeOpen = ttime;

    if (doorOpen == false && run == false) {
      run = true;
      if ((content.substring(1) == SecureID)||(content.substring(1) == MasterID))  //change UID('s) of the card/cards that you want to give access
      {
        Serial.println("Authorized access");
        doorOpen = true;
        state = 4;
        oled();
        Serial.println();
      }
      else   {
        Serial.println("Access denied");
        doorOpen = false;
        state = 5;
        oled();
        Serial.println();
      }
    }
    else if (doorOpen == true && run == false) {
      run = true;
      SecureID = content.substring(1);
      Serial.println("New Card has been secured");
      doorOpen = false;
      state = 6;
      oled();
    }
  }
}
