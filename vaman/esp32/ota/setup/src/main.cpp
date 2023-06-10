#include <WiFi.h>
#include <ArduinoOTA.h>

/* The credentials.h file has the following format:
 *
 * const char *ssid = "SSID";
 * const char *password = "PASSWORD";
 *
 * This is to store credentials securely and ensure
 * that they are not exposed on a git repo.
 */
#include "credentials.h"

void OTAsetup() {
    // Set up WiFi connection
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    // Wait for WiFi connection
    while (WiFi.status() != WL_CONNECTED) delay(1000);
    ArduinoOTA.begin();
}

void OTAloop() {
  ArduinoOTA.handle();
}

void setup(){
  OTAsetup();
}

void loop() {
  OTAloop();
  // Require some delay for OTA to work
  delay(10);
}
