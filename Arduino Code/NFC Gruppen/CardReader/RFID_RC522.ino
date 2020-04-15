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
  Serial.print("Message : ");
  content.toUpperCase();

  if (NewCard) {
    SecureID = content.substring(1);
    Serial.println("New Card has been secured");
    NewCard = false;
    analogWrite(blue_light_pin,0);
  }
  else {
    if (content.substring(1) == SecureID  ||  content.substring(1) == MasterID)  //change UID('s) of the card/cards that you want to give access
    {
      Serial.println("Authorized access");
      Serial.println();
      RGB_color(0, 80, 0); // LED Green
      delay(1500);
    }
    else   {
      Serial.println("Access denied");
      Serial.println();
      RGB_color(80, 0, 0); // LED Red
      delay(1500);
    }
    RGB_color(0, 0, 0);    // LED Off
  }
}
