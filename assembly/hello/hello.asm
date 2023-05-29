.include "../m328Pdef.inc"
	;pinMode(13, OUTPUT);
	ldi r16, 0b00100000
	out DDRB, r16
	;digitalWrite(13, HIGH);
	ldi r17, 0b00000000
	out PortB, r17

Loop:
	rjmp Loop
