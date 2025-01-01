// This code watches two buttons for two players to mark which pressed the button first.
// Chip: attiny85 8pins

// Pin configuration
// Outputs port B:
// DDRB:     0b | 1  | 1  | 1  | 1  | 1  | 1  |
// Pin number:  | 01 | 03 | 02 | 07 | 06 | 05 |
// Port num:    | P5 | P4 | P3 | P2 | P1 | P0 |
// Purpose:     | -- |SW1 |SW2 |BUZ |LRD |LRB | 

// Base frequency of the built in clock 1MHz.
#undef F_CPU
#define F_CPU 1000000UL

#include <stdbool.h>
#include <util/delay.h>
#include <avr/io.h>

int get_player(void) {
    // Read pin 2, 3 port 0.
    if ((PINB & 0b00001000) != 0) {    
        // PORT 3
        return 1;
    }
    if ((PINB & 0b00010000) != 0) {     
        // PORT 4
        return 2;
    }  
    return 0;
}

void led1_on() {
    PORTB |= (1 << PB0);
    return;
}

void led2_on() {
    PORTB |= (1 << PB1);
    return;
}

void buz_on() {
    PORTB |= (1 << PB2);
    return;
}


void all_off() {
    PORTB = 0b00000000;
}

void player1_alarm(int num) {
    for (int i = 0; i < num; i++) {
        buz_on();
        led1_on();
        _delay_ms(500);
        all_off();
        _delay_ms(500);
    }
}

void player2_alarm(int num) {
    for (int i = 0; i < num; i++) {
        buz_on();
        led2_on();
        _delay_ms(1000);
        all_off();
        _delay_ms(1000);
    }
}

// ----------------------------------

void setup(void) {
    // Set pin 5,6,7 as output, the rest as input.
    DDRB |= (1 << PB0);
    DDRB |= (1 << PB1);
    DDRB |= (1 << PB2);

    // Turn off everything
    all_off();
    _delay_ms(100);
    led1_on();
    led2_on();
    buz_on();
    _delay_ms(200);
    all_off();
    return;
}

int main(void) {
    setup();
    int player = 0;

    while(1) {
        player = get_player();
        if(player == 1) {
            player1_alarm(4);
            while (1) {
                led1_on();
                _delay_ms(400);
                all_off();
                _delay_ms(400);
            }
            return 0;
        }
        if(player == 2) {
            player2_alarm(2);
            while (1) {
                led2_on();
                _delay_ms(400);
                all_off();
                _delay_ms(400);
            }
            return 0;
        }
    }
    return 0;
}
