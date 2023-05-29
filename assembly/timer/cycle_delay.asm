.include "../m328Pdef.inc"

setup:
	;Set PB5 as output pin. This
	;corresponds to pin 13 on the
	;Arduino.
	ldi r16, 0b00100000
	out DDRB, r16
	ldi r16, 0
	;Clear status register
	out SREG, r16
	;RAMEND refers to the last address
	;corresponding to RAM.
	;Set SPH and SPL to start the stack 
	;from topmost address.
	ldi r16, low(RAMEND)
	out SPL, r16
	ldi r16, high(RAMEND)
	out SPH, r16
	;For toggling LED state
	ldi r19, 0b00000000
	ldi r20, 0b00100000
	;Set LED to off initially
	out PORTB, r19

loop:
	;Toggle LED
	eor r19, r20
	out PORTB, r19
	;Simulate cycle wait
	rcall wait
	rjmp loop

;Cycle wait routine
wait:
	;Push variables onto the stack
	push r16
	push r17
	push r18
	;loop on r16 80 times
	ldi r16, 0x50
	;loop on r17 and r18 256 times each
	ldi r17, 0x00
	ldi r18, 0x00

w0:
	dec r18
	brne w0
	dec r17
	brne w0
	dec r16 
	brne w0
	;Pop variables in reverse order
	pop r18
	pop r17
	pop r16
	ret
