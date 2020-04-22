//void RGBSetup(){
//  pinMode(red_light_pin, OUTPUT);
//  pinMode(green_light_pin, OUTPUT);
//  pinMode(blue_light_pin, OUTPUT);
//}


//void RGB_color(int red_light_value, int green_light_value, int blue_light_value) {
//  analogWrite(red_light_pin, red_light_value);
//  analogWrite(green_light_pin, green_light_value);
//  analogWrite(blue_light_pin, blue_light_value);
//}

void LEDState() {
  switch (sstate) {
    case 0://Locked
      //RGB_color(100,0,0);
      state = 5;
      break;
    case 1://Open
      //RGB_color(0,100,0);
      state = 4;
      break;
  }
}
