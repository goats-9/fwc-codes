#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <EloquentTinyML.h>
#include <eloquent_tinyml/tensorflow.h>
#include <math.h>
#include <esp32PWMUtilities.h>
#include "gesture_model.h"
#include "credentials.h"

#define NUM_SAMPLES 20
#define NUM_INPUTS 3*NUM_SAMPLES
#define NUM_OUTPUTS 5
#define TENSOR_ARENA_SIZE 4096

WiFiClient client;
HTTPClient ugv;
Eloquent::TinyML::TensorFlow::TensorFlow<NUM_INPUTS, NUM_OUTPUTS, TENSOR_ARENA_SIZE> ml;
StaticJsonDocument<6144> doc;
Motor Motor1;
Motor Motor2;
String ROLL = "r";
String PITCH = "p";
String YAW = "y"; 

int k, prev_id;

void setup() {
    Serial.begin(115200);
    k = 0, prev_id = 0;
    Motor1.attach(14, 16, 17);
    Motor2.attach(15, 18, 19);
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
    ml.begin(ugv_model_tflite);
    while (!ml.isOk()) { 
        Serial.print("ERROR: ");
        Serial.println(ml.getErrorMessage());
        delay(2000);
    }
    ugv.useHTTP10(true);
    ugv.begin(client, ugvURL);
} 

void lock(int del) {
  delay(del);
  Motor1.lockMotor();
  Motor2.lockMotor();
  delay(1000);
}

// Move in forward direction
void front() {
  Motor1.moveMotor(127);
  Motor2.moveMotor(127);
  lock(300);
}

// Move in backward direction
void back() {
  Motor1.moveMotor(-127);
  Motor2.moveMotor(-127);
  lock(300);
}

// Rotate 90 degrees clockwise
void right() {
  Motor1.moveMotor(127);
  Motor2.moveMotor(-127);
  lock(190);
}

// Rotate 90 degrees anticlockwise
void left() {
  Motor1.moveMotor(-127);
  Motor2.moveMotor(127);
  lock(190);
}

void action(int pred) { 
    switch (pred) {
        case 0:
            front();
            return;
        case 1:
            right();
            return;
        case 2:
            back();
            return;
        case 3:
            left();
        default:
            return;
    }
}

void loop() {
    /*
     * 1. Get input from webserver.
     * 2. Handle input from webserver.
     */
    ugv.addHeader("Content-Type", "application/json");
    int httpResponseCode, id;
    while (1) {
        httpResponseCode = ugv.GET();
        deserializeJson(doc, ugv.getStream());
        id = doc["id"];
        if (id > prev_id) {
            prev_id = id;
            break;
        }
        delay(100);
    }
    float input[NUM_INPUTS];
    for (int i = 0; i < NUM_SAMPLES; i++) { 
        input[3*i] = doc[ROLL+i];
        input[3*i + 1] = doc[PITCH+i];
        input[3*i + 2] = doc[YAW+i];
    }
    float output[NUM_OUTPUTS];
    ml.predict(input, output);
    Serial.print("output:");
    for (float val : output) {
      Serial.print(" ");
      Serial.print(val);
    }
    Serial.println();
    int pred = -1;
    float mx = -1000;
    for (int i = 0; i < NUM_OUTPUTS; i++) if (mx < output[i]) mx = output[i], pred = i;
    Serial.print("Prediction = ");
    Serial.println(pred);
    action(pred);
    delay(1000);
}
