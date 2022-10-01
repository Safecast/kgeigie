#include <M5Stack.h>

#define NOTE_DH2 661



void setup() {
  // Initialize the M5Stack object
  M5.begin();

  M5.Lcd.printf("M5Stack Speaker test:\r\n");
}

void loop() {
  if(M5.BtnB.wasPressed())
  {
    M5.Lcd.printf("B wasPressed \r\n");
    M5.Speaker.tone(NOTE_DH2, 200); //frequency 3000, with a duration of 200ms
  }

  M5.update();
}