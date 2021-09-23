/*
 * gfx.c
 *
 *  Created on: 22.12.2019
 *      Author: Laurin
 */

#include "gfx.h"

#include "myCharSet.h"  //needs to be included here, or else compilation will fail

//extern global variables
extern Commands commands;
extern s_ssd1351 *fnptr_glob;

//global colors struct, can be used in other .c files with 'extern Colors colors;'
Colors colors =
{
    //black
    .black.red      = 0x00,//0x1F = maximal value
    .black.green    = 0x00,//0x3F = maximal value
    .black.blue     = 0x00,//0x1F = maximal value

    //gray
    .gray.red       = 0x05,
    .gray.green     = 0x0A,
    .gray.blue      = 0x05,

    //white
    .white.red      = 0x1F,
    .white.green    = 0x3F,
    .white.blue     = 0x1F,

    //red
    .red.red        = 0x3F,
    .red.green      = 0x00,
    .red.blue       = 0x00,

    //green
    .green.red      = 0x00,
    .green.green    = 0x3F,
    .green.blue     = 0x00,

    //blue
    .blue.red       = 0x00,
    .blue.green     = 0x00,
    .blue.blue      = 0x3F,

    //yellow
    .yellow.red     = 0x3F,
    .yellow.green   = 0x3F,
    .yellow.blue    = 0x00,

    //magenta
    .magenta.red    = 0x3F,
    .magenta.green  = 0x00,
    .magenta.blue   = 0x3F,

    //cyan
    .cyan.red       = 0x00,
    .cyan.green     = 0x3F,
    .cyan.blue      = 0x3F

};

/**
 *  @name   send_full_screen
 *  @brief  this function is not needed in this driver version (would be for sending displaybuffer)
 *  @author Laurin Heitzer
 *  @date   23.12.2019
 *
*/
void send_full_screen(void)
{
    set_cursor_std();
}

/**
 *  @name   blankscreen
 *  @brief  clears screen with specified color
 *  @author Laurin Heitzer
 *  @date   23.12.2019
 *
*/
void blankscreen(Color color)
{
    uint16_t ctrx = 0;
    uint16_t ctry = 0;

    for(ctry = 0; ctry < 128; ctry++)
    {
    	for(ctrx = 0; ctrx < 128; ctrx++)
    	{
    		plot_dot_xy(ctrx, ctry, color, 1);
    	}
    }
}

/**
 *  @name   plot_dot_xy
 *  @brief  draws single dot on display - dwdot can be ignored in this driver version
 *  @author Laurin Heitzer
 *  @date   23.12.2019
 *
*/
static inline void plot_dot_xy(uint8_t x, uint8_t y, Color color, uint8_t dwdot)
{
    if((x < 128) && (y < 128))      //check if coordinates are legal
    {
        x = 127 - x;		//invert display direction TODO: global direction bit for direction of display
        y = 127 - y;
    }

    if((x < 128) && (y < 128))
    {
    	send_sth(commands.SetColumn, 0);    //set collumn pointer
    	send_sth(x, 1);
    	send_sth(0x7F, 1);

    	send_sth(commands.SetRow, 0);       //set row pointer
    	send_sth(y, 1);
    	send_sth(0x7F, 1);

    	send_sth(commands.WriteRAM, 0);     //write in ram
    	send_sth((color.blue << 3) | (0x07 & (color.green >> 3)), 1);
    	send_sth((color.green << 5) | (0x1F & (color.red)), 1);

    }
}

/**
 *  @name   filled_rect_xy_ab
 *  @brief  draws a filled rectangle from origin x,y with sizes a,b - dwrect can be ignored in this driver version
 *  @author Laurin Heitzer
 *  @date   23.12.2019
 *
*/
void filled_rect_xy_ab(uint8_t x, uint8_t y, uint8_t a, uint8_t b, Color color, uint8_t dwrect)
{
    uint8_t aCtr = 0;
    uint8_t bCtr = 0;

    uint8_t NextX = x;

    if((x + a - 1) < 128 && (y + b - 1) < 128)  //check if coordinates are legal
    {
        for(bCtr = 0; bCtr < b; bCtr++)
        {
            for(aCtr = 0; aCtr < a; aCtr++)
            {
                plot_dot_xy(x + aCtr, y + bCtr, color, 0);
            }
        }

        if(dwrect) send_full_screen();
    }
}

/**
 *  @name   line_from_to
 *  @brief  draws a line from x1,y1 to x2,y2 with specified color - dwline can be ignored in this driver version
 *  @author Laurin Heitzer
 *  @date   23.12.2019
 *
*/
void line_from_to(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, Color color, uint8_t dwline)
{
    if((x1 < 128) && (x2 < 128) && (y1 < 128) && (y2 < 128))        //check if coordinates are legal
    {
    	int16_t ctr = 0;
        if(x1 > x2)
        {
            uint8_t tmp = x1;
            x1 = x2;
            x2 = tmp;

            tmp = y1;
            y1 = y2;
            y2 = tmp;
        }
        else if((x1 == x2) && !(y1 == y2))
        {
        	for(ctr = y1; ctr < y2; ctr++)
        	{
        		plot_dot_xy(x1, ctr, color, 0);
        	}
        }
        else if((y1 == y2) && !(x1 == x2))
        {
        	for(ctr = x1; ctr < x2; ctr++)
        	{
        		plot_dot_xy(ctr, y1, color, 0);
        	}
        }
        else if((x1 == x2) && (y1 == y2))
        {
        	plot_dot_xy(x1, y1, color, 0);
        }
        else
        {

			int16_t dx = x2 - x1;
			int16_t dy = y2 - y1;

			float m = (float)((float)dy/(float)dx);				//y = mx + b
			float b = (float)(y1 - (m * x1));

			if(get_bigger_difference(dx, dy))	//cycle through x-axis
			{
				for(ctr = x1; ctr <= x2; ctr++)
				{
					plot_dot_xy(ctr, (uint8_t)(m * (float)ctr + b), color, 0);	//y = mx + b
				}
			}
			else		//cycle through y-axis
			{
				for(ctr = y1; ctr <= y2; ctr++)
				{
					plot_dot_xy((uint8_t)(((float)ctr - b) / m), ctr, color, 0);	//x = (y - b)/m
				}
			}
        }
        if(dwline)send_full_screen();
    }
}

/**
 *  @name   get_bigger_difference
 *  @brief  get the bigger difference for line function calculating
 *  @author Laurin Heitzer
 *  @date   07.02.2020
 *
*/
bool get_bigger_difference(int16_t dx, int16_t dy)
{
	if(dx < 0) dx = dx * -1;
	if(dy < 0) dy = dy * -1;

	if(dx > dy) return 1;	//return 1 if x difference is bigger than y differnece
	if(dy > dx) return 0;	//return 0 if y differnece is bigger than x differnece
	if (dx == dy) return 1;	//reutrn 1 if x differnece is same as y differnrece (direction doesen't matter)
	return 1;	//return 1 to shut up compiler warning
}


/**
 *  @name   charxy
 *  @brief  core function of stringxy, only draws a single char at position x,y - dwchar can be ignored in this driver version
 *  @author Laurin Heitzer
 *  @date   23.12.2019
 *
*/
uint8_t charxy(char c, uint8_t x, uint8_t y, Color fgcolor, Color bgcolor, uint8_t dwbgcolor, uint8_t dwchar)
{
	uint8_t RowCtr = 0;
	uint8_t ColCtr = 0;
	uint8_t ArrPos = 0;
	uint8_t nextPos;

	if(c <= 'Z' && c >= 'A') {
		ArrPos = c - 'A';
	}
	else if(c <= 'z' && c >= 'a') {
		ArrPos = c - 'a' + 26;
	}
	else if(c <= '9' && c >= '0') {
		ArrPos = c -'0' + 52;
	}
	else if(c == '.') {
		ArrPos = 64;
	}
	else if(c == '%') {
		ArrPos = 63;
	}
	else if(c == '*') {
		ArrPos = 62;
	}
	else if(c == '>') {
		ArrPos = 66;
	}
	else if(c == '<') {
		ArrPos = 67;
	}
	else if(c == '-') {
		ArrPos = 68;
	}
	else {	//unknown character
		ArrPos = 65;
	}

	for(RowCtr = 0; RowCtr < 14; RowCtr++)
	{
		for(ColCtr = 0; ColCtr < 11; ColCtr++)
		{
			if(c != ' ')
			{
				if(chars_all[ArrPos].character[RowCtr][ColCtr]) plot_dot_xy(x + ColCtr, y + 13 - RowCtr, fgcolor, 0);
				else if(dwbgcolor) plot_dot_xy(x + ColCtr, y + 13 - RowCtr, bgcolor, 0);
			}
			else
			{
				if(dwbgcolor)
				{
					plot_dot_xy(x + ColCtr, y + 13 - RowCtr, bgcolor, 0);
				}
			}
		}
	}

	if(c != ' ')
	{
		nextPos = chars_all[ArrPos].to_next_char;
	}
	else
	{
		nextPos = 5;
	}

	return nextPos;
}

/**   
 *  @name   stringxy
 *  @brief  prints a string from origin x,y - character spacing not optimized
 *  @author Laurin Heitzer
 *  @date   23.12.2019
 *
*/
void stringxy(char *string, uint8_t x, uint8_t y, Color fgcolor, Color bgcolor, uint8_t dwbgcolor)
{
	uint8_t x_origin = x;

	uint8_t nextPos = 0;

	while(*string)
	{
		nextPos = charxy(*string++, x, y, fgcolor, bgcolor, dwbgcolor, 0);
		if(nextPos + x < 127)
		{
			x += nextPos;
		}
		else
		{
			y -= 13;
			x = x_origin;
		}
	}
	send_full_screen();
}
