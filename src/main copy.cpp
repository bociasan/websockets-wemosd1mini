// #include <Arduino.h>

// #include <ESP8266WiFi.h>
// #include <ESP8266WebServer.h>
// #include <WebSocketsServer.h>
// #include <MyEncoder.h>

// #define pinA D6    
// #define pinB D7
// MyEncoder enc(pinA, pinB);

// ESP8266WebServer server;
// WebSocketsServer webSocket = WebSocketsServer(81);

// char* ssid = "Anonymus";
// char* password = "camera18";

// char webpage[] PROGMEM = R"=====(
// <html>
// <head>
//   <script>
//     var Socket;
//     function init() {
//       Socket = new WebSocket('ws://' + window.location.hostname + ':81/');
//       Socket.onmessage = function(event){
//         document.getElementById("rxConsole").value += event.data;
//       }
//     }
//     function sendText(){
//       Socket.send(document.getElementById("txBar").value);
//       document.getElementById("txBar").value = "";
//     }
//     function sendBrightness(){
//       Socket.send("#"+document.getElementById("brightness").value);
//     }    
//   </script>
// </head>
// <body onload="javascript:init()">
//   <div>
//     <textarea id="rxConsole"></textarea>
//   </div>
//   <hr/>
//   <div>
//     <input type="text" id="txBar" onkeydown="if(event.keyCode == 13) sendText();" />
//   </div>
//   <hr/>
//   <div>
//     <input type="range" min="0" max="1023" value="512" id="brightness" oninput="sendBrightness()" />
//   </div>

// </body>
// </html>
// )=====";


// void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
//   if(type == WStype_TEXT){
//     if(payload[0] == '#'){
//       uint16_t brightness = (uint16_t) strtol((const char *) &payload[1], NULL, 10);
//       brightness = 1024 - brightness;
//       analogWrite(13, brightness);
//       Serial.print("brightness= ");
//       Serial.println(brightness);
//     }

//     else{
//       for(int i = 0; i < length; i++)
//         Serial.print((char) payload[i]);
//       Serial.println();
//     }
//   }
  
// }

// void setup()
// {
//   WiFi.begin(ssid,password);
//   Serial.begin(115200);
//   enc.begin();
//   while(WiFi.status()!=WL_CONNECTED)
//   {
//     Serial.print(".");
//     delay(500);
//   }
//   Serial.println("");
//   Serial.print("IP Address: ");
//   Serial.println(WiFi.localIP());

//   server.on("/",[](){
//     server.send_P(200, "text/html", webpage);  
//   });
//   server.begin();
//   webSocket.begin();
//   webSocket.onEvent(webSocketEvent);
// }

// void loop()
// {
//   webSocket.loop();
//   server.handleClient();
//   if(Serial.available() > 0){
//     char c[] = {(char)Serial.read()};
//     webSocket.broadcastTXT(c, sizeof(c));
//   }
// }
