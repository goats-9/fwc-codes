#include <avr/io.h> 
#include <util/delay.h> 
#include <stdlib.h> 

// Declare assembly implemented routines
extern void LCD_Init(void);
extern void LCD_Cmd(uint8_t);
extern void LCD_Char(uint8_t);
extern void LCD_SetCursor(uint8_t, uint8_t);
extern void LCD_Clear(void);

void LCD_String(const char *str) {
	while (*str) LCD_Char(*str++);
}

int main(void) {
	LCD_Init(); // initialize LCD controller
	char *digits[10] = {
		"Zero",
		"One",
		"Two",
		"Three",
		"Four",
		"Five",
		"Six",
		"Seven",
		"Eight",
		"Nine",
	};
	while(1) {
		for (int i = 0; i <= 9; i++) {
			LCD_Clear();
			LCD_String(digits[i]);
			LCD_SetCursor(1,0);
			LCD_Char('0'+i);
			_delay_ms(1000);
		}
	}
}
