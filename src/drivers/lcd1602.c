#include <stdint.h>

#include "lcd1602.h"
#include "system.h"

unsigned char is_lcd_busy() {
    P5 = 0xFF;
    P6 = 0x82;
    delay(DELAY_LCD);
    P6 = 0x83;
    delay(DELAY_LCD);
    return (P5 & 0x80);
}

void lcd1602_command(unsigned char Command) {
    while(is_lcd_busy());
    P5 = Command;
	P6 = 0x80; // RS=0, RW=0, EN=0
    delay(DELAY_LCD);
    // 延时
    P6 = 0x81; // RS=0, RW=0, EN=1
    delay(DELAY_LCD);
    P6 = 0x80; // RS=0, RW=0, EN=0
}

void lcd1602_write(unsigned char data) {
    P5 = data;
    P6 = 0x84; // RS=1, RW=0, EN=0
    delay(DELAY_LCD);
    P6 = 0x85; // RS=1, RW=0, EN=1
    delay(DELAY_LCD);
    P6 = 0x84; // RS=1, RW=0, EN=0
}

const unsigned char __code init_commands [7] = { 0x38, 0x08, 0x01, 0x06, 0x0C,0x80, 0x02};
void lcd1602_init() {
    int i;
    for(i = 0; i <  7; i++) {
        lcd1602_command(init_commands[i]);
    }
}

void lcd1602_write_xy(uint8_t row, uint8_t column, unsigned char data) {
    while(is_lcd_busy());
    if (row == 1)
        column |= 0xC0; // D7=1, 偏移地址为 0x40
    else
        column |= 0x80; // D7=1
    lcd1602_command((unsigned char)column); // 设置地址
    lcd1602_write(data); // 写入数据
}

void lcd1602_clear() {
    while(is_lcd_busy());
    lcd1602_command(0x01);
}
