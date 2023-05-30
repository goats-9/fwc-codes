#include <avr/io.h>

int main(void) {
	// Set PD2-PD5 (pins 2-5) on 
	// the Arduino as output pins.
	DDRD = 0b00111100;
	// Set PB2-PB5 (pins 10-13) on 
	// the Arduino as output pins.
	DDRB = 0b00111100;
	while (1) { 
		// Get input digit, right shift by 2
		int digit = (PINB>>2)&((1<<4)-1);
		// Increment the digit
		digit = (digit + 1)%10;
		// Write to output
		PORTD = digit << 2;
	}
	return 0;
}
