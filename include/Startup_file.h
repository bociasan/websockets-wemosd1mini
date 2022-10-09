#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <ESP8266WebServer.h>
#include <Webpage_file.h>
#include <Encoder_file.h>
#include <FastLED.h>

#define NUM_LEDS 69
CRGB leds[NUM_LEDS];

#define EVERY_MS(x) \
  static uint32_t tmr;\
  bool flag = millis() - tmr >= (x);\
  if (flag) tmr = millis();\
  if (flag)

void loadingAnimation(){
    for(int i = NUM_LEDS - 2; i >= 0; i-- ){
        if (leds[i] == CHSV(255, 255, 255)){
                if (leds[i+1] != CHSV(255, 255, 255)){
                  leds[i+1] = CHSV(255, 255, 255);
                  leds[i] = CHSV(0,0,0);
                }
        }
    }
    FastLED.show();
}

//////////////// webserver
ESP8266WebServer server;
WebSocketsServer webSocket = WebSocketsServer(81);

char* ssid = "Anonymus";
char* password = "camera18";

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
  if(type == WStype_TEXT){
    if(payload[0] == '#'){
      uint16_t brightness = (uint16_t) strtol((const char *) &payload[1], NULL, 10);
      
      encoderCounterHasChanged = true;
      encoderCounter= brightness;

    //   fill_solid (leds, NUM_LEDS, CHSV(brightness, 255, 255));
    //   FastLED.show();
      Serial.print("brightness= ");
      Serial.println(brightness);

    //
    char buffer[5];
    sprintf(buffer, "%d", brightness);
    webSocket.broadcastTXT(buffer);
    //

    }

    else{
      for(int i = 0; i < length; i++)
        Serial.print((char) payload[i]);
      Serial.println();
    }
  }
  
}
///////////////// webserver

bool conectedFlag = false;
byte loadingIndex = 0;

void startup() {
    FastLED.addLeds<WS2812B,D1>(leds, NUM_LEDS);
    for(int i = 0; i < NUM_LEDS; i++) {   
        leds[i] = CHSV(0,0,0);
    }
    FastLED.setBrightness(50);
    FastLED.show();

    WiFi.begin(ssid,password);
    Serial.begin(115200);
    while(WiFi.status()!=WL_CONNECTED){
        // {
        //     EVERY_MS(500){
        //         if (WiFi.status() == WL_CONNECTED) conectedFlag = true;
        //         Serial.print(".");
        //         leds[0] = CHSV(255, 255, 255);
        //         }
        // }
        // {
        //         EVERY_MS(20){
        //         loadingAnimation();
        //     }
        // }

    // leds[loadingIndex++] = CHSV(255, 255, 255);
    fill_solid (leds, NUM_LEDS, CHSV(random8(), 255, 255));
    FastLED.show();
    Serial.print(".");
    delay(500);
        
    }
    Serial.println("");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.on("/",[](){
        server.send_P(200, "text/html", webpage);  
    });
    server.begin();
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);

    // encodeer
    attachInterrupt(pinA, isr, CHANGE);  
    attachInterrupt(pinB, isr, CHANGE); 
    lastState = GPIP(pinA)<<1 | GPIP(pinB);
    if (lastState != 3 && lastState != 0) {
        intermediateState = lastState;
        lastState = 0;
    };
    // encodeer
  
}