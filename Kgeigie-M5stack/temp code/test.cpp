
#include <M5Stack.h>

const int pulsePin = 2;
int count=0;

// Timer: Auxiliary variables
unsigned long now = millis();

// Checks if motion was detected, sets LED HIGH and starts a timer
void IRAM_ATTR detectsPulse() {
  count++;
  Serial.println(count);

}

void setup() {

  Serial.begin(115200);
  pinMode(pulsePin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pulsePin), detectsPulse, RISING);
}

void loop() {
  // Current time
  now = millis();
}


