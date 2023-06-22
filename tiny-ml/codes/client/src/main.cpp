#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <EloquentTinyML.h>
#include <eloquent_tinyml/tensorflow.h>
#include <math.h>

#include "gesture_model.h"
#include "credentials.h"

#define PIN_CHOP 18
#define PIN_WRIST 21
#define ACC_THR 20.0
#define NUM_GESTURES 10
#define NUM_INPUTS 6*NUM_GESTURES
#define NUM_OUTPUTS 1
#define TENSOR_ARENA_SIZE 4096

WiFiClient client;
HTTPClient gesture;
Eloquent::TinyML::TensorFlow::TensorFlow<NUM_INPUTS, NUM_OUTPUTS, TENSOR_ARENA_SIZE> ml;

int prev_id, led_chop, led_wrist, k, fl;

void setup() {
    Serial.begin(115200);
    k = 0, fl = 0;
    /*
     * 1. Establish WiFi connection.
     */
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(1000);
    }
    Serial.println(WiFi.localIP());
    ml.begin(gesture_model_tflite);
    while (!ml.isOk()) { 
        Serial.print("ERROR: ");
        Serial.println(ml.getErrorMessage());
        delay(2000);
    }
    gesture.useHTTP10(true);
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
    int httpResponseCode, id;
    // Wait for new gesture
    while (1) {
        httpResponseCode = gesture.GET();
        deserializeJson(doc, gesture.getStream());
        id = doc["messageId"];
        if (id > prev_id) {
            prev_id = id;
            break;
        }
        delay(100);
    }
    JsonArray arr = doc["payload"].as<JsonArray>();
    int size = arr.size();
    Serial.print("Size of readings = ");
    Serial.println(size);
    float input[NUM_INPUTS];
    int i = 0;
    while (i < size) {
        String name = doc["payload"][i]["name"];
        float vx, vy, vz;
        vx = doc["payload"][i]["values"]["x"];
        vy = doc["payload"][i]["values"]["y"];
        vz = doc["payload"][i]["values"]["z"];
        Serial.print("vx = ");
        Serial.print(vx);
        Serial.print(", vy = ");
        Serial.print(vy);
        Serial.print(", vz = ");
        Serial.println(vz);
        if (fl == 0)
            if (name == "accelerometer")
                if (abs(vx) + abs(vy) + abs(vz) >= ACC_THR) {
                    Serial.println("Threshold");
                    input[0] = vx, input[1] = vy, input[2] = vz, fl = 1;
                }
        else {
            if (name == "accelerometer")
                input[6*k] = vx, input[6*k + 1] = vy, input[6*k + 2] = vz;
            else if (name == "gyroscope")
                input[6*k + 3] = vx, input[6*k + 4] = vy, input[6*k + 5] = vz, k++;
        }
        i++;
        if (k == NUM_GESTURES)
            break;
    }
    Serial.print("k = ");
    Serial.println(k);
    Serial.print("fl = ");
    Serial.println(fl);
    if (k == NUM_GESTURES) {
        float pred = ml.predict(input);
        Serial.print("Prediction = ");
        Serial.println(pred);
        action(pred);
        k = 0, fl = 0;
    }
    delay(1000);
}
