/////// OPSÆTNING AF WIFI-FORBINDELSE  ///////////




// Opretter forbindelse til WiFi
void setup_wifi() {
  // Forbinder til et WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// Opretter forbindelse til mqtt server. Dette gentages ved manglende forbindelse til WiFi, server osv.
void reconnect() {
  // Fortsætter til forbindelsen er oprettet
  while (!client.connected()) {
    Serial.print("Forsøger at oprette MQTT forbindelse...");

    if (client.connect("UNIQUE_CLIENT_NAME", mqtt_user, mqtt_pass)) { // Forbinder til klient med mqtt bruger og password
      Serial.println("connected");
      // Derudover subsribes til topic "LOCK" hvor NodeMCU modtager payload beskeder fra
      client.subscribe("LOCK");
      // Der kan subscribes til flere specifikke topics
      //client.subscribe("LED1");
      // Eller til samtlige topics ved at bruge '#' (Se Power Point fra d. 18. marts)
      // client.subscribe("#");

      // Hvis forbindelsen fejler køres loopet igen efter 5 sekunder indtil forbindelse er oprettet
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Venter 5 sekunder før den prøver igen
      delay(5000);
    }
  }
}




///////// OPSÆTNING AF WIFI SLUT /////////
