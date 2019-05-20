#ifndef _SYSTEM_H
#define _SYSTEM_H

#define SYSCLK 22118400

void system_init();
void xram_init();
void sysclk_init();
void delay(int);
void port_init();


#endif
