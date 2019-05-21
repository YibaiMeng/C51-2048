/*
    

*/
#include <stdlib.h>

#include <C8051F020.h>

#include "system.h"
#include "ili9486.h"
#include "font.h"


/*
    Initailize the ili9486. TODO: Find out what it means and comment them.
*/    
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
    mydata = 0x01; // 0x00
    cmd = 0xB6;
    mydata = 0x02;
    mydata = 0x22;
    cmd = 0xC1;
    mydata = 0x41;
    cmd = 0xC5;
    mydata = 0x00;
    mydata = 0x07; // 0x18
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
    cmd = 0x2C; // Start write
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

void draw_rectangle(unsigned int x_l, unsigned int y_l, unsigned int width, unsigned int height, unsigned int color) {
    unsigned int x_h, y_h;
    long long int cnt;
    x_h = x_l + width - 1;
    y_h = y_l + height - 1;
    cmd = 0x2A; // set column address
    mydata = (x_l >> 8) & 1;
    mydata = (x_l & 0xFF);
    mydata = (x_h >> 8) & 1;
    mydata = x_h & 0xFF;
    cmd = 0x2B; // Set page address
    mydata = (y_l >> 8) & 1;
    mydata = (y_l & 0xFF);
    mydata = (y_h >> 8) & 1;
    mydata = y_h & 0xFF;
    cmd = 0x2C; // 开始写？
    cnt = (y_h - y_l + 1) * (x_h - x_l + 1);
    /*
        TODO: find out why a for loop would not work for certain values of width and height.
    */
    while (cnt > 0) {
        mydata = color >> 8;
        mydata = color & 0xFF;
        cnt--;
    }
}

/*
    Draw a image encoded with run length compression specified in res/run_length_compression.py
    
    Args:
        x_l, y_l: top-left coordinate of the image. See coordinates in
        width, height: width and height of the image. TODO: change the name to more readable ones.
        img: pointer to the image.
        plus_color: color for the '1's
        minus_color: color for the '0's 
    
    Returns:
        nothing.
*/
void draw_image(unsigned int x_l, unsigned int y_l, unsigned int width, unsigned int height, img_type img, color_type plus_color, color_type minus_color) {
    int8_t len; // Note the type, same as img_type. 
    long long int cnt; // Must be long enough to prevent overflow. 
    //x_h = x_h + x_l - 1; 
    //y_h = y_h + y_l - 1;
    color_type color;
    unsigned int x_h, y_h;
    x_h = x_l + width - 1;
    y_h = y_l + height - 1;
    cmd = 0x2A; // set column address
    mydata = (x_l >> 8) & 1;
    mydata = (x_l & 0xFF);
    mydata = ((x_l + width - 1) >> 8) & 1;
    mydata = (x_l + width - 1) & 0xFF;
    cmd = 0x2B; // set page address
    mydata = (y_l >> 8) & 1;
    mydata = (y_l & 0xFF);
    mydata = ((y_l + height - 1) >> 8) & 1;
    mydata = (y_l + height - 1) & 0xFF;
    cmd = 0x2C; // 开始写？
    cnt = width * height;
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
