.include "../m328Pdef.inc"

	;Configuring PD2 to PD7 as output
	;Equivalent to pinMode(i, OUTPUT);
	;where 2 <= i <= 7
	ldi r16, 0b11111100
	out DDRD, r16
	;Configuring PB0 as output
	;Equivalent to pinMode(8, OUTPUT);
	ldi r16, 0b00000001
	out DDRB, r16
	;Writing the number 2 on the 
	;seven segment display
	;Set states of PD2 to PD7
	ldi r17, 0b10010000
	out PortD, r17
	;Set state of PB0
	ldi r17, 0b00000000
	out PortB, r17

Loop:
	rjmp Loop

