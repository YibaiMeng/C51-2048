#include <C8051F020.h>

#include "system.h"

/*
void timer_init() {
    T4CON = 0;
    CKCON |= 0x40;
    RCAP4 = -counts;
    T4 = RCAP4;
    EIE2 |= 0x04;
    T4CON |= 0x04;
}*/

void system_init() {
    // Disable watchdog
    IE = 0;
    WDTCN = 0xde;
    WDTCN = 0xad;
    IE = 1;
    sysclk_init();
    xram_init();
    port_init();
    uart0_init();
    TI0 = 1;
    // TODO: Add all the other inits, controlled by marcos
}

void port_init() {
    XBR0 = 0x04; // 使能UART0
    // XBR1 = 0x00;
    XBR2 = 0x42; // 使用 P0-P3 作为总线，允许XBR，允许使用外部存储作为独占模式，P0.7 (/WR) 和 P0.6（/RD）被crossbar跳过了. 
    P0MDOUT = 0xC1; // 设置总线相关端口为推挽输出 P0.6 和 P0.7, TX推挽输出
    P1MDOUT = 0xFF; // 推挽
    P2MDOUT = 0xFF; // 推挽
    P3MDOUT = 0xFF; // 推挽
    // P74OUT = 0x00; // 开漏输出 P6和P5 
}

void xram_init() {
    EMI0CF = 0x1F; // 非复用总线，不使用内部 XRAM，即x:0x0000到x:0x0fff的区域使用的是片外内存。
    // See if speed is too slow?
    //EMI0TC = 0x41; // XRAM speed setting
}


void uart0_init() {
    SCON0 = 0x50; // UART0 as Mode 1 8-bit; ignore stop bit logic level; reception enabled;
    TMOD = 0x20;  // Timer 1 as baudrate generator
    TH1 = -(SYSCLK/BAUDRATE/16/12); // T1M set to 0; SMOD0 set to 1  
    PCON |= 0x80; // Set SMOD0 to 1
    TR1 = 1; // Start timer1    
}

/*
  Provided for printf
*/
int putchar(int c) {
    SBUF = c;
    while (!TI);
    TI = 0;
    return 1;
}

/*
   provided for scanf
*/
int getchar(void) {
    int c;
    while (RI0 != 1);
    c = SBUF;
    RI0 = 0;
    return c;
}

__xdata char line_buffer[LINE_BUFFER_LEN];
void getline() {
    int bt;
    for(bt = 0; bt < 20; bt++) {
        line_buffer[bt] = getchar();
        if(line_buffer[bt] == '\r' && getchar() == '\n') {
            line_buffer[bt] = '\0';
            break;
        }
    }
}

/*
    Set up the main clock the CPU uses. 
    This routine DOES NOT initalize timers and counters.
*/
void sysclk_init (void) {
    int i = 0;
    OSCXCN = 0x67; // Initalize the external oscillator detection circuit.
    for (i=0; i < 256; i++); // Wait approx. 1ms 
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



