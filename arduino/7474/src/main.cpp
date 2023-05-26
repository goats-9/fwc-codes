#include <Arduino.h>

// Define pins used on Arduino
#define PIN_A_1D_1 2
#define PIN_B_2D_1 3
#define PIN_C_1D_2 4
#define PIN_D_2D_2 5
#define PIN_1Q_1 6
#define PIN_2Q_1 7
#define PIN_1Q_2 8
#define PIN_2Q_2 9
// LED_BUILTIN is a predefined macro
// in Arduino.h for digital pin 13.

// Setup: Code to be executed once at the start here
void setup() {
    // Set pin modes to INPUT and OUTPUT as appropriate
    pinMode(PIN_A_1D_1, OUTPUT);
    pinMode(PIN_B_2D_1, OUTPUT);
    pinMode(PIN_C_1D_2, OUTPUT);
    pinMode(PIN_D_2D_2, OUTPUT);
    pinMode(PIN_1Q_1, INPUT);
    pinMode(PIN_2Q_1, INPUT);
    pinMode(PIN_1Q_2, INPUT);
    pinMode(PIN_2Q_2, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
}

void disp_7447(int digit) { 
    int A, B, C, D;
    // Get binary digits
    A = digit & (1<<0);
    B = digit & (1<<1);
    C = digit & (1<<2);
    D = digit & (1<<3);
    // Write to 7447 and 7474
    digitalWrite(PIN_A_1D_1, A?HIGH:LOW);
    digitalWrite(PIN_B_2D_1, B?HIGH:LOW);
    digitalWrite(PIN_C_1D_2, C?HIGH:LOW);
    digitalWrite(PIN_D_2D_2, D?HIGH:LOW);
}

// Loop: code that executes forever goes here
void loop() {
    int A, B, C, D;
    // Falling CLK edge: read inputs here
    digitalWrite(LED_BUILTIN, LOW);
    // Read input pins
    A = digitalRead(PIN_1Q_1);
    B = digitalRead(PIN_2Q_1);
    C = digitalRead(PIN_1Q_2);
    D = digitalRead(PIN_2Q_2);
    // Get the input digit
    int digit = (D<<3) | (C<<2) | (B<<1) | (A<<0);
    // Increment the digit modulo 10
    digit = (digit + 1) % 10;
    // Rising CLK edge: write incremented digit here
    digitalWrite(LED_BUILTIN, HIGH);
    // Display the digit
    disp_7447(digit);
    delay(1000);
}
