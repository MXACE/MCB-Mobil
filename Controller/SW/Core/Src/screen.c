#include "main.h"
#include "ssd1351.h"
#include "gfx.h"
#include "screen.h"
#include "com.h"
extern Colors colors;

void screen_init()
{

		blankscreen(colors.cyan);
		stringxy("MCB Mobil",30,105,colors.white,colors.black,0);
		stringxy("V1.0",45,91,colors.white,colors.black,0);
		//filled_rect_xy_ab(3,79,119,17,colors.red,1);
		stringxy("O> Joysticks <O",5,50,colors.black,colors.red,0);
		
		line_from_to(20,75,110,75,colors.black,1);
		line_from_to(20,39,110,39,colors.black,1);
		
		//stringxy("MCB Mobil",30,105,colors.white,colors.black,0);
		
		//blankscreen(colors.black);
}	

void screen_connecting()
{
	static char counter = 0;
	static char first = 1;
	
	if(first)
	{
		//filled_rect_xy_ab(0,50,125,20,colors.cyan,1);
		stringxy("Setting up...",10,110,colors.white,colors.black,0);
		stringxy("LoRa",10,90,colors.white,colors.black,0);
		stringxy("Menu",10,75,colors.white,colors.black,0);
		stringxy("ADC - DMA",10,60,colors.white,colors.black,0);
		stringxy("Timer",10,45,colors.white,colors.black,0);
		HAL_Delay(20);
		first = 0;
	}
	switch(counter)
	{
		case 1:
						filled_rect_xy_ab(93,50,10,14,colors.cyan,1);
						counter++;
						break;
		case 2:
						stringxy(".",93,50,colors.white,colors.green,0);
						counter++;
						break;
		case 3:
						stringxy(".",98,50,colors.white,colors.green,0);
						counter = 1;
						break;
	}
	//HAL_Delay(20);
}
void screen_connected()
{
		stringxy("Connected",30,50,colors.white,colors.green,1);
}

void screen_menu(char handbreak, char headlights)
{
	static char first = 1;
	static char handbreak_old = 0;
	static char headlights_old = 0;
	
	if(first)
	{
		blankscreen(colors.white);
		stringxy("MCB Mobil",30,105,colors.black,colors.white,0);
		stringxy("V1.0",45,91,colors.black,colors.white,0);

		filled_rect_xy_ab(10,67,20,10,colors.gray,1);
		filled_rect_xy_ab(30,60,90,25,colors.gray,1);
		stringxy("Handbreak",45,64,colors.white,colors.gray,0);

		filled_rect_xy_ab(10,20,90,25,colors.gray,1);
		filled_rect_xy_ab(100,27,20,10,colors.gray,1);
		stringxy("Headlights",25,24,colors.white,colors.gray,0);
		first = 0;
	}

	if(handbreak_old != handbreak)
	{
		if(handbreak)
		{
			lora_addDATA(1,1,1);
			filled_rect_xy_ab(10,67,20,10,colors.green,1);
			filled_rect_xy_ab(30,60,90,25,colors.green,1);
			stringxy("Handbreak",45,64,colors.black,colors.green,0);
		}
		else
		{
			lora_addDATA(1,1,0);
			filled_rect_xy_ab(10,67,20,10,colors.gray,1);
			filled_rect_xy_ab(30,60,90,25,colors.gray,1);
			stringxy("Handbreak",45,64,colors.white,colors.gray,0);
		}
		handbreak_old = handbreak;
	}

	if(headlights != headlights_old)
	{
		if(headlights)
		{
			lora_addDATA(0,1,1);
			filled_rect_xy_ab(10,20,90,25,colors.green,1);
			filled_rect_xy_ab(100,27,20,10,colors.green,1);
			stringxy("Headlights",25,24,colors.black,colors.green,0);
		}
		else
		{
			lora_addDATA(0,1,0);
			filled_rect_xy_ab(10,20,90,25,colors.gray,1);
			filled_rect_xy_ab(100,27,20,10,colors.gray,1);
			stringxy("Headlights",25,24,colors.white,colors.gray,0);
		}
		headlights_old = headlights;
	}
}



