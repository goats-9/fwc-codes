#include <avr/io.h>

int main(void) {
	// Set PD2-PD7 (pins 2-7) on 
	// the Arduino as output pins.
	DDRD |= 0xFC;
	// Set PB0 (pin 8) on the Arduino
	// as an output pin.
	DDRB |= ((1 << DDB0));
	// Write appropriate number to
	// seven segment display
	PORTD = 0b11100000;
	PORTB = ((1 << PB0));
	// Infinite loop to prevent 
	// termination of the program.
	while (1);
	return 0;
}
