#include <Arduino.h>
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
    Serial.println(buffer);
    webSocket.broadcastTXT(buffer);

  
  }
}
