#ifndef _SCREEN_h_
#define _SCREEN_h_

#include "main.h"
#include "ssd1351.h"
#include "gfx.h"

void screen_init(void);

void screen_connecting(void);
void screen_connected(void);

void screen_menu(char handbreak, char headlights);

char test_lora(void);
#endif
