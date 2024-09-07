// This code runs the dot notifier
// Chip: attiny13a-pu 8pins

// Pin configuration
// Outputs port B:
// DDRB:     0b | 1  | 1  | 1  | 1  | 1  | 1  |
// Pin number:  | 01 | 03 | 02 | 07 | 06 | 05 |
// Port num:    | P5 | P4 | P3 | P2 | P1 | P0 |
// Purpose:     | -- |REL |SND |LED |PIZ |PIR | 

// Base frequency of the built in clock 1MHz.
#undef F_CPU
#define F_CPU 1000000UL

#include <stdbool.h>
#include <util/delay.h>
#include <avr/io.h>

int get_snd_input(void) {
    // Read pin 2, port 3.
    if ((PINB & 0b00001000) != 0) {
        return 1;
    }
    return 0;
}

int get_pir_input(void) {
    // Read pin 5, port 0.
    if ((PINB & 0b00000001) != 0) {    
        return 1;
    }
    return 0;
}
// ----------------------------------
void piz_on() {
    PORTB |= (1 << PB1);
    return;
}

void relay_on() {
    PORTB |= (1 << PB4);
    return;
}

void led_on() {
    PORTB |= (1 << PB2);
    return;
}
// ----------------------------------
void piz_off() {
    PORTB &= ~(1 << PB1);
    return;
}

void relay_off() {
    PORTB &= ~(1 << PB4);
    return;
}

void led_off() {
    PORTB &= ~(1 << PB2);
    return;
}

void all_off() {
    led_off();
    piz_off();
    relay_off();
}

void relay_click() {
    relay_on();
    _delay_ms(100);
    relay_off();
}
// ----------------------------------

void setup(void) {
    // Set pin 6 and 7 as output, the rest as input.
    DDRB = 0b00000110;
    // Turn off everything
    all_off();
    _delay_ms(200);
    piz_on();
    _delay_ms(50);
    all_off();
    return;
}

int main(void) {
    setup();
    int pir = 0;
    int audio = 0;
    int pir_counter = 0;
    int piz_counter = 0;
    int relay_counter = 0;
    int piz_d = 0;
    int relay_d = 1000;
    int pir_d = 100;

    bool relay_active = false;    
    bool piz_active = false;

    while(1) {
        // We will be counting by one millisecond, this means the loop is fast and does not skip quick sound inputs.
        _delay_ms(1);
        pir = 0;  
        audio = 0;      

        if(pir_counter == pir_d) {
            // Only read the pir sensor once a while.
            pir = get_pir_input();
            pir_counter = 0;
        }
        pir_counter++;

        audio = get_snd_input();
        if(audio == 1) {
            // LED is self blinking and stays on until reset.
            led_on();

            // Turn on relay if not on already.
            if(!relay_active) {
                relay_counter = 0;
                relay_active = true;
                relay_click();
            }
        }

        if(audio == 1 && !piz_active) {
            piz_active = true;
            piz_d = 200; 
            int silence_counter;
            for (int i = 0; i < 2; i++) {
                piz_counter = 0;
                silence_counter = 0;
                piz_on();
                while(1) {
                    _delay_ms(1);
                    if(piz_active) {
                        if(piz_counter == piz_d) {
                            piz_off();
                            piz_active = false;
                        }
                        piz_counter++;
                    }
                    if(!piz_active) {
                        if(silence_counter == piz_d) {
                            piz_active = true;
                            break;
                        }
                        silence_counter++;    
                    } 
                }
            }
            piz_active = false;
        }

        if(pir == 1 && !piz_active) {
            piz_active = true;
            piz_d = 50; 
            bool stop = false;      
            int silence_counter;
            for (int i = 0; i < 3; i++) {
                piz_counter = 0;
                silence_counter = 0;
                piz_on();
                while(1) {
                    _delay_ms(1);
                    if(get_snd_input()) {
                        stop = true;
                    }     
                    if(stop) {
                        piz_off();
                        break;
                    }
                    if(piz_active) {
                        if(piz_counter == piz_d) {
                            piz_off();
                            piz_active = false;
                        }
                        piz_counter++;
                    }
                    if(!piz_active) {
                        if(silence_counter == piz_d) {
                            piz_active = true;
                            break;
                        }
                        silence_counter++;    
                    } 
                }
                if(stop) {
                    break;
                }
            }
            piz_active = false;
        }
        
        if(relay_counter == relay_d) {
            relay_click(); 
            relay_active = false;
            relay_counter = 0;
        }    
        if (relay_active) {
            relay_counter++;
        }
    }
    return 0;
}
