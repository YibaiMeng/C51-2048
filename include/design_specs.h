#ifndef _DESIGN_SPECS_H
#define _DESIGN_SPECS_H

#define TILE_SIZE 71
#define MARGIN_SIZE 12
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480

#define BACKGROUND_COLOR_EMPTY 0xce16 // RGB: 0xcfc0b3
#define MARGIN_COLOR 0xbd73 //RGB :0xbcac9e

// 24bit RGB codes for color of the fonts and background of the different tiles.
// The codes are in the order of R,G and B. 
// For example, to get the G componet of the background_color of the tile 512, just access the 3 * log2(512/2) + 2 th element of background_colors. 
const __code uint16_t background_colors[] = {0xef3b,0xef19,0xf58f,0xf4ac,0xf3eb,0xf2e7,0xee6e,0xee6c,0xee4a,0xee27,0xee05}; // RGB: const __code uint8_t background_colors[] = {0xee,0xe4,0xda,0xed,0xe0,0xc8,0xf2,0xb1,0x79,0xf5,0x95,0x63,0xf6,0x7c,0x5f,0xf6,0x5e,0x3b,0xed,0xcf,0x72,0xed,0xcc,0x61,0xed,0xc8,0x50,0xed,0xc5,0x3f,0xed,0xc2,0x2e};
const __code uint16_t font_colors[] = {0x736c,0x736c,0xffbe,0xffbe,0xffbe,0xffbe,0xffbe,0xffbe,0xffbe,0xffbe,0xffbe};

// RGB: {0x77,0x6e,0x65,0x77,0x6e,0x65,0xf9,0xf6,0xf2,0xf9,0xf6,0xf2,0xf9,0xf6,0xf2,0xf9,0xf6,0xf2,0xf9,0xf6,0xf2,0xf9,0xf6,0xf2,0xf9,0xf6,0xf2,0xf9,0xf6,0xf2,0xf9,0xf6,0xf2};


#endif
