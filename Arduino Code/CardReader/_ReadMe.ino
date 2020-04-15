/*
 * All the resources for this project: https://randomnerdtutorials.com/
 * With contributions from: https://www.instructables.com/id/MFRC522-RFID-Reader-Interfaced-With-NodeMCU/
 * Modified by Rui Santos & Peder & Sam Rahbar
 * 
 * Created by FILIPEFLOP
 * RFID-RC522 Connections:
 * ---------------------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino       
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro     NODE MCU
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * ---------------------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST           D3
 * SPI SS      SDA(SS)      10            53        D10        10               10            D4
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16            D7
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14            D6
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15            D5
 * 
 * Button Connected to pin D8
 * 
 * RGB LED connection:
 * R: D0
 * G: D1
 * B: D2
 */
