//////////// START WEATHER ////////////

void weather() {
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    HTTPClient http; //Declare an object of class HTTPClient

    // REMEMBER to replace YOURKEY from the url with your own key
    http.begin("http://api.openweathermap.org/data/2.5/forecast?q=Copenhagen,dk&appid=45b767ff1c19b98f03f1be2a6a9f1c88&units=metric&cnt=3"); //Specify request destination
    int httpCode = http.GET(); //Send the request

    if (httpCode > 0) { //Check the returning code

      String payload = http.getString(); //Get the request response payload - the json object as a plain text

      //define a json object buffer
      DynamicJsonDocument jsonBuffer(2048);

      //try convert the plain text to an arduino - json object
      DeserializationError success = deserializeJson(jsonBuffer, payload);

      // if conversion not successful:
      // NOTE: there are two cases this can fail: if the json object is too big for the arduino
      // OR the communication protocol to the api is secure: e.g. 'https' instead of 'http'
      // There are solutions to both, but not relevant for this exercise..

      if (!success) {
        Serial.println("deserialization failed");
        return;
      }

      //if it is successful, let's grab a data fragment and show it on the serial terminal:

      // the first forecast in the json object is at jsonBuffer['list'][0]
      String ts1 = jsonBuffer["list"][0]["dt_txt"];
      timestamp1 = ts1;
      Serial.print("The time for this forecast: ");
      Serial.println(timestamp1);

      // The 'weather' in the first position in the list, is actually a list, with only one element...
      String d1 = jsonBuffer["list"][0]["weather"][0]["description"];
      desc1 = d1;
      Serial.print("The weather will be: ");
      Serial.println(desc1);

      // Temperature
      float tp1 = jsonBuffer["list"][0]["main"]["temp"];
      temp1 = tp1;
      Serial.print("The temperature will be: ");
      Serial.print(temp1);
      Serial.println(" C");



      // the first forecast in the json object is at jsonBuffer['list'][0]
      String ts2 = jsonBuffer["list"][1]["dt_txt"];
      timestamp2 = ts2;
      Serial.print("The time for this forecast: ");
      Serial.println(timestamp2);

      // The 'weather' in the first position in the list, is actually a list, with only one element...
      String d2 = jsonBuffer["list"][1]["weather"][0]["description"];
      desc2 = d2;
      Serial.print("The weather will be: ");
      Serial.println(desc2);

      // Temperature
      float tp2 = jsonBuffer["list"][1]["main"]["temp"];
      temp2 = tp2;
      Serial.print("The temperature will be: ");
      Serial.print(temp2);
      Serial.println(" C");



      // the first forecast in the json object is at jsonBuffer['list'][0]
      String ts3 = jsonBuffer["list"][2]["dt_txt"];
      timestamp3 = ts3;
      Serial.print("The time for this forecast: ");
      Serial.println(timestamp3);

      // The 'weather' in the first position in the list, is actually a list, with only one element...
      String d3 = jsonBuffer["list"][2]["weather"][0]["description"];
      desc3 = d3;
      Serial.print("The weather will be: ");
      Serial.println(desc3);

      // Temperature
      float tp3 = jsonBuffer["list"][2]["main"]["temp"];
      temp3 = tp3;
      Serial.print("The temperature will be: ");
      Serial.print(temp3);
      Serial.println(" C");

    }
    http.end(); //Close connection
  }
}

void WeatherGetter() { //Updates the weather every 5 minutes
  if (ttime - lastWeatherGet >= weatherGetInterval) {
    lastWeatherGet = ttime;
    weather();
    Serial.println("Weather Gotten");
  }
}
