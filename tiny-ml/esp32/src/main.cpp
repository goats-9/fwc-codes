#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "EloquentTinyML.h"
#include "gesture_model.h"
#include "credentials.h"

#define NUM_INPUTS 120
#define NUM_OUTPUTS 1
#define TENSOR_ARENA_SIZE 4096

WiFiClient client;
HTTPClient gesture;
Eloquent::TinyML::TfLite<NUM_INPUTS, NUM_OUTPUTS, TENSOR_ARENA_SIZE> ml(gesture_model_tflite);

int prev_id;

void setup() {
    Serial.begin(115200);
    /*
     * 1. Establish WiFi connection.
     */
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(1000);
    }
    gesture.begin(client, gestureURL);
    prev_id = 0;
} 

void loop() {
    /*
     * 1. Get input from webserver.
     * 2. Handle input from webserver.
     */
    gesture.addHeader("Content-Type", "application/json");
    StaticJsonDocument<4096> doc;
    // Wait for new gesture
    while (1) {
        int httpResponseCode = gesture.GET();
        String responseBody = gesture.getString();
        deserializeJson(doc, responseBody);
        if (doc["id"] > prev_id) {
            prev_id = doc["id"];
            break;
        }
    }
    float input[120];
    for (int i = 0; i < 20; i++) { 
        input[6*i+0] = doc["ax"+i];
        input[6*i+1] = doc["ay"+i];
        input[6*i+2] = doc["az"+i];
        input[6*i+3] = doc["gx"+i];
        input[6*i+4] = doc["gy"+i];
        input[6*i+5] = doc["gz"+i];
    }
    float pred = ml.predict(input);
    Serial.println(pred);
    delay(1000);
}
