/*
 * ssd1351.h
 *
 *  Created on: 22.12.2019
 *      Author: Laurin
 */

/**
*
*   @howto  to implement this library following functions need to be provided:
*           - write_pin_cs(uint8_t pinstate)
*           - write_pin_rs(uint8_t pinstate)
*           - write_pin_dc(uint8_t pinstate)
*           - delay_ms(uint32_t mstime)
*           - spi_transmit(uint8_t *data, uint32_t len)
*
*/


#ifndef INC_SSD1351_H_
#define INC_SSD1351_H_

//#include "main.h"
#include <stdint.h>
#include <stdbool.h>

#include "gfx.h"

#define OLED_RESET  (1<<2)
#define OLED_DC     (1<<3)
#define OLED_CS     (1<<4)

typedef struct
{
    uint8_t SetColumn;
    uint8_t SetRow;
    uint8_t WriteRAM;
    uint8_t ColorDepth;
    uint8_t SetStartLine;
    uint8_t SetDisplayOffset;
    uint8_t DisplayAllOff;
    uint8_t DisplayAllOn;
    uint8_t DisplayGDDRAM;
    uint8_t DisplayInvert;
    uint8_t SleepOn;
    uint8_t SleepOff;
    uint8_t SetPhase;
    uint8_t SetCommandLock;
    uint8_t SetBrightness;
    uint8_t DivSet;
}Commands;

typedef void (*write_pin)(uint8_t pinstate);
typedef void (*delay_ptr)(uint32_t delaytime);
typedef void (*spi_transmit)(uint8_t *data, uint32_t len);

typedef struct ssd1351
{
	write_pin pin_rs;
	write_pin pin_cs;
	write_pin pin_dc;
	delay_ptr delay;
	spi_transmit transmit_data;
}s_ssd1351;



void init_oled(uint8_t orientation, uint8_t framerate, s_ssd1351 *fnptrs);
void send_command(uint8_t cmd);
void send_data(uint8_t *data, uint16_t len);
void send_sth(uint8_t sth, uint8_t dc);
void set_cursor_std(void);

#endif /* INC_SSD1351_H_ */
