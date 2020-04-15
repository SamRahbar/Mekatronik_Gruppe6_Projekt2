//////////// HARDWARE ////////////
/*
  OLED
  VCC - 3V3
  GNG - GND
  SCL - D1
  SDA - D2

  RED LED
  D7 - 220 OHM - RED LED - GND

  GREEN LED
  D6 - 220 OHM - GREEN LED - GND
*/


//////////// Initiering ///////////

//inkluderer nødvendige bibloteker
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#include <Arduino.h>
#include <U8g2lib.h>

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


// Definerer id og password til netværksforbindelse som NodeMCU anvender
const char* ssid = "Ellens iPhone"; //Indsæt navnet på jeres netværk her
const char* password = "karamellen"; //Indsæt password her
//dlink-79BC-5GHz uygqk50992

// Definerer information til mqtt serveren
const char *mqtt_server = "hairdresser.cloudmqtt.com"; //navn på mqtt-server. Find navnet på cloudmqtt-hjemmesiden
const int mqtt_port = 15721; // Definerer porten
const char *mqtt_user = "Ellen1"; // Definerer mqtt-brugeren
const char *mqtt_pass = "gruppe6go"; // Definerer koden til mqtt-brugeren
//

String payload; // Definerer variablen 'payload' i det globale scope (payload er navnet på besked-variablen)

int ledPinRed = D7; // which is GPIO13. With nodemcu, you should directly use the pin names as they are stated on the board...
int ledPinGreen = D6;

int state;

// For OLED Screen
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

String line1;
String line2;

String timestamp1;
String timestamp2;
String timestamp3;

String desc1;
String desc2;
String desc3;

float temp1;
float temp2;
float temp3;

/////// INITIERING SLUT //////////

//
//
//
//
//
//

/////// FUNKTIONSOPSÆTNING ////////


// Opretter en placeholder for callback-funktionen til brug senere. Den rigtige funktion ses længere nede.
void callback(char* byteArraytopic, byte* byteArrayPayload, unsigned int length);

// Opretter en klient der kan forbinde til en specifik internet IP adresse.
WiFiClient espClient; // Initialiserer wifi bibloteket ESP8266Wifi, som er inkluderet under "nødvendige bibloteker"

// Opretter forbindelse til mqtt klienten:
PubSubClient client(mqtt_server, mqtt_port, callback, espClient); // Initialiserer bibloteket for at kunne modtage og sende beskeder til mqtt. Den henter fra definerede mqtt server og port. Den henter fra topic og beskeden payload

/////// FUNKTIONSOPSÆTNING SLUT /////////

//
//
//
//
//
//

///////// CALLBACKFUNKTION ////////

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
  if (topic == "LOCK") { // OBS: der subscribes til et topic nede i reconnect-funktionen. I det her tilfælde er der subscribed til "LOCK". Man kan subscribe til alle topics ved at bruge "#"
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


    if (payload == "WEATHER1") {
      state = 1;
    }
    if (payload == "WEATHER2") {
      state = 2;
    }
    if (payload == "WEATHER3") {
      state = 3;
    }
    if (payload == "OPEN") {
      state = 4;
    }
    if (payload == "CLOSED") {
      state = 5;
    }



    /// SWITCH ////



    switch (state) {
      case 1: // Show weather forecast 3 hours ahead and save information about 6-hour and 9-hour forecast

        //////////// START WEATHER ////////////

        //void weather(line1, line2);
        if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

          HTTPClient http; //Declare an object of class HTTPClient

          // REMEMBER to replace YOURKEY from the url with your own key
          http.begin("http://api.openweathermap.org/data/2.5/forecast?q=Copenhagen,dk&appid=c77892d924f8c1a8d686cbbdfa6db28d&units=metric&cnt=3"); //Specify request destination
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
            String timestamp1 = jsonBuffer["list"][0]["dt_txt"];
            Serial.print("The time for this forecast: ");
            Serial.println(timestamp1);

            // The 'weather' in the first position in the list, is actually a list, with only one element...
            String desc1 = jsonBuffer["list"][0]["weather"][0]["description"];
            Serial.print("The weather will be: ");
            Serial.println(desc1);

            // Temperature
            float temp1 = jsonBuffer["list"][0]["main"]["temp"];
            Serial.print("The temperature will be: ");
            Serial.print(temp1);
            Serial.println(" C");



            // the first forecast in the json object is at jsonBuffer['list'][0]
            String timestamp2 = jsonBuffer["list"][1]["dt_txt"];
            Serial.print("The time for this forecast: ");
            Serial.println(timestamp2);

            // The 'weather' in the first position in the list, is actually a list, with only one element...
            String desc2 = jsonBuffer["list"][1]["weather"][0]["description"];
            Serial.print("The weather will be: ");
            Serial.println(desc2);

            // Temperature
            float temp2 = jsonBuffer["list"][1]["main"]["temp"];
            Serial.print("The temperature will be: ");
            Serial.print(temp2);
            Serial.println(" C");



            // the first forecast in the json object is at jsonBuffer['list'][0]
            String timestamp3 = jsonBuffer["list"][2]["dt_txt"];
            Serial.print("The time for this forecast: ");
            Serial.println(timestamp3);

            // The 'weather' in the first position in the list, is actually a list, with only one element...
            String desc3 = jsonBuffer["list"][2]["weather"][0]["description"];
            Serial.print("The weather will be: ");
            Serial.println(desc3);

            // Temperature
            float temp3 = jsonBuffer["list"][2]["main"]["temp"];
            Serial.print("The temperature will be: ");
            Serial.print(temp3);
            Serial.println(" C");

            // Print three forecasts on OLED-screen. Loop every 3 seconds. After 5 minutes, check webiste again and collect fresh data
            //unsigned long starttime = 0;
            //starttime = millis();

            //while (millis() - starttime < 5 * 60 * 1000) {

            u8g2.clearBuffer();          // clear the internal memory
            u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
            u8g2.setCursor(0, 10);
            u8g2.print(timestamp1);
            u8g2.setCursor(0, 20);
            u8g2.print(desc1);
            u8g2.setCursor(0, 30);
            u8g2.print(String(temp1));
            u8g2.setCursor(30, 30);
            u8g2.print("C");
            u8g2.sendBuffer();          // transfer internal memory to the display
            delay(100);
            // }
          }
          http.end(); //Close connection
        }

        break;

      case 2: // Show weather forecast 6 hours ahead
        u8g2.clearBuffer();          // clear the internal memory
        u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
        u8g2.setCursor(0, 10);
        u8g2.print(timestamp2);
        u8g2.setCursor(0, 20);
        u8g2.print(desc2);
        u8g2.setCursor(0, 30);
        u8g2.print(String(temp2));
        u8g2.setCursor(30, 30);
        u8g2.print("C");
        u8g2.sendBuffer();          // transfer internal memory to the display
        delay(100);

        break;

      case 3: // Show weather forecast 9 hours ahead
        u8g2.clearBuffer();          // clear the internal memory
        u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
        u8g2.setCursor(0, 10);
        u8g2.print(timestamp3);
        u8g2.setCursor(0, 20);
        u8g2.print(desc3);
        u8g2.setCursor(0, 30);
        u8g2.print(String(temp3));
        u8g2.setCursor(30, 30);
        u8g2.print("C");
        u8g2.sendBuffer();          // transfer internal memory to the display
        delay(100);

        break;

      ////////// WETATHER SLUT //////////


      case 4:

        digitalWrite(2, HIGH);
        digitalWrite(ledPinGreen, HIGH);
        digitalWrite(ledPinRed, LOW);
        delay(100);
        client.publish("Status", "Green");

        u8g2.clearBuffer();          // clear the internal memory
        u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
        u8g2.setCursor(0, 10);
        u8g2.print("Something interesting");
        u8g2.setCursor(0, 20);
        u8g2.print("to write on the OLED...");
        u8g2.sendBuffer();          // transfer internal memory to the display
        delay(100);

        break;

      case 5:

        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinRed, HIGH);
        delay(100);
        client.publish("Status", "Red");

        oled();

        break;


    }
  }

  //// SWITCH ////


  else { // If the signal from the mqtt is not one of the available options, give a message to the mqtt server and pass
    Serial.println(payload);
    client.publish("Status", "Unknown message");
    delay(100);
  }

}


///////// CALLBACK SLUT /////////

//
//
//
//
//
//


///////// SETUP ///////////
void setup() {

  Serial.begin(115200); // Åbner serial porten og sætter data raten til 115200 baud
  delay(1000);

  // LEDs
  pinMode(ledPinGreen, OUTPUT);
  digitalWrite(ledPinGreen, LOW);
  pinMode(ledPinRed, OUTPUT);
  digitalWrite(ledPinRed, LOW);

  setup_wifi(); // Kører WiFi loopet og forbinder herved.
  client.setServer(mqtt_server, mqtt_port); // Forbinder til mqtt serveren (defineret længere oppe)
  client.setCallback(callback); // Ingangsætter den definerede callback funktion hver gang der er en ny besked på den subscribede "cmd"- topic
  u8g2.begin();

}
//////// SETUP SLUT ////////

//
//
//
//
//
//

/////// LOOP /////////

void loop() {

  // Hvis der opstår problemer med forbindelsen til mqtt broker oprettes forbindelse igen ved at køre client loop
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  delay(1000);
}

//////// Loop slut ////////
