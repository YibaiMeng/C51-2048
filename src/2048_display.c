#include <stdio.h>

#include "system.h"
#include "ili9486.h"
#include "2048_core.h"
#include "2048_display.h"
#include "design_specs.h"

//#include "lcd1602.h"

#define START_X 0
#define START_Y 80  // (SCREEN_HEIGHT - SCREEN_WIDTH)/2
#define END_X 320
#define END_Y 400 // (SCREEN_HEIGHT + SCREEN_WIDTH)/2

#include "../res/tiles.inc"

void draw_board_outline() {
    // int i;
    // Draw board background
    draw_rectangle(0, 80, 320, 320, BACKGROUND_COLOR_EMPTY);
    // Draw margins
    draw_rectangle(71, 0, 12, 320, MARGIN_COLOR);
    draw_rectangle(71+12+71, 0, 12, 320, MARGIN_COLOR);
    draw_rectangle(71+12+71+12+71, 0, 12, 320, MARGIN_COLOR);
    draw_rectangle(320, 80+71, 320, 12, MARGIN_COLOR);
    draw_rectangle(320, 80+71+12+71, 320, 12, MARGIN_COLOR);
    draw_rectangle(320, 80+71+12+71+12+71, 320, 12, MARGIN_COLOR);
}


/*
    The ordering of the tile_id s are as the following graph shows:
         0  1  2  3
         4  5  6  7
         8  9 10 11
        12 13 14 15
*/
void draw_tile(uint8_t tile_id, uint8_t tile_content) {
    
    img_type img = NULL;
    /*
        color_type color_background = background_colors[tile_content - 1];
        color_type color_font = font_colors[tile_content - 1];
        uint8_t x = tile_id % 4 * (TILE_SIZE + MARGIN_SIZE) + X_START
        uint8_t y = tile_id / 4 * (TILE_SIZE + MARGIN_SIZE) + Y_START
    */ 
    // This is because the size of each tile is NOT the same, so it's diffcult to store them into a single array. If I do that, them I would need to store a list of their starting points, which would subject to change every time I update the images.
    switch(tile_content) {
        case 1 : {
            img = tile_2;
            break;
        };
        case 2 : {
            img = tile_4;
            break;
        };        
        case 3 : {
            img = tile_8;
            break;
        };        
        case 4 : {
            img = tile_16;
            break;
        };        
        case 5 : {
            img = tile_32;
            break;
        };        
        case 6 : {
            img = tile_64;
            break;
        };        
        case 7 : {
            img = tile_128;
            break;
        };        
        case 8 : {
            img = tile_256;
            break;
        };       
        case 9 : {
            img = tile_512;
            break;
        };        
        case 10 : {
            img = tile_1024;
            break;
        };        
        case 11 : {
            img = tile_2048;
            break;
        };
        default : {
            // This should never be executed!
            break;
        };        
    }
    draw_image((tile_id % 4) * (TILE_SIZE + MARGIN_SIZE) + START_X, (tile_id / 4) * (TILE_SIZE + MARGIN_SIZE) + START_Y, TILE_SIZE, TILE_SIZE, img, font_colors[tile_content - 1], background_colors[tile_content - 1]);   
}


void draw_board(board_type board) {
    static bool is_init = 0;
    static board_type board_backup;
    uint8_t i;
    if (!is_init) {
        for(i = 0; i <  BOARD_SIZE * BOARD_SIZE; i++)
            board_backup[i] = 0;
        is_init = 1;
    }
    for(i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        if (board[i] != board_backup[i]) {
            draw_tile(i, board[i]);
            board_backup[i] = board[i];
        }
    }   
}

void show_score() {
    1;
    /*
    sprintf(buffer, "Score: %d", score);
    show_string();*/
}
