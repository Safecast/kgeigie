// Test for displaying CPM and uS/h for kGeigie

#include <M5StickC.h>
#include <FreeSevenSegNumFont.h>

// Stock font and GFXFF reference handle
#define GFXFF 1
#define FF17 &FreeSans9pt7b
#define FF18 &FreeSans12pt7b
#define FF20 &FreeSans24pt7b
#define CF_7S &FreeSevenSegNumFont
#define testfont &FreeSerifBold9pt7b

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
  float totalcount = 0;
  long totalseconds = 0;
  float totalminutes = 0.0;
  long totalhours = 0;
  float averageCPM = 0.0;
  long minutesdisplay = 0;
  long iteration = 0;
  float avgradval = 0.0;
  long button = 0;
  float background = 0;
  long minind = 0;



void IRAM_ATTR detectsPulse() {
  //Count the pulses routine
  count++;
}

void setup(void) {
  
  M5.begin();

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
        //M5 stick-C has no speaker (unless attachment purchased)
      //M5.Speaker.tone(900, 1000);
        //M5.Lcd.drawCircle(40, 80, 30, RED);
        //M5.Lcd.fillCircle(40, 80, 30, RED);
        //delay(10);
        //M5.Lcd.drawCircle(40, 80, 30, BLACK);
        //M5.Lcd.fillCircle(40, 80, 30, BLACK);
      //M5.Speaker.mute();
    delay(3000);

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
              //M5.Lcd.clear(BLACK);  //Not combatible with M5Stick-C
              M5.Lcd.fillRect(0, 0, 200, 200, BLACK);

          //display welcome and countdown
              M5.Lcd.drawString("kGeigie Counter",0, 0, GFXFF);// Print the string name of the font  
              M5.Lcd.setFreeFont(FF17);  
              M5.Lcd.drawString("Countdown", 0, 20, GFXFF);  

          //display time to first reading   
              M5.Lcd.setCursor(100,33);
              M5.Lcd.fillRect(100, 18, 24, 17, BLACK); //equivalent to clear
              //delay(10);
              M5.Lcd.print(seconds);
        //Display safecast copyright
              M5.Lcd.drawString("SAFECAST 2020", 0, 50, GFXFF);

        //   //Beep
               if (lastcount<count) {
        //           M5.Speaker.tone(900, 1000);
        //           delay(10);
        //           M5.Speaker.mute();
        //     
                    M5.Lcd.drawCircle(138, 20, 10, RED);
                    M5.Lcd.fillCircle(138, 20, 10, RED);
                    delay(500);
                    M5.Lcd.drawCircle(138, 20, 10, BLACK);
                    M5.Lcd.fillCircle(138, 20, 10, BLACK);
                    //totalcount++;
               }
               lastcount = count;
               //totalcount = count;

        }
      }
      M5.Lcd.fillRect(0, 0, 200, 200, BLACK); //clear display

}
void secondloop(){
    Serial.print("one second thing"); 
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
    iteration++;
    }
    float countPerMinute = count;
    //M5.Lcd.setCursor(0,50);
    //M5.Lcd.print("Count Sum=");
    //M5.Lcd.setCursor(100,50);
    //M5.Lcd.print(totalcount);
    
    // add hour if min >= 60
    if (minutesdisplay >= 60) {
        totalhours = totalhours + 1;
        minutesdisplay = 0;
    }
//   //Beep
     if (lastcount<count) {
//         M5.Speaker.tone(900, 1000);
//         delay(10);
//         M5.Speaker.mute();
        M5.Lcd.drawCircle(145, 65, 10, RED); //137
        M5.Lcd.fillCircle(145, 65, 10, RED);
        //totalcount++;
        //M5.Lcd.setCursor(100,50);
        //M5.Lcd.fillRect(100, 35, 50, 17, BLACK); //"clear" by overwritting old total with black rect
        //M5.Lcd.setCursor(100,50);
        //M5.Lcd.print(totalcount);
        delay(500);
        M5.Lcd.drawCircle(145, 65, 10, BLACK);
        M5.Lcd.fillCircle(145, 65, 10, BLACK);
//Count Sum
    if (button >= 1) {
        M5.Lcd.fillRect(100, 35, 70, 17, BLACK);
        M5.Lcd.setCursor(0,50);
        M5.Lcd.print("Count Sum=");
        M5.Lcd.setCursor(100,50);
        M5.Lcd.print(totalcount,0);
    }
     }
     lastcount = count; 
     
    if (millis()-timePreviousMeassure > 60000){
        secondloop();
        totalminutes++;
        minutesdisplay++;
        averageCPM = (totalcount/(totalminutes)) - background; //+ (1/60)*seconds);
        float avgradval = averageCPM * CONV_FACTOR;
        float countPerMinute = count;
        float radiationValue = countPerMinute * CONV_FACTOR;
      //setup counting and display sieverts
          
          timePreviousMeassure = millis();
        
      // Send serial data
          Serial.print("cpm = "); 
          Serial.print(countPerMinute);
          Serial.print(" - ");
          Serial.print("uSv/h = ");
          Serial.println(radiationValue);
          Serial.print("Total Count = ");
          Serial.print(totalcount);   
          Serial.print("Time Elapsed: ");
          Serial.print(totalminutes);
          Serial.print("Average CPM = ");
          Serial.print(averageCPM);
          Serial.print("Average uSv/h = ");
          Serial.print(avgradval);

//old format
      //Display CPM  
          //M5.Lcd.clear(); 
          //M5.Lcd.fillRect(0, 0, 200, 200, BLACK); //large black rectangle which should "clear" screen
          //M5.Lcd.setCursor(0,15);
          //M5.Lcd.setFreeFont(FF17);  
          //M5.Lcd.print("CPM =");
          //M5.Lcd.setCursor(70,15);
          // setup for seven segment fonts
          //M5.Lcd.setFreeFont(FF17);
          //Display data
          //M5.Lcd.print(countPerMinute);
        //M5.Lcd.setCursor(0,70);
        //M5.Lcd.print("Time: ");
        //M5.Lcd.setCursor(50,70);
        //M5.Lcd.print(totalhours);
        //M5.Lcd.println("h");
        //M5.Lcd.setCursor(70,70);
        //M5.Lcd.print(minutesdisplay);
        //M5.Lcd.println("m");
        //M5.Lcd.setCursor(105,70);
        //M5.Lcd.print((millis() - timePreviousMeassure)/1000);
        //M5.Lcd.println("s");
      //Display uSv/h
          //M5.Lcd.setCursor(0,30);
          //M5.Lcd.setFreeFont(FF17); 
          //M5.Lcd.print("uSv/h =");
          //M5.Lcd.setCursor(70,30);
          //M5.Lcd.setFreeFont(FF17);
          //Display data 
          //M5.Lcd.print(radiationValue,3);
          //M5.Lcd.setCursor(0, )

      //Display safecast copyright
          //M5.Lcd.drawString("SAFECAST 2020", 0, 50, GFXFF);// Print the string name of the font
    //Avg Cpm
    if (button == 1) {
        M5.Lcd.fillRect(0, 0, 200, 35, BLACK);
        M5.Lcd.setCursor(0,15);
        M5.Lcd.print("Avg CPM =");
        M5.Lcd.println(averageCPM, 0);
        M5.Lcd.setCursor(0,30);
        M5.Lcd.print("Avg uSv/h =");
        M5.Lcd.println(avgradval, 3);
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
    }
    }
    //float countPerMinute = count;
    //float radiationValue = countPerMinute * CONV_FACTOR;
    //float avgradval = averageCPM * CONV_FACTOR;
      //Reset the counts and reset the count down
    if (M5.BtnA.wasReleased()) {
        M5.Lcd.fillRect(0, 0, 200, 200, BLACK);
        M5.Lcd.setCursor(0,50);
        M5.Lcd.print("Count Sum=");
        M5.Lcd.setCursor(100,50);
        M5.Lcd.print(totalcount, 0);
        M5.Lcd.setCursor(0,15);
        M5.Lcd.print("Avg CPM =");
        M5.Lcd.println(averageCPM, 3);
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
        //M5.Lcd.setCursor(105,70);
        //M5.Lcd.print(seconds);
        //M5.Lcd.println("s");
    //    if (lastcount<count) {
    //    M5.Lcd.setCursor(100,50);
    //    M5.Lcd.fillRect(100, 35, 50, 17, BLACK);
    //    M5.Lcd.setCursor(100,50);
    //    M5.Lcd.print(totalcount);
    //    }
    }
    if (M5.BtnB.wasReleased()) {
        M5.Lcd.fillRect(0, 0, 200, 200, BLACK);
        M5.Lcd.setCursor(0,30);
          M5.Lcd.setFreeFont(FF17); 
          M5.Lcd.print("uSv/h =");
          M5.Lcd.setCursor(70,30);
          M5.Lcd.setFreeFont(FF17);
          //Display data 
          M5.Lcd.print(radiationValue,3);
        M5.Lcd.setCursor(0,15);
          M5.Lcd.setFreeFont(FF17);  
          M5.Lcd.print("CPM =");
          M5.Lcd.setCursor(70,15);
          // setup for seven segment fonts
          M5.Lcd.setFreeFont(FF17);
          //Display data
          M5.Lcd.print(countPerMinute);
        M5.Lcd.setCursor(0,70);
        M5.Lcd.print("Time: ");
        M5.Lcd.setCursor(50,70);
        M5.Lcd.print(totalhours);
        M5.Lcd.println("h");
        M5.Lcd.setCursor(70,70);
        M5.Lcd.print(minutesdisplay);
        M5.Lcd.println("m");
        //M5.Lcd.setCursor(105,70);
        //M5.Lcd.print(seconds);
        //M5.Lcd.println("s");
        M5.Lcd.setCursor(0,50);
        M5.Lcd.print("Count Sum=");
        M5.Lcd.setCursor(100,50); //110 w/ total count =
        M5.Lcd.print(totalcount, 0);
        button = 2;
    }
    if (M5.BtnB.wasReleasefor(5000)) { //hold button B down for 5 seconds
    //Background
    M5.Lcd.fillRect(0, 0, 200, 35, BLUE);
    M5.Lcd.setCursor(0,15);
    M5.Lcd.print("Background Start");
    background = averageCPM;
  } 
  totalcount += count;
  count = 0;
  seconds = 60;
}