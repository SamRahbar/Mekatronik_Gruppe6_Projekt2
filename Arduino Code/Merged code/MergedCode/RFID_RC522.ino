unsigned long lastTtimeOpen = 0; //Last Time the door was opened
const long openInterval = 3000; //How long you have to wait to try to open the door

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
  content.toUpperCase(); //Makes the input uniform

  if (NodeRedInUse == false) {//Checks if NodeRed is in use
    if (ttime - lastTtimeOpen >= openInterval) { //Checks if it has been 3 seconds since last open attempt
      //bool run = false; //The rest hasn't been run yet
      lastTtimeOpen = ttime; //Sets last open attempt

      if (doorOpen == false) { //If the door is open
        if ((content.substring(1) == SecureID) || (content.substring(1) == MasterID)) //Checks if the RFID tag used is the secured one or the MasterID (could be the janitor)
        {
          Serial.println("Authorized access");
          client.publish("FromMCU", "RFIDOPEN"); //Tells NodeRed it has been opened with RFID
          state = 4; //Changes oled frame
          oled(); //updates OLED
          doorOpen = true; //Opens door since button is being pressed
          //OpenDoor();
        }
        else   {
          Serial.println("Access denied");
          doorOpen = false; //Door remains locked
          state = 5; //Oled state changes
          oled(); //Oled updates
        }
      }
      else if (doorOpen == true) { //If the door is open, a new card can be secured and used
        SecureID = content.substring(1); //The SecureID string is updated to match the newly scanned card
        Serial.println("Door locked with RFID");
        doorOpen = false; //Door will be locked
        prevOpenTimer = ttime; //Sets timer start for automatic door open
        state = 6; //Oled state changes
        oled(); // Oled updates
        client.publish("FromMCU", "RFIDLOCK"); //Tells NodeRed that the locker has been locked with RFID
        //Send MQTT message, (RFIDLOCK)
      }
    }
  }
}
void DoorTimerUnlock() { //If the door has been locked, it will only stay locked for 8 hours
  if ((ttime - prevOpenTimer >= openTimerInterval)&& doorOpen == false) { //if 8 hours have passed
    Serial.println("Opened because of timer");
    doorOpen = true; //Opens the door
    //OpenDoor();
    state = 7; //Changes oled frame
    oled(); //updates oled
    client.publish("FromMCU", "DOOROPENWTIMER"); //Tells nodered that it has been opened with timer
  }
}
