#define __SFR_OFFSET 0
#include <avr/io.h>

.global delay

.section .text

delay:
	dec r24
	brne delay
	dec r22
	brne delay
	dec r20
	brne delay
	ret
