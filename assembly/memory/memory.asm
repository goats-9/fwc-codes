.include "../m328Pdef.inc"

setup:
	;Set PB5 or pin 13 on Arduino as
	;output pin
	sbi DDRB, 5
	;Set prescaler in TC0 control
	;register B to be 1024
	ldi r16, 0b00000101
	out TCCR0B, r16
	;LED will be toggled with r21
	;ldi r21, 0
	ldi r22, 0b00100000
	;out PORTB, r21
	;Clear SREG
    ldi r16, 0
    out SREG, r16
	;Store the stack pointer in r16
	;Creating stack to be as large
	;as available main memory
	ldi r16, low(RAMEND)
    out SPL, r16
    ldi r16, high(RAMEND)
    out SPH, r16
 	;Set PD2 to PD5 as output pins.
	;Correspond to pins 2 to 5 on 
	;the Arduino.
    ldi r16, 0b00111100
    out DDRD, r16
	;Start storage from 0x0100.
	;Store lower and higher byte 
	;separately.
    ldi XL, 0x00
    ldi XH, 0x01
	;Initialize counter and digit
	ldi r16, 0
    ldi r17, 0x0A

;Loading digits 0-9 into memory 
;locations 0x0100-0x0109
loop_mem:
	;Store current value in current
	;memory location
    st X, r16
 	;Next value to be stored   
    inc r16
	;Next address to store the value
    inc XL
	;Decrement count
    dec r17
    brne loop_mem

;Main loop program
;Write each value to the 7447
;Delay using the timer
loop:
	;Load the starting address
	;only need to load for XL
	;since XH was unchanged.
	ldi XL, 0x00
	;Initialize loop variables
	ldi r19, 10
	rcall loop_decade
	rjmp loop

;Loop function for the decade counter
loop_decade:
	;Load current value for the
	;loop variable from memory
	;and increment memory location
	ld r18, X
	inc XL
	;Multiply by 4 to output to 7447
	lsl r18
	lsl r18
	out PORTD, r18
	;eor r21, r22
	out PORTB, r22
	ldi r29, 0b01000000
	rcall pause
	;Update and check if loop 
	;variable equals zero
	dec r19
	brne loop_decade
	ret

;Pause routine waits till TIFR0 has 
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
	dec r29
	brne loop_pause
	ret
