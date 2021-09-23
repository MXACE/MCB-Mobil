/**
 * ssd1351.c
 *
 *  Created on: 22.12.2019
 *      Author: Laurin
 *  @version    0.2.2
 *  @brief      this and gfx.c/.h are an update to OLEDGFX.h
 *              this library needs to be initialized with the correct functionpointers
 */

#include "ssd1351.h"


extern Colors colors;

s_ssd1351 *fnptr_glob;

Commands commands =
{
    .SetColumn              = 0x15,
    .SetRow                 = 0x75,
    .WriteRAM               = 0x5C,
    .ColorDepth             = 0xA0,
    .SetStartLine           = 0xA1,
    .SetDisplayOffset       = 0xA2,
    .DisplayAllOff          = 0xA4,
    .DisplayAllOn           = 0xA5,
    .DisplayGDDRAM          = 0xA6,
    .DisplayInvert          = 0xA7,
    .SleepOn                = 0xAE,
    .SleepOff               = 0xAF,
    .SetPhase               = 0xB1,
    .SetCommandLock         = 0xFD,
    .SetBrightness          = 0xC7,
    .DivSet                 = 0xB3
};

/**
 *  @name   init_oled
 *  @brief  initializes 128x128 OLED with SSD1351 chip
 *  @author Laurin Heitzer
 *  @date   23.12.2019
 * 
 * TODO: implement framerate
 * TODO: implement orientation -> mb. global orientation property for gfx.h + orientation in ssd1351
 *
*/
void init_oled(uint8_t orientation, uint8_t framerate, s_ssd1351 *fnptrs)
{

	if(fnptrs == NULL)return;	//return if function pointer is empty

	fnptr_glob = fnptrs;

    //reset cycle of display

    fnptr_glob->pin_rs(1);
    fnptr_glob->pin_rs(0);
    fnptr_glob->delay(1000);
    fnptr_glob->pin_rs(1);
    fnptr_glob->pin_cs(1);
    fnptr_glob->delay(500);

    send_sth(commands.SetCommandLock, 0);   //set command lock
    send_sth(0xB1, 1);                      //unlock locked commands

    //TODO: implement framerate
    send_sth(commands.DivSet, 0);           //freq divset
    send_sth(0xF0, 1);                      //divide freq. by 1

    send_sth(commands.ColorDepth, 0);       //set re-map color depth
    send_sth(0x20, 1);                      //color depth to 262k color (565 rgb)

    send_sth(commands.SetStartLine, 0);     //set display start line
    send_sth(0x00, 1);                      //no offset

    send_sth(commands.SetDisplayOffset, 0); //set offset
    send_sth(0x00, 1);                      //no offset

    send_sth(commands.SetBrightness, 0);    //change brightness, contrast current control
    send_sth(0x0F, 1);                      //0x0F -> brightest, 0x00 -> dimmest

    blankscreen(colors.black);              //blank the screen (set whole GDDRAM to 0)

    set_cursor_std();                    //set cursor to standard limitations (0,0,127,127)

    send_sth(commands.DisplayGDDRAM, 0);    //tell to display GDDRAM
    send_sth(commands.SleepOff, 0);         //turn sleep off

}

/**
 *  @name   send_command
 *  @brief  for sending commands to ssd1351
 *  @author Laurin Heitzer
 *  @date   23.12.2019
 * 
*/
void send_command(uint8_t cmd)
{
	fnptr_glob->pin_cs(0);
	fnptr_glob->pin_dc(0);
	fnptr_glob->transmit_data(&cmd, 1);
	fnptr_glob->pin_cs(1);
}

/**
 *  @name   send_data
 *  @brief  for sending data to ssd1351 (should only be used after a command has been sent)
 *  @author Laurin Heitzer
 *  @date   23.12.2019
 * 
*/
void send_data(uint8_t *data, uint16_t len)
{
	fnptr_glob->pin_cs(0);
	fnptr_glob->pin_dc(1);
	fnptr_glob->transmit_data(data, len);
	fnptr_glob->pin_cs(1);
}

/**
 *  @name   send_sth
 *  @brief  send data or command, could be replaced with send_data and send_command
 *  @author Laurin Heitzer
 *  @date   23.12.2019
 * 
*/
void send_sth(uint8_t sth, uint8_t dc)
{
	fnptr_glob->pin_cs(0);
	fnptr_glob->pin_dc(dc);
	fnptr_glob->transmit_data(&sth, 1);
	fnptr_glob->pin_cs(1);
}

/**
 *  @name   set_cursor_std
 *  @brief  sets cursor in RAM of ssd1351 to standard (0,0,127,127)
 *  @author Laurin Heitzer
 *  @date   23.12.2019
 *
*/
void set_cursor_std(void)
{
    uint8_t TxBuff[2] = { 0 , 0 };

    TxBuff[0] = 0x00;
    TxBuff[1] = 127;
    send_command(commands.SetColumn);
    send_data(TxBuff, 2);		

    TxBuff[1] = 127;
    send_command(commands.SetRow);
    send_data(TxBuff, 2);

}
