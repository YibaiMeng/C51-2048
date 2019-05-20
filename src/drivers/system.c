#include <C8051F020.h>

#include "system.h"

void system_init() {
    // Disable watchdog.
    IE = 0;
    WDTCN = 0xde;
    WDTCN = 0xad;
    IE = 1;
    sysclk_init();
    xram_init();
    port_init();
    // TODO: Add all the other inits, controlled by marcos
}

void port_init() {
    XBR2 = 0x42; // 使用 P0-P3 作为总线，允许XBR，允许使用外部存储作为独占模式，P0.7 (/WR) 和 P0.6（/RD）被crossbar跳过了. 
    P0MDOUT = 0xC0; // 设置总线相关端口为推挽输出 P0.6 和 P0.7
    P1MDOUT = 0xFF; // 推挽
    P2MDOUT = 0xFF; // 推挽
    P3MDOUT = 0xFF; // 推挽
    //P74OUT = 0x00; // 开漏输出 P6和P5 
}

void xram_init() {
    EMI0CF = 0x1F; // 非复用总线，不使用内部 XRAM，即x:0x0000到x:0x0fff的区域使用的是片外内存。
    EMI0TC = 0x41; // XRAM speed setting
}


/*
    Set up the main clock the system (CPU) uses. 

    This routine DOES NOT initalize timers and counters.
*/
void sysclk_init (void) {
    int i = 0;
    OSCXCN = 0x67; // Initalize the external oscillator detection circuit.
    for (i=0; i < 256; i++); // Wait 1ms 
    while (!(OSCXCN & 0x80)); // Poll for XTLVLD to become 1
    OSCICN = 0x88; // Switch to using the external oscillator
}

/*
    A crude delay function.
    Roughly m / k
*/
void delay(int k) {
    int i;
    for (i = 0; i < k; ++i);
}
