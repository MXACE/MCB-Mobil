/*
 * gfx.h
 *
 *  Created on: 22.12.2019
 *      Author: Laurin
 */

#ifndef INC_GFX_H_
#define INC_GFX_H_

#include <stdlib.h>

#include "ssd1351.h"
//#include "main.h"
#include <stdbool.h>
//#include "myCharSet.h"

typedef struct Color
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}Color;

typedef struct
{
    Color red;
    Color green;
    Color blue;
    Color cyan;
    Color magenta;
    Color yellow;
    Color black;
    Color white;
    Color gray;
}Colors;

void send_full_screen(void);
void blankscreen(Color color);
static inline void plot_dot_xy(uint8_t x, uint8_t y, Color color, uint8_t dwdot);
void filled_rect_xy_ab(uint8_t x, uint8_t y, uint8_t a, uint8_t b, Color color, uint8_t dwrect);
void line_from_to(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, Color color, uint8_t dwline);
bool get_bigger_difference(int16_t dx, int16_t dy);
uint8_t charxy(char c, uint8_t x, uint8_t y, Color fgcolor, Color bgcolor, uint8_t dwbgcolor, uint8_t dwchar);
void stringxy(char *string, uint8_t x, uint8_t y, Color fgcolor, Color bgcolor, uint8_t dwbgcolor);


#endif /* INC_GFX_H_ */
