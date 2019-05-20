#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <C8051F020.h>
#define LEFT 3
#define MID_LEFT 2
#define MID_RIGHT 1
#define RIGHT 0

#define NO_KEY 255

#define KEYBOARD_PORT P4

unsigned char get_key();

#endif
