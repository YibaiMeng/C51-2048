#include <C8051F020.h>

#include "system.h"
#include "ili9486.h"

void main(void) {
    system_init();
    ili9486_init();
    dis_color(0xFF00);
    show_char(160, 240, 0x00FF, 'F');
    show_char(168, 240, 0x00FF, '/');
    show_char(176, 240, 0x00FF, '0');
    draw_rectangle(50, 50, 100, 100, 0x00FF);
    while (1) {
        draw_rectangle(50, 50, 100, 100, 0x00FF);
        delay(1000000);
        draw_rectangle(50, 50, 100, 100, 0x0000);
        delay(1000000);      
    }
}
