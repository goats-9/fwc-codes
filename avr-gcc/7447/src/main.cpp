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
    Serial.begin(9600);
}

// Display (digit + 1) modulo 10 using the 7447
void disp_7447(int digit) {
    int a, b, c, d;
    // Get each bit of the digit
    a = digit & (1<<0);
    b = digit & (1<<1);
    c = digit & (1<<2);
    d = digit & (1<<3);
    Serial.print(d);
    Serial.print(c);
    Serial.print(b);
    Serial.println(a);
    // Write to 7447 input pins
    digitalWrite(PIN_A, a?LOW:HIGH);
    digitalWrite(PIN_B, b?LOW:HIGH);
    digitalWrite(PIN_C, c?LOW:HIGH);
    digitalWrite(PIN_D, d?LOW:HIGH);
}

void loop() {
    int w, x, y, z;
    // Read input pins
    w = digitalRead(PIN_W);
    x = digitalRead(PIN_X);
    y = digitalRead(PIN_Y);
    z = digitalRead(PIN_Z);
    // Get the input digit
    int digit = (z<<3) | (y<<2) | (x<<1) | (w<<0);
    Serial.print(digit);
    Serial.print(": ");
    // Increment the digit modulo 10
    digit = (digit + 1) % 10;
    // Display the resulting digit
    disp_7447(digit);
    // Persist for 1 second
    delay(2000);
}
