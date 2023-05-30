#define __SFR_OFFSET 0
#include <avr/io.h>

.global disp

.section .text

disp:
	lsl r24
	lsl r24
	out PORTD, r24
	ret
