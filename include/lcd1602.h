#ifndef __LCD1602_H_
#define __LCD1602_H_
#include <C8051F020.h>
#include <stdint.h>

//#define RS 0x03
//#define RW 0x02
//#define E  0x01
//#define CMD_PORT P6
//#define DAT_PORT P5

//#define CLR 0x01
//#define RET 0x02

//#define IN_MODE 0x04
//#define CURSOR_RIGHT 0x02
//#define CURSOR_LEFT 0x00
//#define SHIFT_LEFT 0x01
//#define SHIFT_RIGHT 0x00

#define DELAY_LCD 100

//#define ROW_LEN 2
//#define COLUMN_LEN 16


//void lcd1602_command(unsigned char);  
//void lcd1602_write(unsigned char);
//unsigned char lcd1602_read(void);
//unsigned char is_lcd_busy(void);
void lcd1602_init(void);
void lcd1602_clear();
void lcd1602_write_xy(uint8_t, uint8_t, unsigned char);
#endif
