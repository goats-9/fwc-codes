.include "../m328Pdef.inc"

setup:
	;Set PB5 as an output pin.
	;This corresponds to pin 13
	;in the Arduino.
	sbi DDRB, 5
	;Define the prescaler in TC0 
	;Control Register B. Setting
	;bits 2 to 0 to 101 gives a
	;prescaler of 1024
	ldi r16, 0b00000101
	out TCCR0B, r16
	;r18 will be used to write to
	;the LED beside pin 13. 
	;Initially LED should not blink.
	clr r18
	;r20 will be XOR-ed with r18 to
	;toggle the LED.
	ldi r20, 0b00100000
	;r17 is used to check OCF0A bit
	;in TIFR0 register.
	ldi r17, 0b00000010

loop:
	;Toggle LED
	eor r18, r20
	;Write new status to LED
	out PORTB, r18
	;r19 contains the number of times
	;the loop should be run to get a
	;1 second delay
	ldi r19, 0b01000000
	;Call the PAUSE routine
	rcall pause
	rjmp loop

;Pause routine using timer.
pause:
	;Check whether OCF0A is set in TIFR0.
	;If so, then 256 cycles have passed.
	;Else, go back to pause and start over.
	;TCNT0 <- counter
	;OCF0A = TIFR0[1] = 0, when TCNT0 = OCR0A
	in r16, TIFR0
	;r17 = 0b00000010
	and r16, r17
	breq pause
	;Clear OCR0A flag
	out TIFR0, r17
	dec r19
	brne pause
	ret
