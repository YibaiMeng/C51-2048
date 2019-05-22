#include <C8051F020.h>
#include <stdio.h>
#include "system.h"
#include "ili9486.h"
#include "2048_display.h"
#include "2048_core.h"
#include "keyboard.h"
board_type board;


#define DEBUG printf
void main(void) {
    //int i;
    char key;
    bool is_success;
    system_init();
    ili9486_init();
    dis_color(0xFF00);
    draw_board_outline();
    delay(200);
    init_game(board);
    delay(200);
    draw_board(board);
    delay(200);
    while(1) {
        if (game_ended(board)) {
            printf("Game Over\n");
            break;
        }
        key = get_key();
        printf("Moved %c\n", key);
        switch(key) {
            case '1' : {
                is_success = move_tile(board, LEFT);
                break;
            };
            case '2' : {
                is_success = move_tile(board, RIGHT);            
                break;
            };
            case '3' : {
                is_success = move_tile(board, UP);            
                break;
            };     
            case '4' : {
                is_success = move_tile(board, DOWN);            
                break;
            };
            
            case '5' : {
                init_game(board);
                draw_board(board);
                continue;
            }
            default : {
                continue;
            }            
        }
        
        if(is_success) {
            printf("Move success!\n");
            add_random_tile(board);
        }
        else {
           printf("Move not a success!\n");
           continue;
        }
        draw_board(board);
        //show_score();
        delay(10000);
    }
    while (1) { 
    } 
}
