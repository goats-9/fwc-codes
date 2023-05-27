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
    // Start the decade counter at 0
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(PIN_A_1D_1, LOW);
    digitalWrite(PIN_B_2D_1, LOW);
    digitalWrite(PIN_C_1D_2, LOW);
    digitalWrite(PIN_D_2D_2, LOW);
    delay(1000);
}

// Loop: code that executes forever goes here
void loop() {
    // Feedback inputs
    int a, b, c, d;
    // Outputs to 7447
    int A, B, C, D;
    // Falling CLK edge: read inputs here
    digitalWrite(LED_BUILTIN, LOW);
    // Read input pins
    a = digitalRead(PIN_1Q_1);
    b = digitalRead(PIN_2Q_1);
    c = digitalRead(PIN_1Q_2);
    d = digitalRead(PIN_2Q_2);
    // Rising CLK edge: write incremented digit here
    digitalWrite(LED_BUILTIN, HIGH);
    D = (d&&!b&&!a)||(c&&b&&a);
    C = (!c&&b&&a)||(c&&!b)||(c&&!a);
    B = (!d&&!b&&a)||(b&&!a);
    A = !a;
	// Optionally, do this instead of the K-map approach:
	// int digit = (d<<3) | (c<<2) | (b<<1) | (a<<0);
	// digit = (digit + 1) % 10;
	// A = digit & (1<<0);
	// B = digit & (1<<1);
	// C = digit & (1<<2);
	// D = digit & (1<<3);
    digitalWrite(PIN_A_1D_1, A);
    digitalWrite(PIN_B_2D_1, B);
    digitalWrite(PIN_C_1D_2, C);
    digitalWrite(PIN_D_2D_2, D);
    delay(1000);
}
