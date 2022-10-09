#include <ESP8266WiFi.h>
#include <Startup_file.h>

void setup()
{
  startup();
}

void loop()
{
  webSocket.loop();
  server.handleClient();
  if (encoderCounterHasChanged){
    encoderCounterHasChanged = false;
    char buffer[5];
    sprintf(buffer, "%d", encoderCounter);
    Serial.print("From loop: ");
    Serial.println(buffer);
    webSocket.broadcastTXT(buffer);

    fill_solid (leds, NUM_LEDS, CHSV(encoderCounter, 255, 255));
    FastLED.show();
  
  }
}
