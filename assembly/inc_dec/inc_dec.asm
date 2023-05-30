.include "../m328Pdef.inc"

setup:
	;Set pins PB2-PB5 as input pins.
	;This corresponds to pins 10-13
	;on the Arduino.
	ldi r17, 0b11000011
	out DDRB, r17
	;Set pins PD2-PD5 as output pins.
	;This corresponds to pins 2-5 on
	;the Arduino.
	ldi r16, 0b00111100
	out DDRD, r16

loop:
	;Get input from input pins
	in r17, PINB
	;Increment the input
	;Note that we add 4 since the 
	;digit is present from bit 2
	ldi r18, 0b00000100
	adc r17, r18
	;If digit is 10 or more, subtract
	cpi r17, 0b00101000
	brlt nosub
	subi r17, 0b00101000
;skip subtraction
nosub:
	;Write outputs to output pins
	out PORTD, r17
	;Loop indefinitely
	rjmp loop
