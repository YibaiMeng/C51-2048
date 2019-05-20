/*
    This file is used to generate the lookup table used in ../src/2048_core.c
*/
#include <stdio.h>
#include "../src/2048_core.h"

int* get_func(enum move mv, int row_num) {    
    static int f[BOARD_SIZE];
    switch(mv)
    {
    	case LEFT:
	    {
                for(int i = 0; i < BOARD_SIZE; i++)
		        {
		            f[i] = BOARD_SIZE * row_num + i;
		        }	
		        break;
	    }
	    case RIGHT:
            {
                for(int i = 0; i < BOARD_SIZE; i++)
                {
                    f[i] = BOARD_SIZE * row_num + BOARD_SIZE - 1 - i;
                }
                break;
            }
	case DOWN:
            {
                for(int i = 0; i < BOARD_SIZE; i++)
                {
                    f[i] = row_num + BOARD_SIZE * (BOARD_SIZE - 1 - i);
                }
                break;
            }
	case UP:
            {
                for(int i = 0; i < BOARD_SIZE; i++)
                {
                    f[i] = row_num + BOARD_SIZE * i;
                }
                break;
            }
    }
    printf("{");
    for(int i = 0; i < BOARD_SIZE-1; i++) {
        printf("%i,", f[i]);
    }
    printf("%i", f[BOARD_SIZE-1]);
    printf("}");

    return f;
}

int main () {
    printf("static uint8_t lookup_table[][BOARD_SIZE][BOARD_SIZE] = {{\n");
    for(int j = 0; j < BOARD_SIZE; j++) { 
        printf("    ");
        get_func(LEFT, j);
        if(j != BOARD_SIZE - 1)
            printf(",");
        printf("\n");
    }
    printf("}, {\n");
    for(int j = 0; j < BOARD_SIZE; j++) { 
        printf("    ");
        get_func(RIGHT, j);
        if(j != BOARD_SIZE - 1)
            printf(",");
        printf("\n");
    }
    printf("}, {\n");
    for(int j = 0; j < BOARD_SIZE; j++) { 
        printf("    ");
        get_func(UP, j);
        if(j != BOARD_SIZE - 1)
            printf(",");
        printf("\n");
    }
    printf("}, {\n");
    for(int j = 0; j < BOARD_SIZE; j++) { 
        printf("    ");
        get_func(DOWN, j);
        if(j != BOARD_SIZE - 1)
            printf(",");
        printf("\n");
    }
    printf("};\n");
    
    return 0;
};
