// Definerer callback funktionen der modtager beskeder fra mqtt
// OBS: den her funktion kører hver gang MCU'en modtager en besked via mqtt
void callback(char* byteArraytopic, byte* byteArrayPayload, unsigned int length) {

  // Konverterer indkomne besked (topic) til en string:
  String topic;
  topic = String(byteArraytopic);
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.println("] ");
  // Konverterer den indkomne besked (payload) fra en array til en string:
  // Topic == Temperaturmaaler, Topic == Kraftsensor
  if (topic == "ToMCU") { // OBS: der subscribes til et topic nede i reconnect-funktionen. I det her tilfælde er der subscribed til "LOCK". Man kan subscribe til alle topics ved at bruge "#"
    payload = ""; // Nulstil payload variablen så forloopet ikke appender til en allerede eksisterende payload
    for (int i = 0; i < length; i++) {
      payload += (char)byteArrayPayload[i];
      // For-loop: tag hvert tegn i hele længden af den inkomne besked, og konverter denne til en char. Append tegnene 1 efter 1:
      // Eksempel:
      // Besked = Study Abroad
      // Length = 12
      // Loop 1 = "S"
      // Loop 2 = "St" osv.
      // Loop (length) = "Study Abroad"
    }
    
    if (payload == "NodeRedSIGNUP") { // Hvis døren bliver låst med NodeRed ved MCU'en det
      NodeRedInUse = true; // NodeRed bliver brugt
      prevOpenTimer = ttime; //Sets timer start for automatic door open
      doorOpen == false; //Døren sættes til at være lukket
      state = 8; //Sætter OLED state til at være 8
    }
    if (payload == "NodeRedLOGIN") { // Hvis døren bliver åbnet med NodeRed ved MCU'en det
      NodeRedInUse = false; //NodeRedBliver ikke brugt længere
      doorOpen == true; // døren er åben og siden knappen er trykket ind, åbnes døren.
      //OpenDoor(); // Åbner døren
      state = 9; //Sætter OLED state til at være 9
    }
    else { // If the signal from the mqtt is not one of the available options, give a message to the mqtt server and pass
      Serial.println(payload);
      client.publish("Status", "Unknown message");
      delay(100);
    }

    oled(); // Display the chosen message on OLED-screen
  }
}

void MQTT_Setup() {
  client.setServer(mqtt_server, mqtt_port); // Forbinder til mqtt serveren (defineret længere oppe)
  client.setCallback(callback); // Ingangsætter den definerede callback funktion hver gang der er en ny besked på den subscribede "cmd"- topic
}

void MQTT_Loop() {
  // Hvis der opstår problemer med forbindelsen til mqtt broker oprettes forbindelse igen ved at køre client loop
  if (ttime - prevMillisConnect > 1000) {
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
    prevMillisConnect = ttime;
  }
}
