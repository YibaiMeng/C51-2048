/*
    Copyrighted Meng Yibai 2018, 2019
    Core logic functions for the game 2048
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "2048_core.h"

#ifndef __SDCC
#include <ncurses.h>
int row2 = 30;
#define DEBUG(...)  //mvprintw(row2++, 30, __VA_ARGS__); 
#else 
#define DEBUG(...)  printf(__VA_ARGS__)
#endif

#ifdef __SDCC
__xdata uint16_t score = 0;
#else
uint16_t score = 0;
#endif
/*
 * Function: concatenate
 * 
 *  Alters the series board[f[0]], board[f[1]], ... , board[f[concate_size - 1]
 *  in place so that they are concatenated. For example, 4, 4, 2, 0 turns to
 *  8, 2, 0, 0; 2, 2, 2, 0 turns to 4, 2, 0, 0; 4, 4, 8, 0 turns to 16, 0, 0, 0; The purpose of this is to
 *
 *  board: Pointer that points to the gameboard
 *  f: Array of ints. The f in the above 
 *  description. Space used will be freed later.
 *  concate_size: Ss the concate_size in the above description.
 *
 *  returns: Whether anything changed
 */
static bool concate(board_type board, uint8_t* f, bool check_only) {
    static __code const uint32_t score_table[] = {0, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096};
	uint8_t __data temp[BOARD_SIZE]; // make tmp and board the same type
	int i, j;
	bool ret;
	for(i = 0; i < BOARD_SIZE; i++) {
	    temp[i] = 0;
	}
	j = 0;
	for(i = 0; i < BOARD_SIZE; i++) {
	    if(board[f[i]] != 0) {
            temp[j] = board[f[i]];
            j++;
	    }
	    else
	       continue;
	}
	for(i = 0; i < j - 1;) {
	    if(temp[i] == temp[i + 1] && temp[i] != 0) {
	        temp[i] += 1;
	        if(check_only == 0) {
	            //DEBUG("[concate] FIRST Score is %i, and score_table  tmp i is%i\n", score, score_table[temp[i]]); 
	            score = score + score_table[temp[i]];// For each successful merge, points worth the value of the merged tile is added. I did not consult the src of the original！ I made up the rules myself.
                //DEBUG("[concate] NOW Score is %i, and tmp i is %i\n", score, score_table[temp[i]]); 
            }
		    for(int k = i + 1; k < j - 1; k++) {
		        temp[k] = temp[k+1];  
		    }
		    temp[j - 1] = 0;
		    continue;
	    }
	    i++;
	}
    //DEBUG("Temp array is: ");
    //DEBUG("\n");
	ret = false;
	for(i = 0; i < BOARD_SIZE; i++) {
        if(board[f[i]] != temp[i])
            ret = true;
        if(check_only == 0) {
            //DEBUG("Swapping!\n");
            //DEBUG("Index is %i\n",f[i]);
            board[f[i]] = temp[i];
        }
    }
	return ret;
}

/*
    Original function is below, optimized as a lookup table
    See lookup_table.c for generation code.
    
    int* get_func(uint8_t mv, int row_num) {
        First malloc a array of BOARD_SIZE, like int f[BOARD_SIZE];
        switch(mv) {
            case LEFT: {
                for(int i = 0; i < BOARD_SIZE; i++) {
                    f[i] = BOARD_SIZE * row_num + i;
                }	
                break;
            }
            case RIGHT: {
                for(int i = 0; i < BOARD_SIZE; i++) {
                    f[i] = BOARD_SIZE * row_num + BOARD_SIZE - 1 - i;
                }
                break;
            }
            case DOWN: {
                for(int i = 0; i < BOARD_SIZE; i++)
                {
                    f[i] = row_num + BOARD_SIZE * (BOARD_SIZE - 1 - i);
                }
                break;
            }
            case UP: {
                for(int i = 0; i < BOARD_SIZE; i++)
                {
                    f[i] = row_num + BOARD_SIZE * i;
                }
                break;
            }
        }
    return f;
    }
 */  
static uint8_t* get_func(uint8_t mv, uint8_t row_num) { 
    #ifndef __SDCC 
    static uint8_t lookup_table[][BOARD_SIZE][BOARD_SIZE] = {{
    #else
    static __code uint8_t lookup_table[][BOARD_SIZE][BOARD_SIZE] = {{
    #endif
    	    {0,1,2,3},
            {4,5,6,7},
            {8,9,10,11},
            {12,13,14,15}
        }, {
            {3,2,1,0},
            {7,6,5,4},
            {11,10,9,8},
            {15,14,13,12}
        }, {
            {0,4,8,12},
            {1,5,9,13},
            {2,6,10,14},
            {3,7,11,15}
        }, {
            {12,8,4,0},
            {13,9,5,1},
            {14,10,6,2},
            {15,11,7,3}
        }
     };
    return lookup_table[mv][row_num];
}


/*
 *Function: move_tile
 *--------------
 *
 * Alters the board according to the move given. Does nothing if can't move
 * in given direction.
 *
 * board: The 2048 board to alter.
 * mv: The move given.
 *
 * returns: Whether the move is possible/whether anything's changed.
 *
 */
bool move_tile(board_type board, uint8_t mv)
{
    int i;
    bool ret = false;
    DEBUG("[move_tile] Move number uint8_t mv is %i\n", mv);
    DEBUG("[move_tile]: Start moving tiles!\n");
    DEBUG("[move_tile]: Before moving, the board is: ");
    for(i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        DEBUG("%i ", board[i]);
    }
    DEBUG("\n");
    for(i = 0; i < BOARD_SIZE; i++) {
        if(concate(board, get_func(mv, i), false) == true)
            ret = true;
    }
    DEBUG("[move_tile]: After moving, the board is: ");
    for(i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        DEBUG("%i ", board[i]);
    }
    DEBUG("\n");
    return ret;    
}

/*
 * Function: add_random_tile
 *
 * Generate random tile if possible. CAUTION, must check if game is over before calling this function, or 
 * this function could block
 *
 * Original Code:
  
   GameManager.prototype.addRandomTile = function () {
      if (this.grid.cellsAvailable()) {
      var value = Math.random() < 0.9 ? 2 : 4;
      var tile = new Tile(this.grid.randomAvailableCell(), value);

      this.grid.insertTile(tile);
      }  
  };

 */
void add_random_tile(board_type board) {
    static bool init = 0;
    int r, value;
    if (init == 0) {
        DEBUG("[add_random_tile] Setting up seed!\n");
        srand(SEED); // TODO 有个时钟
        DEBUG("[add_random_tile] Seed set.\n");
        init = 1;
    }
    DEBUG("[add_random_tile] Getting random value\n");
    r = rand();
    DEBUG("[add_random_tile] Random value is %i.\n", r);
    DEBUG("[add_random_tile] Value of board at such point is %i\n", board[r % (BOARD_SIZE * BOARD_SIZE)]);
    value =  r < 0.9 * RAND_MAX ? 1 : 2;
    while(board[r % 16] != 0) {
        r = rand();
        //printf("r is %i\n", r);
        //printf("board is %i\n", board[r % (BOARD_SIZE * BOARD_SIZE)]);
    }
    DEBUG("[add_random_tile] Finally a valid place to place the new tile. id of tile is %i\n", r);
    board[r % 16] = value; 
    DEBUG("[add_random_tile] Value of the tile is %i \n", value);
}

/*
 * Function: game_ended
 *
 * Check if the game can proceed or not. That is, are there any possible moves left. 
 * 
 * TODO: a better algorithm perhaps?
 */

bool game_ended(board_type board) {
    int i,j;
    for(i = 0; i < BOARD_SIZE*BOARD_SIZE; i++) {
        if (board[i] == 0) {
            return 0;
        }
    }
    for(i = 0; i < 4; i++) {
        for(j = 0; j < BOARD_SIZE; j++) {
            if (concate(board, get_func(i, j), true))
                return 0;
        }
    }
    return 1;
}

void init_game(board_type board) {
    int i;
    for(i=0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        board[i] = 0;
    }
    printf("[init_game]: Setting score!\n");
    score = 0;
    printf("[init_game]: Adding random tile!\n");
    add_random_tile(board);
    add_random_tile(board);
    printf("[init_game]: Tile added!\n");
}


/* Example gameplay is as follows:
    define board here
    init_game();
    while(true) {
        if game_ended(board) {
            break and do stuff
        }
        print_board(board);
        int input;
        do {
             scanf("%i", &input);
        } while(move_tile(board, input) != true);
        draw_board(board);
        add_random_tile(board);
    } 
*/
