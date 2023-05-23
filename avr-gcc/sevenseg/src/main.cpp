#include <Arduino.h>

// Segments for each digit
int seg[10][7] = 
{ 
    {1,1,1,1,1,1,0},
    {0,1,1,0,0,0,0},
    {1,1,0,1,1,0,1},
    {1,1,1,1,0,0,1},
    {0,1,1,0,0,1,1},
    {1,0,1,1,0,1,1},
    {1,0,1,1,1,1,1},
    {1,1,1,0,0,0,0},
    {1,1,1,1,1,1,1},
    {1,1,1,1,0,1,1},
};

// Setup: Code to be executed once at the start here
void setup() {
    // Set pin modes to OUTPUT
    pinMode(2, OUTPUT);  
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);            
}

void loop() {
    // Display each digit with a 2 second delay.
    for (int i = 0; i < 10; i++) {
        // Go through the segment array
        for (int j = 0; j < 7; j++)
            digitalWrite(j+2, seg[i][j]);
        delay(2000);
    }
}
