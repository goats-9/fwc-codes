#include <Arduino.h>

// Define pins used on Arduino
#define PIN_a 2
#define PIN_b 3
#define PIN_c 4
#define PIN_d 5
#define PIN_e 6
#define PIN_f 7
#define PIN_g 8
#define PIN_A 9
#define PIN_B 10
#define PIN_C 11
#define PIN_D 12

// Setup: Code to be executed once at the start here
void setup() {
    // Set pin modes to INPUT and OUTPUT as appropriate
    pinMode(PIN_a, OUTPUT);
    pinMode(PIN_b, OUTPUT);
    pinMode(PIN_c, OUTPUT);
    pinMode(PIN_d, OUTPUT);
    pinMode(PIN_e, OUTPUT);
    pinMode(PIN_f, OUTPUT);
    pinMode(PIN_g, OUTPUT);
    pinMode(PIN_A, INPUT);  
    pinMode(PIN_B, INPUT);
    pinMode(PIN_C, INPUT);
    pinMode(PIN_D, INPUT);
}

// Loop: code that executes forever goes here
void loop() {
    int A, B, C, D, a, b, c, d, e, f, g;
    // Read input pins
    A = digitalRead(PIN_A);
    B = digitalRead(PIN_B);
    C = digitalRead(PIN_C);
    D = digitalRead(PIN_D);
	// Boolean functions for each pin
	a = (C&&!B&&!A)||(!D&&!C&&!B&&A);
	b = (C&&!B&&A)||(C&&B&&!A);
	c = !C&&B&&!A;
	d = (!D&&!C&&!B&&A)||(C&&!B&&!A)||(C&&B&&A);
	e = (!B||A)&&(C||B||A);
	f = (!D&&!C&&A)||(!C&&B)||(B&&A);
	g = (!D&&!C&&!B)||(C&&B&&A);
	// Write to pins
	digitalWrite(PIN_a, a);
	digitalWrite(PIN_b, b);
	digitalWrite(PIN_c, c);
	digitalWrite(PIN_d, d);
	digitalWrite(PIN_e, e);
	digitalWrite(PIN_f, f);
	digitalWrite(PIN_g, g);
}
