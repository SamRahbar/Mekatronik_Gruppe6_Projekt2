//////////// INITIATION ///////////

//inkluderer nødvendige bibloteker
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#include <U8g2lib.h>

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN      D4
#define RST_PIN     D3
#define btn_PIN     D8

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

// Definerer id og password til netværksforbindelse som NodeMCU anvender
const char* ssid = "XKEYSCORE #C-137"; //Indsæt navnet på jeres netværk her
const char* password = "arduinocode"; //Indsæt password her
//dlink-79BC-5GHz uygqk50992

// Definerer information til mqtt serveren
const char *mqtt_server = "hairdresser.cloudmqtt.com"; //navn på mqtt-server. Find navnet på cloudmqtt-hjemmesiden
const int mqtt_port = 15721; // Definerer porten
const char *mqtt_user = "Ellen1"; // Definerer mqtt-brugeren
const char *mqtt_pass = "gruppe6go"; // Definerer koden til mqtt-brugeren

String payload; // Definerer variablen 'payload' i det globale scope (payload er navnet på besked-variablen)

// For OLED Screen
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

int state;

String timestamp1;
String timestamp2;
String timestamp3;

String desc1;
String desc2;
String desc3;

float temp1;
float temp2;
float temp3;

// -- LED setup -------
//int red_light_pin   = SDD1;
//int green_light_pin = SDD2;
//int blue_light_pin  = SDD3;

//-- RFID Values ------
String SecureID;
String MasterID = "D9 DF 57 C1";

bool doorOpen = true;

unsigned long ttime;
unsigned long lastTtimeOpen = 0;
const long openInterval = 3000;
unsigned long prevMillisConnect = 0;
unsigned long prevMillisReconnect = 0;

// Opretter en placeholder for callback-funktionen til brug senere. Den rigtige funktion ses længere nede.
void callback(char* byteArraytopic, byte* byteArrayPayload, unsigned int length);

// Opretter en klient der kan forbinde til en specifik internet IP adresse.
WiFiClient espClient; // Initialiserer wifi bibloteket ESP8266Wifi, som er inkluderet under "nødvendige bibloteker"

// Opretter forbindelse til mqtt klienten:
PubSubClient client(mqtt_server, mqtt_port, callback, espClient); // Initialiserer bibloteket for at kunne modtage og sende beskeder til mqtt. Den henter fra definerede mqtt server og port. Den henter fra topic og beskeden payload

/////// INITIATION FINISHED //////////

void setup() {

  Serial.begin(115200); // Åbner serial porten og sætter data raten til 115200 baud

  setup_wifi(); // Kører WiFi loopet og forbinder herved.
  MQTT_Setup(); // Kører setup til MQTT
  u8g2.begin(); // Start OLED-display
  RFIDSetup();
}

void loop() {
  ttime = millis();
  RFIDLoop();
  MQTT_Loop();
}
