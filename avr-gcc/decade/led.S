; Helper macro for pulsing the E line
.macro LCD_Pulse_E
    sbi PORTB, E    ; E = 1
    nop             ; Delay
    cbi PORTB, E    ; E = 0
.endm

; Constants for LCD control pins
.equ RS = 0   ; Register Select pin
.equ E = 1    ; Enable pin

; Constants for LCD data pins (assuming PORTB)
.equ LCD_D0 = 0
.equ LCD_D1 = 1
.equ LCD_D2 = 2
.equ LCD_D3 = 3
.equ LCD_D4 = 4
.equ LCD_D5 = 5
.equ LCD_D6 = 6
.equ LCD_D7 = 7

.global LCD_Init
; LCD initialization routine
LCD_Init:
    ; Set up I/O port directions
    ldi r16, 0xFF   ; Set PORTB as output
    out DDRB, r16

    ; Wait for power-up delay
    ldi r20, 64    ; Delay loop count
    ldi r21, 250   ; Delay loop count
    LCD_Init_Delay:
        dec r21
        brne LCD_Init_Delay
        dec r20
        brne LCD_Init_Delay

    ; Initialize LCD in 4-bit mode
    ; Send the initialization sequence
    ldi r16, (1 << RS)    ; RS = 1 (command mode)
    out PORTB, r16
    LCD_Pulse_E
    LCD_Pulse_E
    LCD_Pulse_E

    ; Set interface to 4-bit mode
    ldi r16, (1 << LCD_D4)
    out PORTB, r16
    LCD_Pulse_E

    ; Function set: 4-bit, 2 lines, 5x7 matrix
    ldi r16, (1 << LCD_D5) | (1 << LCD_D4)
    out PORTB, r16
    LCD_Pulse_E

    ; Display on/off control: display on, cursor off, blink off
    ldi r16, (1 << LCD_D3)
    out PORTB, r16
    LCD_Pulse_E

    ; Clear display
    ldi r16, (1 << LCD_D0)
    out PORTB, r16
    LCD_Pulse_E

    ; Entry mode set: increment mode, no shift
    ldi r16, (1 << LCD_D2) | (1 << LCD_D1)
    out PORTB, r16
    LCD_Pulse_E

    ret

.global LCD_WriteCommand
; Write command data to LCD
LCD_WriteCommand:
    push r16

    ; Set RS to 0 (command mode)
    ldi r16, (0 << RS)
    out PORTB, r16

    ; Set data bits
    mov r16, r22

    ; High nibble
    andi r16, 0xF0
    swap r16
    andi r16, 0x0F
    or r16, r22
    out PORTB, r16
    LCD_Pulse_E

    ; Low nibble
    lsl r22
    andi r22, 0xF0
    swap r22
    andi r22, 0x0F
    or r22, r16
    out PORTB, r22
    LCD_Pulse_E

    pop r16
    ret

; Write character to LCD
LCD_WriteCharacter:
    push r16

    ; Set RS to 1 (data mode)
    ldi r16, (1 << RS)
    out PORTB, r16

    ; Set data bits
    mov r16, r22

    ; High nibble
    andi r16, 0xF0
    swap r16
    andi r16, 0x0F
    or r16, r22
    out PORTB, r16
    LCD_Pulse_E

    ; Low nibble
    lsl r22
    andi r22, 0xF0
    swap r22
    andi r22, 0x0F
    or r22, r16
    out PORTB, r22
    LCD_Pulse_E

    pop r16
    ret

.global LCD_AdjustCursorPosition
; Adjust cursor position of LCD
LCD_AdjustCursorPosition:
    push r16

    ; Set RS to 0 (command mode)
    ldi r16, (0 << RS)
    out PORTB, r16

    ; Set data bits
    mov r16, r22

    ; High nibble
    andi r16, 0xF0
    swap r16
    andi r16, 0x0F
    or r16, r22
    out PORTB, r16
    LCD_Pulse_E

    ; Low nibble
    lsl r22
    andi r22, 0xF0
    swap r22
    andi r22, 0x0F
    or r22, r16
    out PORTB, r22
    LCD_Pulse_E

    pop r16
    ret

.global LCD_Clear
; Clear the LCD
LCD_Clear:
    push r16

    ; Set RS to 0 (command mode)
    ldi r16, (0 << RS)
    out PORTB, r16

    ; Set data bits
    ldi r16, (1 << LCD_D0)
    out PORTB, r16
    LCD_Pulse_E

    pop r16
    ret
