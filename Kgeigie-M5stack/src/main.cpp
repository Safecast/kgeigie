//**************************************************// 
//    Display for kGeigie (kids Geiger Counter)     //
//                    V2.0.0                        //
// Intended for breadboard assembly with M5 Stick-C //
//     Reads CPM, uSv/h, Avg CPM, and Avg uSv/h     //
//        Includes background count feature         //
//                                                  //
//   written by Rob Oudendijk and Catherine Mohr    //
//     Contact email: catherinermohr@gmail.com      //
//          Copyright (c) 2020, Safecast            //        
//              All rights reserved.                //
//**************************************************//

#include <M5StickC.h>
#include <FreeSevenSegNumFont.h>

// Stock font and GFXFF reference handle
#define GFXFF 1
#define FF17 &FreeSans9pt7b

// Conversion factor - CPM to uSV/h
#define CONV_FACTOR 0.008333 //for lnd7128

//setup initial variables
  const int geiger_input = 36; //must use this port if speaker attachment
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
  long totalcount = 0;
  long totalseconds = 0;
  float totalminutes = 0.0;
  long totalhours = 0;
  float averageCPM = 0.0;
  long minutesdisplay = 0;
  float avgradval = 0.0;
  long button = 0;
  float background = 0;
  //**sound variables**//
  const int servo_pin = 26; //connect speaker in port G26
  int freq = 50;
  int ledChannel = 0;
  int resolution = 10;

void IRAM_ATTR detectsPulse() {
  //Count the pulses routine
  count++;
  totalcount++;
}

void setup(void) {
  M5.begin();
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(servo_pin, ledChannel);

//draw Safecast Logo
  M5.Lcd.setFreeFont(FF17);  
  M5.Lcd.setRotation(3);
  M5.Lcd.drawLine(10, 5, 50, 30, WHITE);
  M5.Lcd.drawLine(50,30,50, 65, WHITE);
  M5.Lcd.drawLine(10, 17, 40, 35, WHITE);
  M5.Lcd.drawLine(40,35,40, 65, WHITE);
  M5.Lcd.fillCircle(20, 50, 10, BLUE);
  M5.Lcd.setCursor(55,30); //51
  M5.Lcd.print("SAFECAST");
  M5.Lcd.setCursor(80,50);
  M5.Lcd.print("2020");

  //Beeps at startup
    ledcWriteTone(ledChannel, 1000);
    delay(500); //beep for 0.5 seconds
    ledcWriteTone(ledChannel, 0);
    delay(3000); //delay to give time to view logo

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
              M5.Lcd.fillRect(0, 0, 200, 200, BLACK); //equivalent to "clear" function

          //display welcome and countdown
              M5.Lcd.drawString("kGeigie Counter",0, 0, GFXFF);// Print the string name of the font  
              M5.Lcd.setFreeFont(FF17);  
              M5.Lcd.drawString("Countdown", 0, 20, GFXFF);  

          //display time to first reading   
              M5.Lcd.setCursor(100,33);
              M5.Lcd.fillRect(100, 18, 24, 17, BLACK);
              M5.Lcd.print(seconds);
        //Display safecast copyright
              M5.Lcd.drawString("SAFECAST 2020", 0, 50, GFXFF);

        // Beep and display red circle when count detected
               if (lastcount<count) {  
                    M5.Lcd.fillCircle(138, 20, 10, RED);
                    ledcWriteTone(ledChannel, 1000);
                    delay(50);
                    ledcWriteTone(ledChannel, 0);
                    M5.Lcd.fillCircle(138, 20, 10, BLACK);
               }
               lastcount = count;
        }
      }
      M5.Lcd.fillRect(0, 0, 200, 200, BLACK); //clear display

}
int secondloop(float totalminutes, float count){
    float countPerMinute = count;
    float radiationValue = countPerMinute * CONV_FACTOR;
    //serial print the info
    Serial.print("second loop count =");
    Serial.println(count); 
    Serial.print("radiationVal from second=");
    Serial.println(radiationValue); 

    //return the random count
    return countPerMinute;
}

void loop() {
    M5.update();
    //display menu of button options
    if (button==0) {
    M5.Lcd.setCursor(0,15); //51
    M5.Lcd.print("A for Average");
    M5.Lcd.setCursor(0,30); //55
    M5.Lcd.print("B for Current");
    M5.Lcd.setCursor(0,50); //70
    M5.Lcd.print("Hold B for");
    M5.Lcd.setCursor(0,70); //55
    M5.Lcd.print("Background");
    }
    // add hour if min >= 60
    if (minutesdisplay >= 60) {
        totalhours = totalhours + 1;
        minutesdisplay = 0;
    }
//   //Beep and display red circle when count detected
     if (lastcount<count) {
        M5.Lcd.fillCircle(145, 65, 10, RED);
        ledcWriteTone(ledChannel, 1000);
        delay(50);
        ledcWriteTone(ledChannel, 0);
        M5.Lcd.fillCircle(145, 65, 10, BLACK);
//Print Count Sum after every beep (if not on button menu)
    if (button >= 1) {
        M5.Lcd.fillRect(100, 35, 70, 17, BLACK);
        M5.Lcd.setCursor(0,50);
        M5.Lcd.print("Count Sum=");
        M5.Lcd.setCursor(100,50);
        M5.Lcd.print(totalcount);
    }
  }
  lastcount = count; 

  //Loop which lasts one minute, for CPM
    if (millis()-timePreviousMeassure > 60000){
        countPerMinute= secondloop(totalminutes, count); // current CPM
        float radiationValue = countPerMinute * CONV_FACTOR; //current uSv/h

        //check return count
        Serial.print ("totalminutes=");
        Serial.println (totalminutes);

        //continue
        totalminutes++; //for calculating avg CPM
        minutesdisplay++; //for displaying time
        averageCPM = (totalcount/(totalminutes)) - background; //+ (1/60)*seconds);
        float avgradval = averageCPM * CONV_FACTOR;  // Avg uSv/h
      //setup counting and display sieverts
          timePreviousMeassure = millis();
        
      // Send serial data
          Serial.print("cpm = "); 
          Serial.print(countPerMinute);
          Serial.print(" - ");
          Serial.print("uSv/h = ");
          Serial.println(radiationValue);
          Serial.print(" Total Count = ");
          Serial.print(totalcount);   
          Serial.print(" Time Elapsed: ");
          Serial.print(totalminutes);
          Serial.print(" Average CPM = ");
          Serial.print(averageCPM);
          Serial.print(" Average uSv/h = ");
          Serial.println(avgradval);
    // If minute passes after a button has been pressed, update screen's data
    if (button == 1) {
        M5.Lcd.fillRect(0, 0, 200, 35, BLACK);
        M5.Lcd.setCursor(0,15);
        M5.Lcd.print("Avg CPM =");
        M5.Lcd.println(averageCPM, 0);
        M5.Lcd.setCursor(0,30);
        M5.Lcd.print("Avg uSv/h =");
        M5.Lcd.println(avgradval,3);
    }
    if (button ==2){
        M5.Lcd.fillRect(0, 0, 200, 35, BLACK);
        M5.Lcd.setCursor(0,15);
        M5.Lcd.print("CPM =");
        M5.Lcd.println(countPerMinute);
        M5.Lcd.setCursor(0,30);
        M5.Lcd.print("uSv/h =");
        M5.Lcd.println(radiationValue, 3);
    }
//both button menus have time and count sum
    if (button >= 1) {
        M5.Lcd.fillRect(50, 55, 60, 60, BLACK);
        M5.Lcd.setCursor(0,70);
        M5.Lcd.print("Time: ");
        M5.Lcd.setCursor(50,70);
        M5.Lcd.print(totalhours);
        M5.Lcd.println("h");
        M5.Lcd.setCursor(70,70);
        M5.Lcd.print(minutesdisplay);
        M5.Lcd.println("m");
        M5.Lcd.setCursor(0,50);
        M5.Lcd.print("Count Sum=");
        M5.Lcd.setCursor(100,50);
        M5.Lcd.print(totalcount);
    }
  //Reset the counts and reset the count down
  count = 0;
  seconds = 60;
    }
    // calculate uSv/h values
    float radiationValue = countPerMinute * CONV_FACTOR;
    float avgradval = averageCPM * CONV_FACTOR;

    //display Averages if Button A (M5 button) pressed
    if (M5.BtnA.wasReleased()) {
        M5.Lcd.fillRect(0, 0, 200, 200, BLACK);
        M5.Lcd.setCursor(0,50);
        M5.Lcd.print("Count Sum=");
        M5.Lcd.setCursor(100,50);
        M5.Lcd.print(totalcount);
        M5.Lcd.setCursor(0,15);
        M5.Lcd.print("Avg CPM =");
        M5.Lcd.println(averageCPM, 0);
        M5.Lcd.setCursor(0,30);
        M5.Lcd.print("Avg uSv/h =");
        M5.Lcd.println(avgradval, 3);
        M5.Lcd.setCursor(0,70);
        M5.Lcd.print("Time: ");
        M5.Lcd.setCursor(50,70);
        M5.Lcd.print(totalhours);
        M5.Lcd.println("h");
        M5.Lcd.setCursor(70,70);
        M5.Lcd.print(minutesdisplay);
        M5.Lcd.println("m");
        button = 1;
    }
    //Display current CPM measured if button B (side) pressed
    if (M5.BtnB.wasReleased()) {
        M5.Lcd.fillRect(0, 0, 200, 200, BLACK);
        M5.Lcd.setCursor(0,30);
        M5.Lcd.print("uSv/h =");
        //Display data 
        M5.Lcd.println(radiationValue,3);
        M5.Lcd.setCursor(0,15);
        M5.Lcd.print("CPM =");
        //Display data
        M5.Lcd.println(countPerMinute);
        M5.Lcd.setCursor(0,70);
        M5.Lcd.print("Time: ");
        M5.Lcd.setCursor(50,70);
        M5.Lcd.print(totalhours);
        M5.Lcd.println("h");
        M5.Lcd.setCursor(70,70);
        M5.Lcd.print(minutesdisplay);
        M5.Lcd.println("m");
        M5.Lcd.setCursor(0,50);
        M5.Lcd.print("Count Sum=");
        M5.Lcd.setCursor(100,50);
        M5.Lcd.print(totalcount);
        button = 2;
    }
    //hold button B down for 5 seconds to set avg CPM as background
    if (M5.BtnB.wasReleasefor(5000)) { 
    //Background
    M5.Lcd.fillRect(0, 0, 200, 35, BLUE);
    M5.Lcd.setCursor(0,15);
    M5.Lcd.print("Background Start");
    background = averageCPM;
    Serial.print("Background!");
    Serial.print(background);
    totalcount = 0;
    totalminutes = 0;
  } 
}