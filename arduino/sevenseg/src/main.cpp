#include <Arduino.h>

// Digital pins used in the Arduino
#define PIN_a 2
#define PIN_b 3
#define PIN_c 4
#define PIN_d 5
#define PIN_e 6
#define PIN_f 7
#define PIN_g 8

void disp_sevenseg(int a, int b, int c, int d, int e, int f, int g) {
	digitalWrite(PIN_a, a);
	digitalWrite(PIN_b, b);
	digitalWrite(PIN_c, c);
	digitalWrite(PIN_d, d);
	digitalWrite(PIN_e, e);
	digitalWrite(PIN_f, f);
	digitalWrite(PIN_g, g);
}

// Setup: Code to be executed once at the start here
void setup() {
    // Set pin modes to OUTPUT
    pinMode(PIN_a, OUTPUT);  
    pinMode(PIN_b, OUTPUT);
    pinMode(PIN_c, OUTPUT);
    pinMode(PIN_d, OUTPUT);
    pinMode(PIN_e, OUTPUT);
    pinMode(PIN_f, OUTPUT);
    pinMode(PIN_g, OUTPUT);            
}

void loop() {
	// Call the display function
	disp(0,0,0,0,0,0,1);
}
