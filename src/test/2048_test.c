#include <stdio.h>
#include <ncurses.h>

#include "2048_core.h"

#define printf(...) //mvprintw(row++, 30, __VA_ARGS__); 

board_type board;
int row = 0;
void draw_board(board_type board) {
    for(int i = 0; i < BOARD_SIZE; i++)
        for(int j = 0; j < BOARD_SIZE; j++)
            mvprintw(j * 4,i * 4, "%i", board[i + j * BOARD_SIZE]);
    refresh();
};

int main(void) {
    char key;
    bool is_success;
    initscr();
    noecho();
    raw();	
    move(20,30);
    init_game(board);
    draw_board(board);
    while(1) {
        if (game_ended(board)) {
            printf("Game Over\n");
            break;
        }
        key = getch();
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
            case 'q' : {
               endwin();
               return 0;
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
    }
    endwin();
    return 0;
}
