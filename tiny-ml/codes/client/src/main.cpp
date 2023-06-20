#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "EloquentTinyML.h"
#include "gesture_model.h"
#include "credentials.h"

#define PIN_CHOP 18
#define PIN_WRIST 21

#define NUM_INPUTS 240
#define NUM_OUTPUTS 1
#define TENSOR_ARENA_SIZE 4096

WiFiClient client;
HTTPClient gesture;
Eloquent::TinyML::TfLite<NUM_INPUTS, NUM_OUTPUTS, TENSOR_ARENA_SIZE> ml;

int prev_id, led_chop, led_wrist;

void setup() {
    Serial.begin(115200);
    ml.begin(gesture_model_tflite);
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
    prev_id = 0, led_chop = 0, led_wrist = 0;
    pinMode(PIN_CHOP, OUTPUT);
    pinMode(PIN_WRIST, OUTPUT);
} 

void action(float pred) { 
    if (pred < 0.1) {
        led_chop ^= 1;
        digitalWrite(PIN_CHOP, led_chop);
    } else if (pred > 0.9) { 
        led_wrist ^= 1;
        digitalWrite(PIN_WRIST, led_wrist);
    }
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
    float input[NUM_INPUTS];
    for (int i = 0; i < 40; i++) { 
        input[6*i+0] = doc["ax"+i];
        input[6*i+1] = doc["ay"+i];
        input[6*i+2] = doc["az"+i];
        input[6*i+3] = doc["gx"+i];
        input[6*i+4] = doc["gy"+i];
        input[6*i+5] = doc["gz"+i];
    }
    float pred = ml.predict(input);
    Serial.println(pred);
    action(pred);
    delay(1000);
}
