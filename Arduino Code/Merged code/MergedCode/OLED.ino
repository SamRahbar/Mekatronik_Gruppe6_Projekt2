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
      break;

    case 4: // Locker has been opened with RFID

      digitalWrite(2, HIGH);
      u8g2.clearBuffer();          // clear the internal memory
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      u8g2.setCursor(0, 10);
      u8g2.print("Locker opened with RFID");
      //      u8g2.setCursor(0, 20);
      //      u8g2.print("to write on the OLED...");
      u8g2.sendBuffer();          // transfer internal memory to the display
      break;

    case 5: // Access denied - For RFID users

      u8g2.clearBuffer();          // clear the internal memory
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      u8g2.setCursor(0, 10);
      u8g2.print("Access denied");
      //      u8g2.setCursor(0, 20);
      //      u8g2.print("to write on the OLED...");
      u8g2.sendBuffer();          // transfer internal memory to the display
      break;

    case 6: // Door locked with RFID

      u8g2.clearBuffer();          // clear the internal memory
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      u8g2.setCursor(0, 10);
      u8g2.print("Door locked with");
      u8g2.setCursor(0, 20);
      u8g2.print("RFID");
      u8g2.sendBuffer();          // transfer internal memory to the display
      break;

    case 7: // Door Opened because of timer
      u8g2.clearBuffer();          // clear the internal memory
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      u8g2.setCursor(0, 10);
      u8g2.print("Door opened");
      u8g2.setCursor(0, 20);
      u8g2.print("because of timer");
      u8g2.sendBuffer();          // transfer internal memory to the display
      break;

    case 8: // Door opened because of nodered
      u8g2.clearBuffer();          // clear the internal memory
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      u8g2.setCursor(0, 10);
      u8g2.print("Door opened");
      u8g2.setCursor(0, 20);
      u8g2.print("via nodered");
      u8g2.sendBuffer();          // transfer internal memory to the display
      break;

    case 9: // Door locked because of nodered
      u8g2.clearBuffer();          // clear the internal memory
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      u8g2.setCursor(0, 10);
      u8g2.print("Door locked");
      u8g2.setCursor(0, 20);
      u8g2.print("via nodered");
      u8g2.sendBuffer();          // transfer internal memory to the display
      break;
  }
}


void weatherCycle() { //Cycles through the 3 weather states
  if (ttime - prevWeatherShowed >= weatherInterval) { //Checks if the next frame should show
    Serial.println("Frame updater");
    prevWeatherShowed = ttime; //Sets last frame time
    if (frame == 3) { //Makes sure it loops
      frame = 1; //Sets frame to keep the loop going
      state = frame; 
    }
    else {
      frame ++; //Steps frame with 1
      state = frame; //Sets state to frame so state wont go past its limit
    }
  }
  oled();//Updates oled
}
