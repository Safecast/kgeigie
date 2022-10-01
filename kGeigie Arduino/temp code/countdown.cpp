
#include <M5Stack.h>

uint16_t seconds = 60;      // max == 65535
uint32_t lastTime;


void setup()
{
  Serial.begin(115200);

  lastTime = millis();
  while (seconds > 0)
  {
    if (millis() - lastTime >= 1000)
    {
       seconds--;
       lastTime += 1000;
       Serial.println(seconds);
     }
  }
}

void loop()
{
}




