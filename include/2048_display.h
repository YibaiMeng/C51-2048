#ifndef _2048_DISPLAY_H
#define _2048_DISPLAY_H

#include "2048_core.h"

extern board_type board_backup;

// draw the new board and update backup.
void draw_board(board_type board, board_type board_backup);

// Draw the number 2 ** (tile_content) on tile tile_id.  
void draw_tile(uint8_t tile_id, uint8_t tile_content, board_type board); 


#endif
