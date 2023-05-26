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

// Implement BCH logic
void disp_bch(int digit) {
    int A, B, C, D;
    // Get binary digits
    A = digit & (1<<3);
    B = digit & (1<<2);
    C = digit & (1<<1);
    D = digit & (1<<0);
    // Condition to display segment 'a'
    if ((!B&&!D)||(!A&&C)||(B&&C)||(A&&!D)||(!A&&B&&D)||(A&&!B&&!C))
        digitalWrite(PIN_a, LOW);
    else digitalWrite(PIN_a, HIGH);
    // Condition to display segment 'b'
    if ((!A&&!B)||(!B&&!D)||(!A&&!C&&!D)||(!A&&C&&D)||(A&&!C&&D))
        digitalWrite(PIN_b, LOW);
    else digitalWrite(PIN_b, HIGH);
    // Condition to display segment 'c'
    if ((!A&&!C)||(!A&&D)||(!C&&D)||(!A&&B)||(A&&!B))
        digitalWrite(PIN_c, LOW);
    else digitalWrite(PIN_c, HIGH);
    // Condition to display segment 'd'
    if ((A&&!C)||(!A&&!B&&!D)||(!B&&C&&D)||(B&&!C&&D)||(B&&C&&!D))
        digitalWrite(PIN_d, LOW);
    else digitalWrite(PIN_d, HIGH);
    // Condition to display segment 'e'
    if ((!B&&!D)||(C&&!D)||(A&&B)||(A&&C))
        digitalWrite(PIN_e, LOW);
    else digitalWrite(PIN_e, HIGH);
    // Condition to display segment 'f'
    if ((!C&&!D)||(B&&!D)||(A&&!B)||(A&&C)||(!A&&B&&!C))
        digitalWrite(PIN_f, LOW);
    else digitalWrite(PIN_f, HIGH);
    // Condition to display segment 'g'
    if ((!B&&C)||(C&&!D)||(A&&!B)||(A&&D)||(!A&&B&&!C))
        digitalWrite(PIN_g, LOW);
    else digitalWrite(PIN_g, HIGH);
}

// Loop: code that executes forever goes here
void loop() {
    int A, B, C, D;
    // Read input pins
    A = digitalRead(PIN_A);
    B = digitalRead(PIN_B);
    C = digitalRead(PIN_C);
    D = digitalRead(PIN_D);
    // Get the input digit
    int digit = (A<<3) | (B<<2) | (C<<1) | (D<<0);
    // Display the hexadecimal digit
    disp_bch(digit);
}
