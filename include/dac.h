#ifndef __DAC_H
#define __DAC_H

#include <stdint.h>

//__sfr16 RCAP4 = 0xe4; // RCAP4H and RCAP4L together
__sfr16 __at (0xf5f4) T4;    // Timer4
//__sfr16 DAC0 = 0xd2;  // DAC0H and DAC0L

#define DATARATE 8000
#define SOUND_POSITION_END 1463

void dac_init();
void play_sound();
// MUST place interrupt here, or it won't execute!
void Timer4_isr (void) __interrupt 16;


#endif
