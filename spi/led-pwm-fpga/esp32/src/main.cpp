#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "esp32_eoss3_spi.h"
#include "credentials.h"

#define MISC_BASE_ADDR 0x40005000
#define SW_MB_1 MISC_BASE_ADDR + 0x110
#define SW_MB_2 MISC_BASE_ADDR + 0x114
#define FPGA_ONION_PWMCTRL_REG_ADDR_PWM_2_CONFIG 0x40022008

AsyncWebServer server(80);

const char* PARAM_PWM = "pwm";
uint32_t pwm;

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>Vaman PWM Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/get" target="hidden-form">
    Enter pwm: <input type="number" min="0" max="255" step="1" name="pwm">
    <input type="submit" value="Submit">
  </form>
  <iframe style="display:none" name="hidden-form"></iframe>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

String processor(const String& var){
  if (var == "pwm") return String(pwm);
  else return String(-1);
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

  server.on("/pwm", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    if (request->hasParam(PARAM_PWM)) {  
      pwm = request->getParam(PARAM_PWM)->value().toInt();
      pwm |= (1<<31);
      Serial.println(pwm);
      esp32_eoss3_spi_ahb_write(FPGA_ONION_PWMCTRL_REG_ADDR_PWM_2_CONFIG, (uint8_t *)&pwm, 4);
    }
    request->send(200, "text/plain", "Redirect");
  });
  server.onNotFound(notFound);
  server.begin();
}

void loop() {}
