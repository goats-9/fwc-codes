.include "../m328Pdef.inc"

setup:
	
	;Set PB5 as an output pin.
	;This corresponds to pin 13
	;in the Arduino.
	sbi DDRB, 5
	;Define the prescaler in TC0 
	;Control Register B. Setting
	;last 3 bits to 101 gives a
	;prescaler of 1024
	ldi r16, 0b00000101
	out TCCR0B, r16
	;r18 will be used to write to
	;the LED beside pin 13. 
	;Initially LED should not blink.
	clr r18
	;r20 will be XOR-ed with r18 to
	;toggle the LED
	ldi r20, 0b00100000

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

;pause routine waits till TIFR0 has 
;bit 1 set.
pause:

;loop_pause routine returns after
;executing pause 64 times.
loop_pause:
	;TIFR0 is the Timer Interrupt
	;Flag Register. When the value
	;in counter (TCNT0) matches
	;Output Compare Register A (OCR0A)
	;TIFR0 has bit 1 set.
	in r16, TIFR0
	;To check if bit 1 is set in TIFR0.
	ldi r17, 0b00000010
	and r16, r17
	;If equal, the bit 1 is set, and
	;start over.
	breq pause
	;Set TIFR0 flag
	out TIFR0, r17
	;Update loop and check.
	dec r19
	brne loop_pause
	ret
