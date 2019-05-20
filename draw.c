#include<stdio.h>
#include<stdlib.h>
#include "bmp.h"

#define DISPLAY_WIDTH 640
#define DISPLAY_HEIGHT 480
#define GRID_W 105
#define GRID_FILL 12
#define BLANK_FRONT 80
#define BLANK_BACK 560

//#define GRID_COLOR
#define FILL_COLOR 0xbbada0
//#define FONT_COLOR 
#define BG_COLOR 0xfaf8ef


void draw_board(int* board)
{
    int sz = bmp_size(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    void* picture = (void*) calloc(sz, sizeof(char));
    bmp_init(picture, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    for(int i = 0; i < DISPLAY_HEIGHT; i++)
       for(int j = 0; j < DISPLAY_WIDTH; j++)
	{
	    
	    if(j < BLANK_FRONT || j >= BLANK_BACK)
            {
	        bmp_set(picture, j, i, BG_COLOR);
	    }
	    else if ( i % (GRID_W + GRID_FILL) >= 0 && i % (GRID_W + GRID_FILL) < GRID_FILL)
	    {	
               	bmp_set(picture, j, i, FILL_COLOR);
	    }
	    else if((j - BLANK_FRONT) % (GRID_W + GRID_FILL) >= 0 && (j-BLANK_FRONT) % (GRID_W + GRID_FILL) < GRID_FILL )
            {
                bmp_set(picture, j, i, FILL_COLOR);
	    }	    
	    else
	     bmp_set(picture, j, i, 0xffffff);
	}
    // now set according to board
   
    
    FILE* fp = fopen("test.bmp", "wb");
    fwrite(picture, sizeof(char), sz, fp);
    fclose(fp);
    free(picture);

}
