#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Webserver_file.h>
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


void startup() {
    FastLED.addLeds<WS2812B,D1>(leds, NUM_LEDS);
    for(int i = 0; i < NUM_LEDS; i++) {   
        leds[i] = CHSV(0,0,0);
    }
    FastLED.setBrightness(50);
    FastLED.show();

    WiFi.begin(ssid,password);
    Serial.begin(115200);
    while(WiFi.status()!=WL_CONNECTED)
    {
        // {
        //     EVERY_MS(500){
        //         Serial.print(".");
        //         // leds[0] = CHSV(255, 255, 255);
        //         }
        // }
        // {
        //         EVERY_MS(50){
        //         loadingAnimation();
        //     }
        // }

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