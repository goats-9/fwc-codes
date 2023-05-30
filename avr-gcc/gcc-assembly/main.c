#include <avr/io.h>

// Assembly function declarations
extern void init(void);
extern void disp(uint8_t);
extern void delay(uint8_t, uint8_t, uint8_t);

int main(void) {
	// Data direction setup
	init();
	// Decade counter implementation
	while (1) {
		for (int i = 0; i < 10; i++) {
			disp(i);
			delay(0,0,80);
		}
	}
	return 0;
}
