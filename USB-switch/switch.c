// This code runs the dot notifier
// Chip: attiny13a-pu 8pins

// Pin configuration
// Outputs port B:
// DDRB:     0b | 0 | 0 | 1  | 1  | 1  | 1  | 1  | 1  |
// Pin number:  | / | / | 01 | 03 | 02 | 07 | 06 | 05 |
// Port num:    | / | / | P5 | P4 | P3 | P2 | P1 | P0 |
// Purpose:     | / | / | -- |REL | -- | C  | R  | L  | 

// Base frequency of the built in clock 1MHz.
#undef F_CPU
#define F_CPU 1000000UL

#include <stdbool.h>
#include <util/delay.h>
#include <avr/io.h>

int get_sw_state(void) {
    // Read pins 7. Center position.
    if ((PINB & 0b00000100) != 0) {
        return 1;
    }
    // Read pins 6. Right position.
    if ((PINB & 0b00000010) != 0) {
        return 2;
    }  
    // Read pins 5. Left position.
    if ((PINB & 0b00000001) != 0) {
        return 0;
    }  
    return 10;
}

void relay_on() {
    // PIN 3.
    PORTB |= (1 << PB4);
    return;
}

void relay_off() {
    PORTB &= ~(1 << PB4);
    return;
}

void click(int n) {
    for (int i = 0; i < n; i++) {
        relay_on();
        _delay_ms(100);
        relay_off();
        _delay_ms(100);
    }
    return;
}
// ----------------------------------

void setup(void) {
    // Set pin 5,6,7 as input, the rest as output.
    // 1 output, 0 input.
    DDRB = 0b11111000;
    relay_off();
    return;
}

int main(void) {
    // Number of clicks to switch from current to desired machine.
    // matrix[current, target]
    // Left - notebook - sw value 0
    // Center - shelf - sw value 1
    // Right - desktop - sw value 2

    // left     {left, center, right}
    // center   {left, center, right}
    // right    {left, center, right}
    int matrix[3][3] =  { 
                        {0, 2, 3}, 
                        {2, 0, 1},
                        {1, 3, 0} 
                        };
    
    setup();
    int target_0 = 0;
    int target_1 = 0;
    int current = 0;
    int clicks = 0;
    while(1) {
        target_0 = get_sw_state();
        _delay_ms(500);
        target_1 = get_sw_state();
        // Wait for the switch to settle int final position.
        if (target_0 == target_1) {
            clicks = matrix[current][target_1];
            click(clicks);
            current = target_1;
            _delay_ms(100);
        }
    }
    return 0;
}
