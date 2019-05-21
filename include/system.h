#ifndef _SYSTEM_H
#define _SYSTEM_H

#define SYSCLK 22118400
#define BAUDRATE 115200
#define LINE_BUFFER_LEN 10
void system_init();
void xram_init();
void sysclk_init();
void delay(int);
void port_init();
void getline();
void uart0_init();

#endif
