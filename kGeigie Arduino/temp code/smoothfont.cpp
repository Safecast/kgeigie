

#include <M5Stack.h>


void setup(void) {
M5.begin();
Serial.begin(115200);
  if (!SPIFFS.begin()) {
    Serial.println("\r\nSPIFFS initialisation failed!");
    while (1) yield(); // Stay here twiddling thumbs waiting
  }
  Serial.println("\r\nSPIFFS available!");
  
  // ESP32 will crash if any of the fonts are missing
  bool font_missing = false;
  if (SPIFFS.exists("/OpenSans-Regular-24.vlw")    == false) font_missing = true;
  if (SPIFFS.exists("/OpenSans-Regular-14.vlw")    == false) font_missing = true;
  if (SPIFFS.exists("/DSEG7Modern-Bold-48.vlw")    == false) font_missing = true;

  if (font_missing)
  {
    Serial.println("\r\nFont missing in SPIFFS, did you upload it?");
    while(1) yield();
  }
  else Serial.println("\r\nFonts found OK.");

M5.Lcd.clear();
M5.Lcd.setTextWrap(true,true);
String fontName="OpenSans-Regular-14";
M5.Lcd.loadFont(fontName);
M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
M5.Lcd.setCursor(10,10);
M5.Lcd.print("SAFECAST");

String fontName2="DSEG7Modern-Bold-48";
M5.Lcd.loadFont(fontName2);
M5.Lcd.println(" 465");

}
void loop() {
}
