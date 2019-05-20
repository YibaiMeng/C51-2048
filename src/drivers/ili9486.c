#include <C8051F020.h>
#include <stdlib.h>
#include "system.h"
#include "ili9486.h"
#include "font.h"
    
/* ZHA cryptic comments */
void ili9486_init(void) {
    reset = 1;
    delay(200);
    reset = 0;
    delay(200);
    cmd = 0xF2;
    mydata = 0x18;
    mydata = 0xA3;
    mydata = 0x12;
    mydata = 0x02;
    mydata = 0xB2;
    mydata = 0x12;
    mydata = 0xFF;
    mydata = 0x10;
    mydata = 0x00;
    cmd = 0xF8;
    mydata = 0x21;
    mydata = 0x04;
    cmd = 0xF9;
    mydata = 0x00;
    mydata = 0x08;
    cmd = 0x36;
    mydata = 0x08;
    cmd = 0x3A;
    mydata = 0x05;
    cmd = 0xB4;
    mydata = 0x01;//0x00
    cmd = 0xB6;
    mydata = 0x02;
    mydata = 0x22;
    cmd = 0xC1;
    mydata = 0x41;
    cmd = 0xC5;
    mydata = 0x00;
    mydata = 0x07;//0x18
    cmd = 0xE0;
    mydata = 0x0F;
    mydata = 0x1F;
    mydata = 0x1C;
    mydata = 0x0C;
    mydata = 0x0F;
    mydata = 0x08;
    mydata = 0x48;
    mydata = 0x98;
    mydata = 0x37;
    mydata = 0x0A;
    mydata = 0x13;
    mydata = 0x04;
    mydata = 0x11;
    mydata = 0x0D;
    mydata = 0x00;
    cmd = 0xE1;
    mydata = 0x0F;
    mydata = 0x32;
    mydata = 0x2E;
    mydata = 0x0B;
    mydata = 0x0D;
    mydata = 0x05;
    mydata = 0x47;
    mydata = 0x75;
    mydata = 0x37;
    mydata = 0x06;
    mydata = 0x10;
    mydata = 0x03;
    mydata = 0x24;
    mydata = 0x20;
    mydata = 0x00;
    cmd = 0x11;
    delay(200);
    cmd = 0x29;
}

void dis_color(unsigned int c) {
    int i, j;
    cmd = 0x2C; // start write
    for (i = 0; i < 480; ++i)
        for (j = 0; j < 320; ++j) {
            mydata = c >> 8;
            mydata = c & 0xFF;
        }
}

// 左上右下  RGB 5 6 5 - > int 
void show_char(unsigned int x, unsigned int y, unsigned int color, unsigned char f) {
    unsigned char i, j, c;
    cmd = 0x2A; // set column address
    mydata = (x >> 8) & 1;
    mydata = (x & 0xFF);
    mydata = ((x + 7) >> 8) & 1;
    mydata = (x + 7) & 0xFF;
    cmd = 0x2B; // set page address
    mydata = (y >> 8) & 1;
    mydata = (y & 0xFF);
    mydata = ((y + 11) >> 8) & 1;
    mydata = (y + 11) & 0xFF;
    cmd = 0x2C;
    for (i = 0; i < 12; ++i) {
        c = font_8x12[f][i];
        for (j = 0; j < 8; ++j) {
            if (c & 1) {
                mydata = color >> 8;
                mydata = color & 0xFF;
            } else {
                mydata = 0xff;
                mydata = 0;
            }
            c = c >> 1;
        }
    }
}

void draw_rectangle(unsigned int x_l, unsigned int y_l, unsigned int x_h, unsigned int y_h, unsigned int color) {
    unsigned char i, j;
    x_h = x_l + x_h - 1;
    y_h = y_l + y_h - 1;
    cmd = 0x2A; // set column address
    mydata = (x_l >> 8) & 1;
    mydata = (x_l & 0xFF);
    mydata = (x_h >> 8) & 1;
    mydata = x_h & 0xFF;
    cmd = 0x2B; // set page address
    mydata = (y_l >> 8) & 1;
    mydata = (y_l & 0xFF);
    mydata = (y_h >> 8) & 1;
    mydata = y_h & 0xFF;
    cmd = 0x2C; // 开始写？
    for (i = 0; i < y_h - y_l + 1; ++i) {
        for (j = 0; j < x_h - x_l + 1; ++j) {
            mydata = color >> 8;
            mydata = color & 0xFF;
        }
    }
}

/*
    It is YOUR responsibility to make sure that x_l - x_h and y_l - y_h are of the appropriate length! It is non-trival to check these information from img!
*/
void draw_image(unsigned int x_l, unsigned int y_l, unsigned int x_h, unsigned int y_h, img_type img, color_type plus_color, color_type minus_color) {
    int8_t len; // Note the type, same as img_type. 
    long long int cnt; // Must be long enough to prevent overflow. 
    x_h = x_h + x_l - 1;
    y_h = y_h + y_l - 1;
    color_type color;
    cmd = 0x2A; // set column address
    mydata = (x_l >> 8) & 1;
    mydata = (x_l & 0xFF);
    mydata = (x_h >> 8) & 1;
    mydata = x_h & 0xFF;
    cmd = 0x2B; // set page address
    mydata = (y_l >> 8) & 1;
    mydata = (y_l & 0xFF);
    mydata = (y_h >> 8) & 1;
    mydata = y_h & 0xFF;
    cmd = 0x2C; // 开始写？
    cnt = (y_h - y_l + 1) * (x_h - x_l + 1);
    while (cnt > 0) {
        len = *img;
        if (len < 0) {
            color = minus_color;
        }
        else if (len > 0) {
            color = plus_color;
        }
        else {
            img++;
            continue;
        }
        len = abs(len);
        while(len > 0 && cnt > 0) {
            mydata = color >> 8;
            mydata = color & 0xFF;
            cnt--;
            len--;
        }
        img++;
    }
}
