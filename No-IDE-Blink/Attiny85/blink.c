// This code blinks on pin 5.
// Chip: attiny85 8pins

// Pin configuration
// Outputs port B:
// DDRB:     0b | 0 | 0 | 1  | 1  | 1  | 1  | 1  | 1  |
// Pin number:  | / | / | 01 | 03 | 02 | 07 | 06 | 05 |
// Port num:    | / | / | P5 | P4 | P3 | P2 | P1 | P0 |
// Purpose:     | / | / | /  | /  | /  | /  | /  | /  | 

// Base frequency of the built in clock 1MHz.
#undef F_CPU
#define F_CPU 1000000UL

#include <stdbool.h>
#include <util/delay.h>
#include <avr/io.h>

void led_on() {
    // PIN 5.
    PORTB |= (1 << PB0);
    return;
}

void led_off() {
    PORTB &= ~(1 << PB0);
    return;
}

// ----------------------------------

void setup(void) {
    // Set all as output.
    // 1 output, 0 input.
    DDRB = 0b11111111;
    led_off();
    return;
}

int main(void) {
    setup();
    while(1) {
        led_on();
        _delay_ms(500);
        led_off();
        _delay_ms(500);
    }
    return 0;
}
