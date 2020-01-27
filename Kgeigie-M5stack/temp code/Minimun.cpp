
#include <M5Stack.h>


void setup()
{
  M5.begin();
  Serial.begin(115200);
  Serial.println("test");

}

void loop()
{
    Serial.println("test2");
    delay(1000);
}
