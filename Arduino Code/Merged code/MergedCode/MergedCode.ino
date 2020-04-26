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
const char* ssid = "XKEYSCORE #C-137"; //Network name
const char* password = "arduinocode"; //Wifipassword
//dlink-79BC-5GHz uygqk50992

// Definerer information til mqtt serveren
const char *mqtt_server = "hairdresser.cloudmqtt.com"; //The name of the mqtt site
const int mqtt_port = 15721; // Defines the mqtt port
const char *mqtt_user = "Sam"; // Defines the mqtt username
const char *mqtt_pass = "Sam"; //Defines the mqtt code

String payload; //Defines the variable 'payload' in the global scope

// For OLED Screen
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int state; // The chosen state/frame of the oled

//-- Weather info --
String timestamp1;
String timestamp2;
String timestamp3;

String desc1;
String desc2;
String desc3;

float temp1;
float temp2;
float temp3;

//-- RFID Values ------
String SecureID; // The users RFID
String MasterID = "D9 DF 57 C1"; // The janitors RFID

bool doorOpen = true; // The boolean that knows if the door is open or not

int frame = 3; // The frame of the oled screen

int buttonState = 0;         // variable for reading the pushbutton status

bool NodeRedInUse = false; // variable for knowing if node red is in use

unsigned long ttime; //Assigns a value for time
unsigned long prevMillisConnect = 0; //Previous time tried to connect
unsigned long prevMillisReconnect = 0; //Previous time tried to reconnect
const long openTimerInterval = 28800000; //How long the locker will be closed for
unsigned long prevOpenTimer = 0; //When the door was locked
unsigned long prevWeatherShowed = 0; //Last time weather was shown
const long weatherInterval = 5000; //How often weather gets shown
unsigned long lastWeatherGet = 0; //Last time the weather info was updated
const long weatherGetInterval = 300000; //How often the weather info gets updated


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
  weather(); // Henter vejrinformationen ved startup
  MQTT_Setup(); // Kører setup til MQTT
  u8g2.begin(); // Start OLED-display
  RFIDSetup(); // Kører RFID setup
  ButtonSetup(); // Kører button setup
  LEDSetup(); // Kører LED setup
}

void loop() {
  ButtonLoop(); // Kører button loop
  ttime = millis(); // Giver os en tidsvariabel
  RFIDLoop(); // Kører RFIDLoopet
  MQTT_Loop(); // Kører MQTT loopet
  DoorTimerUnlock(); // Kører metoden der åbner døren efter en given tid siden den blev låst
  weatherCycle(); // Får skærmen til at vise forskelligt vejr
  WeatherGetter(); // Opdaterer vejrinformationen hvert 5 minut
  LockoutSecurity(); // Sørger for at døren ikke kan lukkes når den ikke skal være låst
}
