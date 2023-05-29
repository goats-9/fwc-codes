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
	;Write outputs to output pins
	out PORTD, r17
	;Loop indefinitely
	rjmp loop
