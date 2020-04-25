const int LockPin = D0;
unsigned long doorOpened = 0;
const long doorOpenDur = 3000;

void LEDSetup(){
  pinMode(LockPin, OUTPUT);
}

//En metode der åbner døren
void OpenDoor(){
  Serial.println("Door is opened");
  digitalWrite(LockPin,HIGH);
  client.publish("FromMCU", "LOCKISOPEN");
  delay(doorOpenDur); //Et delay der sørger for at døren åbnes
  digitalWrite(LockPin,LOW);
  client.publish("FromMCU", "LOCKISCLOSED");
}
