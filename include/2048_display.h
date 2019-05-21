#ifndef _2048_DISPLAY_H
#define _2048_DISPLAY_H

#include "2048_core.h"

void draw_board_outline();

// draw the new board and update backup.
void draw_board(board_type board);

// Draw the number 2 ** (tile_content) on tile tile_id.  
void draw_tile(uint8_t tile_id, uint8_t tile_content); 
void show_score();

#endif
