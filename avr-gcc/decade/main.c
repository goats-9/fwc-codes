#include <avr/io.h> 
#include <util/delay.h> 
#include <stdlib.h> 

// Declare assembly implemented routines
extern void LCD_Init(void);
extern void LCD_WriteCommand(uint8_t);
extern void LCD_WriteCharacter(uint8_t);
extern void LCD_AdjustCursorPosition(uint8_t);
extern void LCD_Clear(void);

int main(void) {
	// Use PortB for LCD interface
	DDRB = 0xFF; // Set PB0-PB7 as outputs	 
	LCD_Init(); // initialize LCD controller
	while(1) {
		LCD_Clear();
		LCD_Message("Sample Text");  // show counter 
		LCD_Integer(8);
		_delay_ms(600);   // set animation speed
	}
}
