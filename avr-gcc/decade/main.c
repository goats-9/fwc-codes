#include "lcd.h"

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
			LCD_Cmd(0xC0);
			LCD_Char('0'+i);
			_delay_ms(1000);
		}
	}
}
