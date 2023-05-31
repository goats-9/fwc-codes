.global LCD_Init
.global LCD_Cmd
.global LCD_Char
.global LCD_Clear
.global LCD_SetCursor

.section .text

; Definition of LCD pins
#define LCD_RS 0		; RS
#define LCD_EN  1		; EN
#define LCD_D4 2		; DB4
#define LCD_D5 3		; DB5
#define LCD_D6 4		; DB6
#define LCD_D7 5		; DB7
#define PORTB  0x05
#define DDRB   0x04

; Definition of used LCD commands
#define LCD_CLR   0x01	; Clear LCD Display
#define LCD_CRS   0x02	; Return Cursor to Home
#define LCD_ENT   0x06	; Set Cursor Direction to Right
#define LCD_DISP  0x0C	; Set LCD Display on
#define LCD_FS 	  0x28	; Set 4 bit, 2 line, 5x8 dots
#define LCD_DDRAM 0x80	; Set LCD DDRAM Address
#define LCD_LINE  0x40	; DDRAM Address of second line.
;Macro to pulse enable line
.macro LCD_Pulse_EN
	push r16
	sbi PORTB, LCD_EN 
	ldi r16, 64
	pulse_delay:
		dec r16
		brne pulse_delay
	cbi PORTB, LCD_EN
	pop r16
.endm

;Global LCD Driver functions in this file:
;	1. LCD_Init
;	2. LCD_Cmd
;	3. LCD_Char
;	4. LCD_Clear
;	5. LCD_SetCursor

;Function to send nibble to LCD
;The upper 4 bits will be sent
LCD_Send_Nibble:
	push r16
	;Clear data lines
	in r16, PORTB
	andi r16, 0xC3
	out PORTB, r16
	;Send nibble
	mov r16, r24
	lsr r16
	lsr r16
	andi r16, 0x3C
	out PORTB, r16
	LCD_Pulse_EN
	pop r16
	ret

;Function to send byte to LCD
;Calls LCD_Send_Nibble
LCD_Send_Byte:
	push r16
	mov r16, r24
	andi r16, 0xF0
	rcall LCD_Send_Nibble
	mov r16, r24
	swap r16
	andi r16, 0xF0
	rcall LCD_Send_Nibble
	pop r16
	cbi PORTB, 5
	ret

;Send command to the LCD
LCD_Cmd:
	;Set RS to 0
	cbi PORTB, LCD_RS
	rcall LCD_Send_Byte
	ret

LCD_Char:
	;Set RS to 1
	sbi PORTB, LCD_RS
	rcall LCD_Send_Byte
	ret

;Initialize the LCD
;LCD will operate in 4 bit mode.
LCD_Init:
	push r16
	push r17
	;Declare output pins
	ldi r16, 0xFF
	out DDRB, r16
	;LCD Function set
	ldi r24, LCD_FS
	rcall LCD_Cmd
	;Turn on LCD
	ldi r24, LCD_DISP
	rcall LCD_Cmd
	;Clear LCD
	ldi r24, LCD_CLR
	rcall LCD_Cmd
	;Require delay for this command
	ldi r16, 64
	ldi r17, 0
	delay:
		dec r16
		brne delay
		dec r17
		brne delay
	;Set LCD Entry Mode
	ldi r24, LCD_ENT
	rcall LCD_Cmd
	pop r17
	pop r16
	ret

;Clear the LCD
LCD_Clear:
	ldi r24, LCD_CLR
	rcall LCD_Cmd
	ret

;Set cursor position as specified.
;r24 -> row number
;r25 -> column number
LCD_SetCursor:
	push r16
	push r17
	push r18
	mov r16, r24
	mov r17, r25
	;Send command data
	cbi PORTB, LCD_RS
	ldi r18, LCD_DDRAM
	cpi r16, 0
	breq continue
	ori r18, LCD_LINE
continue:
	or r18, r17
	mov r24, r18
	rcall LCD_Cmd
	pop r18
	pop r17
	pop r16
	ret

