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

//////////// HARDWARE FINISHED ////////////


//////////// INITIATION ///////////

//inkluderer nødvendige bibloteker
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#include <U8g2lib.h>

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


// Definerer id og password til netværksforbindelse som NodeMCU anvender
const char* ssid = "XKEYSCORE #C-137"; //Indsæt navnet på jeres netværk her
const char* password = "arduinocode"; //Indsæt password her
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


String timestamp1;
String timestamp2;
String timestamp3;

String desc1;
String desc2;
String desc3;

float temp1;
float temp2;
float temp3;

/////// INITIATION FINISHED //////////

//
//
//
//
//
//

/////// FUNKTION SETUP ////////


// Opretter en placeholder for callback-funktionen til brug senere. Den rigtige funktion ses længere nede.
void callback(char* byteArraytopic, byte* byteArrayPayload, unsigned int length);

// Opretter en klient der kan forbinde til en specifik internet IP adresse.
WiFiClient espClient; // Initialiserer wifi bibloteket ESP8266Wifi, som er inkluderet under "nødvendige bibloteker"

// Opretter forbindelse til mqtt klienten:
PubSubClient client(mqtt_server, mqtt_port, callback, espClient); // Initialiserer bibloteket for at kunne modtage og sende beskeder til mqtt. Den henter fra definerede mqtt server og port. Den henter fra topic og beskeden payload

/////// FUNCTION SETUP SINISHED /////////

//
//
//
//
//
//

///////// CALLBACK FUNCTION ////////

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


    // Depending on payload message, set at state for the OLED to display a specific message
    if (payload == "GETWEATHER") { // Collect fresh weather data every 5 minutes
      weather();
      state = 1;
    }
    if (payload == "WEATHER1") { // 3 hour forecast
      state = 1;
    }
    if (payload == "WEATHER2") { // 6 hour forecast
      state = 2;
    }
    if (payload == "WEATHER3") { // 9 hour forecast
      state = 3;
    }
    if (payload == "OPEN") { // Test - turn on green led
      state = 4;
    }
    if (payload == "CLOSED") { // Test - turn on red led
      state = 5;
    }
    else { // If the signal from the mqtt is not one of the available options, give a message to the mqtt server and pass
      Serial.println(payload);
      client.publish("Status", "Unknown message");
      delay(100);
    }

    oled(); // Display the chosen message on OLED-screen
  }
}


///////// CALLBACK FINSHED /////////

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
  u8g2.begin(); // Start OLED-display

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
