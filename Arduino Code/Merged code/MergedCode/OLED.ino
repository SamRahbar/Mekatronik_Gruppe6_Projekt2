#include <U8g2lib.h>
#include <Wire.h>

// Switch function for OLED-creen.
// Depending on the state, the OLED will display a specific message.

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
      //delay(100);

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
      //delay(100);

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
      //delay(100);

      break;

    case 4: // TEST - green LED

      digitalWrite(2, HIGH);
      //RGB_color(0,90,0);
      //delay(100);
      client.publish("Status", "Green");

      u8g2.clearBuffer();          // clear the internal memory
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      u8g2.setCursor(0, 10);
      u8g2.print("Locker opened");
      //      u8g2.setCursor(0, 20);
      //      u8g2.print("to write on the OLED...");
      u8g2.sendBuffer();          // transfer internal memory to the display
      //delay(100);

      break;

    case 5: // TEST - red LED

      //RGB_color(90,0,0);
      //delay(100);
      client.publish("Status", "Red");

      u8g2.clearBuffer();          // clear the internal memory
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      u8g2.setCursor(0, 10);
      u8g2.print("Access denied");
      //      u8g2.setCursor(0, 20);
      //      u8g2.print("to write on the OLED...");
      u8g2.sendBuffer();          // transfer internal memory to the display
      //delay(100);

      //Serial.println("Yeyey");
      break;

    case 6: // TEST - red LED

      //RGB_color(90,0,0);
      //delay(100);
//      client.publish("Status", "Red");

      u8g2.clearBuffer();          // clear the internal memory
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      u8g2.setCursor(0, 10);
      u8g2.print("New card has been");
      u8g2.setCursor(0, 20);
      u8g2.print("secured");
      u8g2.sendBuffer();          // transfer internal memory to the display
      //delay(100);

      //Serial.println("Yeyey");
      break;
    
    case 7: // TEST - red LED

      //RGB_color(90,0,0);
      //delay(100);
//      client.publish("Status", "Red");

      u8g2.clearBuffer();          // clear the internal memory
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      u8g2.setCursor(0, 10);
      u8g2.print("Door opened");
      u8g2.setCursor(0, 20);
      u8g2.print("because of timer");
      u8g2.sendBuffer();          // transfer internal memory to the display
      //delay(100);

      //Serial.println("Yeyey");
      break;
  }
}

void weatherCycle(){
  if(ttime - prevWeatherShowed >= weatherInterval){
    Serial.println("Frame updater");
    prevWeatherShowed = ttime;
    if(frame == 3){
      frame = 1;
      state = frame;
      Serial.println("Frame"+ frame);
      oled();
    }
    else{
      frame ++;
      state = frame;
      Serial.println("Frame"+ frame);
      oled();
    } 
  }
}
