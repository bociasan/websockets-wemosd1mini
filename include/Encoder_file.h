#include <Arduino.h>

#define pinA D6    
#define pinB D7
unsigned char lastState = 0, intermediateState = 5;
int  encoderCounter = 0;
bool encoderCounterHasChanged = false;

IRAM_ATTR void isr() {
  unsigned char currentState = GPIP(pinA)<<1 | GPIP(pinB);
  if ((currentState == 0 || currentState == 3) && currentState != lastState){
    lastState = currentState;
    if ((currentState == 0 && intermediateState == 1) || (currentState == 3 && intermediateState == 2)) {
      encoderCounter++;
    } else encoderCounter--;

    encoderCounterHasChanged = true;
    intermediateState = 5;
  } else {
    intermediateState = currentState;
  }
}