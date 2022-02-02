#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(443);

const char* ssid = "your-ssid";
const char* password = "your-password";

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

int fileRequest(void * arg, const char *filename, uint8_t **buf) {
  Serial.printf("Reading file: %s\n", filename);
  if(SPIFFS.begin()) {
    Serial.println("SPIFFS has started");
  }
  File file = SPIFFS.open(filename, "r");
  if(file){
    Serial.printf("File found: %s\n", filename);
    size_t size = file.size();
    uint8_t * nbuf = (uint8_t*)malloc(size);
    if(nbuf){
      size = file.read(nbuf, size);
      file.close();
      *buf = nbuf;
      return size;
    }
    file.close();
  } else {
    Serial.println("File not found!");
    *buf = 0;
    return 0;
  }
}

void handleTest(AsyncWebServerRequest *request) {
  String message = "";
  
  if(request->hasParam("message")) {
    message = request->getParam("message")->value();
  }
  
  request->send(200, "text/plain", "Param: " + message);
}

void setup() {

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
    
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Hello, world");
  });

  server.on("/test", HTTP_GET, handleTest);

  server.onNotFound(notFound);
  server.onSslFileRequest(fileRequest, NULL);

  Serial.println( "Certs validation" );
  server.beginSecure("/Cert.pem", "/Key.pem", NULL);
  Serial.println( "HTTPs server has started" );
}

void loop() {
}
