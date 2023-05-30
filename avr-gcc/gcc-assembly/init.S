#define __SFR_OFFSET 0
#include <avr/io.h>

.global init

.section .text

init:
	;Set PD2-PD5 as output pins
	ldi r16, 0b00111100
	out DDRD, r16
	ret
