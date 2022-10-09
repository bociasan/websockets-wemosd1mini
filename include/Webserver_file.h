#include <WebSocketsServer.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server;
WebSocketsServer webSocket = WebSocketsServer(81);

char* ssid = "Anonymus";
char* password = "camera18";

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
  if(type == WStype_TEXT){
    if(payload[0] == '#'){
      uint16_t brightness = (uint16_t) strtol((const char *) &payload[1], NULL, 10);
      brightness = 1024 - brightness;
      analogWrite(13, brightness);
      Serial.print("brightness= ");
      Serial.println(brightness);
    }

    else{
      for(int i = 0; i < length; i++)
        Serial.print((char) payload[i]);
      Serial.println();
    }
  }
  
}