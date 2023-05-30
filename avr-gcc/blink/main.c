#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	// Set pin 13 on Arduino as
	// output pin.
	DDRB |= ((1<<DDB5));
	// Toggle the LED every one second.
	while (1) {
		PORTB ^= ((1<<PB5));
		_delay_ms(1000);
	}
	return 0;
}
