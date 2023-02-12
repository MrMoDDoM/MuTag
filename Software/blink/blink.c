#include "stm8l.h"
int d;

// Find a better way to do this
void wait(){
	for(d = 0; d < 32000; d++) { }
	for(d = 0; d < 32000; d++) { }
}

int main() {
	// Configure pin for the right led
	PD_DDR = 0x01; // Output direction
	PD_CR1 = 0x01; // Set the control register -- check the datasheet

	// Configure pin for the left led
	PB_DDR = 0x01; // Output direction
	PB_CR1 = 0x01; // Set the control register -- check the datasheet

	PB_ODR ^= 0x01; // Invert the first state

	// Loop
	do {
		// Invert the state of the two pins
		PB_ODR ^= 0x01;
		PD_ODR ^= 0x01;
		wait();
	} while(1);
}
