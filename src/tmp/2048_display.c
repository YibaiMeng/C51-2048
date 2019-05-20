#include <stdio.h>
#include "display.h"
#define BOARD_SIZE 4
void print_board(int* board)
{   

    for( int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            printf("%i", board[i*BOARD_SIZE + j]);
        }
        printf("\n");
    }
}

