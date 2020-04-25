const int buttonPin = D8;     // the number of the pushbutton pin
unsigned long LastButtonInfo;
const long ButtonInfoInterval = 5000;
// variables will change:


void ButtonSetup() {
  pinMode(buttonPin, INPUT);
}

void ButtonLoop() {
  buttonState = digitalRead(buttonPin);
  if (ttime - LastButtonInfo >= ButtonInfoInterval) {
    LastButtonInfo = ttime;
    if (buttonState == 1) {
      client.publish("FromMCU", "DoorClosed"); //Sender en besked til NODERED om at døren er lukket
    }
    else {
      client.publish("FromMCU", "DoorOpened"); //Sender en besked til NODERED om at døren er åben
    }
    //Serial.print("Buttonstate = ");Serial.println(buttonState);
  }
}

void LockoutSecurity() {
  //Da låsen altid er låst når den ikke har strøm, skal man sørge for
  //at man ikke bliver låst ude hvis man lukker den før man har brugt RFID eller Nodered.
  //Hvis døren er lukket men ikke er låst så åbner døren igen.
  if (doorOpen == true && buttonState == 1) {
    OpenDoor();
  }
}
