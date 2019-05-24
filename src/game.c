#include <C8051F020.h>
#include <stdio.h>
#include "system.h"
#include "ili9486.h"
#include "2048_display.h"
#include "2048_core.h"
#include "keyboard.h"
#include "dac.h"
#include "lcd1602.h"
board_type board;

#define DEBUG printf
void main(void) {
    char key;
    bool is_success;
    system_init();
    dac_init();
    lcd1602_init();
    ili9486_init();
    display_color(0xffdd); // RGB faf8ef
    draw_board_outline();
    delay(200);
    init_game(board);
    delay(200);
    draw_board(board);
    delay(200);
    while(1) {
        if (game_ended(board)) {
            game_over();
            printf("[game.c] Game Over\n");
            break;
        }
        key = get_key();
        printf("[game.c] Key pressed is %c\n", key);
        switch(key) {
            case '5' : {
                printf("[game.c] Command:  Move left!\n");
                is_success = move_tile(board, GAME_MOVE_LEFT);
                break;
            };
            case '7' : {
                printf("[game.c] Command:  Move right!\n");
                is_success = move_tile(board, GAME_MOVE_RIGHT);            
                break;
            };
            case '2' : {
                printf("[game.c] Command:  Move up!\n");
                is_success = move_tile(board, GAME_MOVE_UP);            
                break;
            };     
            case '0' : {
                is_success = move_tile(board, GAME_MOVE_DOWN); 
                printf("[game.c] Command:  Move down!\n");           
                break;
            };
            
            case 'F' : {
                printf("[game.c] Command:  Reset game!\n");           
                init_game(board);
                draw_board(board);
                continue;
            }
            default : {
                printf("[game.c] Invalid Command!\n");
                continue;
            }            
        }
        
        if(is_success) {
            printf("[game.c] Move successful!\n");
            add_random_tile(board);
            play_sound();
            draw_board(board);
        }
        else {
           printf("[game.c] Move not successful!\n");
           continue;
        }
        show_score();
        delay(1000);
    }
    while (1) { 
    } 
}
