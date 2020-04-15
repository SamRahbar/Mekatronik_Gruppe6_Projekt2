#include <U8g2lib.h>
#include <Wire.h>
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


void oled() {

  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2.setCursor(0, 10);
  u8g2.print("Another interesting thing");
  u8g2.setCursor(0, 20);
  u8g2.print("to write on the OLED...");
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay(100);

  Serial.println("Yeyey");

}


void OLED_char(const char* input) {
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2.drawStr(0, 10, input); // write something to the internal memory
  u8g2.sendBuffer();          // transfer internal memory to the display
}
