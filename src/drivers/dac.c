#include <stdio.h>

#include <C8051F020.h>

#include "system.h"
#include "dac.h"

uint16_t sound_position;
// sound_data
#include "../../res/sound/sound_data.inc"
static volatile int is_complete = 0;

#define DEBUG printf
void dac_init() {
    // Voltage 	generator init
    REF0CN = 0x03; // Internal Bias Generator On, Internal Reference Buffer On. Internal voltage reference is driven on the VREF pin.
    // DAC init
    DAC1CN = 0x97; // 0b10010111 Enables DAC1, output occurs on timer 4 overflow, data left align
    
    // Set Timer 4 
    T4CON = 0x00; // clear flag; use interal clock, disable external pin; reload when overflows; stopped;
    CKCON |= 0x40; // timer 4 uses SYSCLK. Must not mess up other configurations, so use '|'
    RCAP4 = - SYSCLK / DATARATE;
    T4 = RCAP4;
    EA = 1;
}


void play_sound() {
    DEBUG("[play_sound]: Start playing sound!\n");
    sound_position = 0;
    EIE2 |= 0x04;  // Allows interrupt for timer 4 
    T4CON |= 0x04; // starts timer 4 
    EA = 1;    
    DEBUG("[play_sound]: Registers set!\n");
    while(!is_complete) {
        delay(10);
    }
    DEBUG("[play_sound]: Sound play completed!\n");
    is_complete = 0;
}	

void Timer4_isr (void) __interrupt 16 {
    DAC1 = sound_data[sound_position++]; // 播放喇叭
    T4CON &= ~0x80; // clear overflow flag;
    if (sound_position >= SOUND_POSITION_END) {
	    is_complete = 1;
	    T4CON &= 0xfb; // 0b11111011 stop T4
	    EIE2 &= 0xfb; // 0b11111011 stop handling T4 interrupt 
        sound_position = 0;
	    DEBUG("[timer4_isr]: finishing! is_complete is: %i\n", is_complete);
    }
}
