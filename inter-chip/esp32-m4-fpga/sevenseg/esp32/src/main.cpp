#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "esp32_eoss3_spi.h"
#include "credentials.h"

#define SW_MB_1 0x40005110

AsyncWebServer server(80);

const char* PARAM_DIGIT = "digit";
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>Vaman LED Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head>
  <body>
  <h1>Seven-Segment Display</h1>
  <form action="/sevenseg" method="POST">
    Enter digit: <input type="number" min="0" max="9" step="1" name="state"><br>
    <input type="submit" value="Submit">
  </form>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  esp32_eoss3_spi_init();
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(2000);
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/sevenseg", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/sevenseg", HTTP_POST, [](AsyncWebServerRequest *request) {
    if (request->hasParam(PARAM_DIGIT)) {
        uint32_t digit = request->getParam(PARAM_DIGIT)->value().toInt();
        esp32_eoss3_spi_ahb_write(SW_MB_1, (uint8_t *)&digit, 4);
    }
    request->send(200, "text/html", index_html);
  });

  server.onNotFound(notFound);
  server.begin();
}

void loop() {}
