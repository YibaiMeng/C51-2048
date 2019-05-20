#ifndef _ILI9486_H
#define _ILI9486_H

#include <stdint.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480

typedef __code const int8_t* img_type;
typedef uint16_t color_type;

unsigned char __xdata  __at (0x8003) reset;
unsigned char __xdata  __at (0x8002) cmd; //
unsigned char __xdata  __at (0x9002) mydata; // Write data to WDR

void ili9486_init();
void dis_color(unsigned int c);
void show_char(unsigned int x, unsigned int y, unsigned int color, unsigned char f);
void draw_rectangle(unsigned int x_l, unsigned int y_l, unsigned int width, unsigned int height, unsigned int color);
void draw_image(unsigned int x_l, unsigned int y_l, unsigned int width, unsigned int height, img_type img, color_type plus_color, color_type minus_color);

#endif
