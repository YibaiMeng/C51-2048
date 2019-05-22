#ifndef _2048_CORE_H
#define _2048_CORE_H

#include <stdint.h>
#include <stdbool.h>

#define BOARD_SIZE 4
#define SEED 0x18da // TODO: Until i find a better way of initing the random seed. Turn on the ADC?

#ifdef __SDCC
// TODO: why __pdata would not work.
typedef __xdata uint8_t board_type[BOARD_SIZE * BOARD_SIZE]; 
extern __xdata uint32_t score;
#else
typedef uint8_t board_type[BOARD_SIZE * BOARD_SIZE]; 
extern  uint32_t score;
#endif
extern board_type board; 

#define GAME_MOVE_LEFT 0
#define GAME_MOVE_RIGHT 1
#define GAME_MOVE_UP 2 
#define GAME_MOVE_DOWN 3

void init_game(board_type);
void add_random_tile(board_type);
bool move_tile(board_type, uint8_t);
bool game_ended(board_type);

#endif
