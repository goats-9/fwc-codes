#include <WiFi.h>
#include <ArduinoOTA.h>
#include "credentials.h"

void OTAsetup() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) delay(1000);
    ArduinoOTA.begin();
}

void OTAloop() {
    ArduinoOTA.handle();
}

void setup(){
    OTAsetup();
    pinMode(2, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
}

void loop() {
    OTAloop();
    digitalWrite(2, HIGH);   
    digitalWrite(4, HIGH);   
    digitalWrite(5, HIGH);   
    delay(1000);
    digitalWrite(2, LOW);   
    digitalWrite(4, LOW);   
    digitalWrite(5, LOW);   
    delay(1000);
}
