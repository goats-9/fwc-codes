#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <EloquentTinyML.h>
#include <eloquent_tinyml/tensorflow.h>
#include <math.h>

#include "gesture_model.h"
#include "credentials.h"

#define PIN_RIGHT 18
#define PIN_TAP 21
#define ACC_THR 30.0
#define NUM_SAMPLES 40
#define NUM_INPUTS 6*NUM_SAMPLES
#define NUM_OUTPUTS 1
#define TENSOR_ARENA_SIZE 4096

String AX = "ax";
String AY = "ay";
String AZ = "az";
String GX = "gx";
String GY = "gy";
String GZ = "gz";

WiFiClient client;
HTTPClient gesture;
Eloquent::TinyML::TensorFlow::TensorFlow<NUM_INPUTS, NUM_OUTPUTS, TENSOR_ARENA_SIZE> ml;

int prev_id, led_right, led_tap;
StaticJsonDocument<6144> doc;

void setup() {
    Serial.begin(115200);
    /*
     * 1. Establish WiFi connection.
     */
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(2000);
    }
    ml.begin(gesture_model_tflite);
    while (!ml.isOk()) { 
        Serial.print("ERROR: ");
        Serial.println(ml.getErrorMessage());
        delay(2000);
    }
    gesture.useHTTP10(true);
    gesture.begin(client, gestureURL);
    prev_id = 0, led_right = 0, led_tap = 0;
    pinMode(PIN_RIGHT, OUTPUT);
    pinMode(PIN_TAP, OUTPUT);
} 

void action(float pred) { 
    if (pred < 0.1) {
        led_right ^= 1;
        digitalWrite(PIN_RIGHT, led_right);
    } else if (pred > 0.9) { 
        led_tap ^= 1;
        digitalWrite(PIN_TAP, led_tap);
    }
}

void loop() {
    /*
     * 1. Get input from webserver.
     * 2. Handle input from webserver.
     */
    gesture.addHeader("Content-Type", "application/json");
    int httpResponseCode, id;
    // Wait for new gesture
    while (1) {
        httpResponseCode = gesture.GET();
        deserializeJson(doc, gesture.getStream());
        id = doc["id"];
        if (id > prev_id) {
            prev_id = id;
            break;
        }
        delay(100);
    }
    float input[NUM_INPUTS];
    for (int i = 0; i < NUM_SAMPLES; i++) { 
        input[6*i] = doc[AX+i];
        input[6*i + 1] = doc[AY+i];
        input[6*i + 2] = doc[AZ+i];
        input[6*i + 3] = doc[GX+i];
        input[6*i + 4] = doc[GY+i];
        input[6*i + 5] = doc[GZ+i];
    }
    Serial.print("Prediction = ");
    float pred = ml.predict(input);
    Serial.println(pred);
    action(pred);
    delay(1000);
}
