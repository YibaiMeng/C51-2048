#include <stdio.h>

#include "system.h"
#include "ili9486.h"
#include "2048_core.h"
#include "2048_display.h"
#include "design_specs.h"
#include "lcd1602.h"

#define START_X 0
#define START_Y 80  // (SCREEN_HEIGHT - SCREEN_WIDTH)/2
#define END_X 320
#define END_Y 400 // (SCREEN_HEIGHT + SCREEN_WIDTH)/2

#include "../res/tiles.inc"

void draw_board_outline() {
    // int i;
    // Draw board background
    //draw_rectangle(0, 80, 320, 320, BACKGROUND_COLOR_EMPTY);
    // Draw margins
    draw_rectangle(71, 80, 12, 320, MARGIN_COLOR);
    draw_rectangle(71+12+71, 80, 12, 320, MARGIN_COLOR);
    draw_rectangle(71+12+71+12+71, 80, 12, 320, MARGIN_COLOR);
    draw_rectangle(0, 80+71, 320, 12, MARGIN_COLOR);
    draw_rectangle(0, 80+71+12+71, 320, 12, MARGIN_COLOR);
    draw_rectangle(0, 80+71+12+71+12+71, 320, 12, MARGIN_COLOR);
    printf("[draw_board_outline] Finished drawing!\n");
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
    if (tile_content == 0) {
        draw_rectangle((tile_id % 4) * (TILE_SIZE + MARGIN_SIZE) + START_X, (tile_id / 4) * (TILE_SIZE + MARGIN_SIZE) + START_Y, TILE_SIZE, TILE_SIZE, BACKGROUND_COLOR_EMPTY);
        printf("[draw_tile] No tile at tile_id %i\n", tile_id);
        return;
    }
    
    
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
            printf("[draw_tile] wtf! This shouldn't have happened!\n");
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
        draw_tile(i, board[i]);
        /*
        if (board[i] != board_backup[i]) {
            draw_tile(i, board[i]);
            board_backup[i] = board[i];
        }*/
    }   
}

static __xdata char score_buffer[16];
void show_score() {
    int i;
    for(i = 0; i < 16; i++) {
        score_buffer[i] = ' '; //space
    }
    /*
    score = 0;
    for(i = 0; i < 16; i++) {
        if(board[i] != 1 && board[i] != 2) {
            score += board[i];
        }
    }*/
    sprintf(score_buffer, "Score: %d", score);
    for(i = 0; i < 16; i++) {
        if (score_buffer[i] == '\0') {
            score_buffer[i] = ' ';
            break;
        }
    }
    printf("%s\n", score_buffer);
    for(i = 0; i < 16; i++) {
        lcd1602_write_xy(0, i, score_buffer[i]);
    }
}

void game_over() {
    int i;
    for(i = 0; i < 16; i++) {
        score_buffer[i] = ' '; //space
    }
    /*
    score = 0;
    for(i = 0; i < 16; i++) {
        if(board[i] != 1 && board[i] != 2) {
            score += board[i];
        }
    }*/
    sprintf(score_buffer, "Game Over!");
    for(i = 0; i < 16; i++) {
        if (score_buffer[i] == '\0') {
            score_buffer[i] = ' ';
            break;
        }
    }
    printf("%s\n", score_buffer);
    for(i = 0; i < 16; i++) {
        lcd1602_write_xy(0, i, score_buffer[i]);
    }
}
