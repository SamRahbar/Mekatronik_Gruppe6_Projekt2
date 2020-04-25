const int buttonPin = D8;     // the number of the pushbutton pin
// variables will change:


void ButtonSetup() {
  pinMode(buttonPin, INPUT);
}

void ButtonLoop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == 1){
    client.publish("FromMCU","DoorClosed"); //Sender en besked til NODERED om at døren er lukket
  }
  //Serial.print("Buttonstate = ");Serial.println(buttonState);
}

void LockoutSecurity(){
  //Da låsen altid er låst når den ikke har strøm, skal man sørge for 
  //at man ikke bliver låst ude hvis man lukker den før man har brugt RFID eller Nodered.
  //Hvis døren er lukket men ikke er låst så åbner døren igen.
  if (buttonState == 1 && doorOpen){ 
    OpenDoor();
  }
}
