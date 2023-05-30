.include "../m328Pdef.inc"
	;pinMode(13, OUTPUT);
	ldi r16, 0b00100000
	out DDRB, r16
	;digitalWrite(13, HIGH/LOW);
	ldi r17, 0b00100000
	out PORTB, r17

Loop:
	rjmp Loop
