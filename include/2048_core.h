#ifndef _2048_CORE_H
#define _2048_CORE_H

#include <stdint.h>
#include <stdbool.h>

#define BOARD_SIZE 4
#define SEED 0x18da // TODO: Until i find a better way of initing the random seed. Turn on the ADC?

typedef __pdata uint8_t board_type[BOARD_SIZE * BOARD_SIZE]; 

extern board_type board; 
extern __pdata uint32_t score;

enum move {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

void init_game(board_type);
void add_random_tile(board_type);
bool move_tile(board_type, enum move mv);
bool game_ended(board_type);

#endif
