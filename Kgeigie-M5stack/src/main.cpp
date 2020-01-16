// Test for displaying CPM and uS/h for kGeigie stickC version V2

#include <M5Stack.h>
#include </Users/rob/Documents/Arduino/libraries/M5Stack/src/Fonts/Custom/FreeSevenSegNumFont.h>

// Stock font and GFXFF reference handle
#define GFXFF 1
#define FF17 &FreeSans9pt7b
#define FF18 &FreeSans12pt7b
#define FF20 &FreeSans24pt7b
#define CF_7S &FreeSevenSegNumFont

// Conversion factor - CPM to uSV/h
#define CONV_FACTOR 0.008333 //for lnd7128

//setup initial variables
  const int geiger_input = 2;
  long count = 0;
  long lastcount = 0;
  long countPerMinute = 0;
  long timePrevious = 0;
  long timePreviousMeassure = 0;
  long time_long = 0;
  long countPrevious = 0;
  float radiationValue = 0.0;
  uint16_t seconds = 60;    
  uint32_t lastTime;


void IRAM_ATTR detectsPulse() {
  //Count the pulses routine
  count++;
}

void setup(void) {
  
  M5.begin();

  //Beeps at startup
      M5.Speaker.tone(900, 1000);
      delay(10);
      M5.Speaker.mute();

  // Reset text padding to zero (default)
      M5.Lcd.setTextPadding(0);

  // Setup counting pulse interrupt
      pinMode(geiger_input, INPUT_PULLUP);
      attachInterrupt(digitalPinToInterrupt(geiger_input), detectsPulse, RISING);

  //set colors
      M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);

  //Read the time and putinto lastTime
      lastTime = millis();

  //Start countdown and display startup text
      while (seconds > 0)
      {
        if (millis() - lastTime >= 1000)
        {
          seconds--;
          lastTime += 1000;

          //Clear display
              M5.Lcd.clear();  

          //display welcome and countdown
              M5.Lcd.setFreeFont(FF18);  
              M5.Lcd.drawString("kGeigie counter V0.1",40, 80, GFXFF);// Print the string name of the font  
              M5.Lcd.setFreeFont(FF17);  
              M5.Lcd.drawString("Countdown", 10,210, GFXFF);  

          //display time to first reading   
              M5.Lcd.setCursor(110,222);
              M5.Lcd.print(seconds);

          //Beep
              if (lastcount<count) {
                  M5.Speaker.tone(900, 1000);
                  delay(10);
                  M5.Speaker.mute();
              }
              lastcount = count;

          //Display safecast copyright
               M5.Lcd.drawString("SAFECAST 2019", 170, 210, GFXFF);

        }
      }

}

void loop() {
  //Beep
    if (lastcount<count) {
        M5.Speaker.tone(900, 1000);
        delay(10);
        M5.Speaker.mute();
    }
    lastcount = count;
  
    if (millis()-timePreviousMeassure > 60000){
      //setup counting and display sieverts
          int countPerMinute = count;
          float radiationValue = countPerMinute * CONV_FACTOR;
          timePreviousMeassure = millis();

      // Send serial data
          Serial.print("cpm = "); 
          Serial.print(countPerMinute,DEC);
          Serial.print(" - ");
          Serial.print("uSv/h = ");
          Serial.println(radiationValue);   

      //Display CPM  
          M5.Lcd.clear(); 
          M5.Lcd.setCursor(20,120);
          M5.Lcd.setFreeFont(FF20);  
          M5.Lcd.print("CPM =");
          M5.Lcd.setCursor(180,120);
          // setup for seven segment fonts
          M5.Lcd.setFreeFont(CF_7S);
          //Display data
          M5.Lcd.print(countPerMinute);

      //Display uSv/h
          M5.Lcd.setCursor(25,140);
          M5.Lcd.setFreeFont(FF17); 
          M5.Lcd.print("uSv/h =");
          M5.Lcd.setCursor(95,140);
          M5.Lcd.setFreeFont(FF17);
          //Display data 
          M5.Lcd.print(radiationValue,3);

      //Display safecast copyright
          M5.Lcd.drawString("SAFECAST 2019", 170, 210, GFXFF);// Print the string name of the font
      
      //Reset the counts and reset the count down
          count = 0;
          seconds = 60;
    }
}