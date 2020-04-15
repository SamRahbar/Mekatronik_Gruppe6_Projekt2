#include <U8g2lib.h>
#include <Wire.h>


void oled() {

  switch (state) {
    case 1: // Weather 3 hour forecast

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

      break;

    case 2: // Weather 6 hour forecast

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

    case 3: // Weather 9 hour forecast

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

      u8g2.clearBuffer();          // clear the internal memory
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      u8g2.setCursor(0, 10);
      u8g2.print("Another interesting thing");
      u8g2.setCursor(0, 20);
      u8g2.print("to write on the OLED...");
      u8g2.sendBuffer();          // transfer internal memory to the display
      delay(100);

      Serial.println("Yeyey");
      break;

  }
}
