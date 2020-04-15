const int buttonPin = btn_PIN;  
int buttonState = 0;  

void BUTTONSetup() {
  pinMode(buttonPin, INPUT);
}

void NewCardChanger() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    Serial.println("New card will be secured");
    state = 2;
    NewCard = true;
  }
}
