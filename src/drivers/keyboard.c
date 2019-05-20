#include <C8051F020.h>

#include "system.h"
#include "keyboard.h"

#define NO_KEY 255
static unsigned char _get_key() {
    unsigned char i;
    unsigned char key;
    const unsigned char __code dec[] = {0, 0, 1, 0, 2, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0};
    const unsigned char __code trans[] = {0xC, 9, 5, 1, 0xD, 0, 6, 2, 0xE, 0xA, 7, 3, 0xF, 0xB, 8, 4};
    KEYBOARD_PORT = 0x0F; // 低四位高电平输出
    delay(100); // 延时等待电平稳定
    i = ~KEYBOARD_PORT & 0x0F; // 获取低四位
    if (i == 0) 
        return NO_KEY; // 没有按键
    key = dec[i] * 4; // 转换为列值然后x4
    delay(10); // 延时去抖
    KEYBOARD_PORT = 0xF0; // 高四位高电平输出
    delay(100); // 延时
    i = ~KEYBOARD_PORT;
    i >>= 4; // 获取输入值
    if (i == 0) 
        return NO_KEY; // 没有按键
    key = key + dec[i]; // 计算出键码
    key = trans[key]; // 转换为真实键值
    
    if (key <= 9)
        return key + '0';
    else
        return key - 10 + 'A'; 

}
unsigned char get_key() {
    static unsigned char prev_key = NO_KEY;
    unsigned char key_pressed;
    key_pressed = _get_key();
    if (key_pressed != NO_KEY && key_pressed != prev_key) {
        prev_key = key_pressed;
        return key_pressed;
    }
    return NO_KEY;
}
