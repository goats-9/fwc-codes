#include <Arduino.h>

// Define pins used on Arduino
#define PIN_A 2
#define PIN_B 3
#define PIN_C 4
#define PIN_D 5
#define PIN_W 6
#define PIN_X 7
#define PIN_Y 8
#define PIN_Z 9

// Setup: Code to be executed once at the start here
void setup() {
    // Set pin modes to INPUT and OUTPUT as appropriate
    pinMode(PIN_A, OUTPUT);
    pinMode(PIN_B, OUTPUT);
    pinMode(PIN_C, OUTPUT);
    pinMode(PIN_D, OUTPUT);
    pinMode(PIN_W, INPUT);
    pinMode(PIN_X, INPUT);
    pinMode(PIN_Y, INPUT);
    pinMode(PIN_Z, INPUT);
}

void loop() {
    int W, X, Y, Z, A, B, C, D;
    // Read input pins
    W = digitalRead(PIN_W);
    X = digitalRead(PIN_X);
    Y = digitalRead(PIN_Y);
    Z = digitalRead(PIN_Z);
	// Get output as functions of inputs
    D = (Z&&!X&&!W)||(Y&&X&&W);
    C = (!Y&&X&&W)||(Y&&!X)||(Y&&!W);
    B = (!Z&&!X&&W)||(X&&!W);
    A = !W;
	/* Alternatively, do this:
	   // Get the digit
	   int digit = (Z<<3) | (Y<<2) | (X<<1) | (W<<0);
	   // Increment the digit
	   digit = (digit + 1) % 10;
	   // Get new bits of incremented digit
	   A = digit & (1<<0);
	   B = digit & (1<<1);
	   C = digit & (1<<2);
	   D = digit & (1<<3);
	*/
	// Write to 7447
    digitalWrite(PIN_A, A);
    digitalWrite(PIN_B, B);
    digitalWrite(PIN_C, C);
    digitalWrite(PIN_D, D);
}
