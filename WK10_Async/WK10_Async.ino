#include "WiFi.h"
#include "ESPAsyncWebServer.h"
 
const char* ssid = "smallblack";
const char* password = "0487ggyy";
 
AsyncWebServer server(80);

void handleRoot(AsyncWebServerRequest *request) {
  char temp[1000];
  snprintf(temp, 1000,"<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><script src=\"https://code.jquery.com/jquery-2.2.4.min.js\"></script><script>setInterval(requestData, 500);function requestData(){$.get(\"/sensors\").done(function(data){if(data){$(\"#resis\").text(data.vr);} else {$(\"#resis\").text(\"?\");}}).fail(function(){console.log(\"fail\");});  }</script><title>VR Reader</title></head><body><div class=\"container\"><p>Variable Resistor = <span id=\"resis\"></span></p></div></body></html>");
  request->send(200, "text/html",temp);
}

void HSD(AsyncWebServerRequest *request) {
  int sensor=analogRead(A0);
  String json = "{\"vr\":";
  json += sensor;
  json +="}";
  request->send(200, "application/json", json);
  }

void setup(){
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println(WiFi.localIP());
 
   server.on("/", handleRoot);
   server.on("/sensors", HSD);
   
  server.on("/get", [](AsyncWebServerRequest *request){
    request->send(200, "text/html", "<h1>Hello world</h1>");
  });
  
  server.begin();
}
 
void loop(){
}

