#include <avr/io.h>

int main(void) {
	// Set PD2-PD7 (pins 2-7) on 
	// the Arduino as output pins.
	DDRD = 0b11111100;
	// Set PB2-PB5 (pins 10-13) on 
	// the Arduino as input pins and
	// PB0 (pin 8) as an output pin.
	DDRB = 0b11000011;
	int a, b, c, d, e, f, g, A, B, C, D;
	int portd, portb;
	while (1) {
		// Get input binary digits
		A = PINB & (1<<PB2);
		B = PINB & (1<<PB3);
		C = PINB & (1<<PB4);
		D = PINB & (1<<PB5);
		// Evaluate appropriate boolean
		// expressions.
		a = (!D&&!C&&!B&&!A)||(!C&&B&&A);
		b = (C&&!B);
		c = (!D&&!C&&!B&&A);
		d = (!D&&!C&&!B&&!A)||(!C&&B&&A)||(C&&B&&!A);
		e = !A||(!C&&B&&A);
		f = (!D&&!C&&!B)||(!D&&B&&!A);
		g = (!D&&!C&&!B&&!A)||(D&&A)||(C&&B&&!A);
		// Set the outputs
		portd = (a<<PD2);
		portd |= (b<<PD3);
		portd |= (c<<PD4);
		portd |= (d<<PD5);
		portd |= (e<<PD6);
		portd |= (f<<PD7);
		portb = (g<<PB0);
		PORTD = portd, PORTB = portb;
	}
	return 0;
}
