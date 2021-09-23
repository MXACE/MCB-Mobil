#include "main.h"
#include <string.h>
#include "stdio.h"
#include "COM.h"
#include "joystick.h"
#include "Math.h"
#include <stdlib.h>
#include "lora.h"

//#define Rotate45 -0.707f
#define Rotate45 0.707f
int JS_Values[4];

void Joystick (uint32_t *ADCValues, char mainLOOP)
{
	//1
			//[0] = left left/right (l=4100,r=0,m=2100)
			//[1] = left up/down (d=0,u=4100,m=2060)
			//[2] = right left/right (l=0,r=4100,m=2060)
			//[3] = right up/down (d=4100,u=0,m=2000)
	//2
			//[0] = left left/right (l=4100,r=0,m=2040)
			//[1] = left up/down (d=0,u=4100,m=2040)
			//[2] = right left/right (l=0,r=4100,m=2015)
			//[3] = right up/down (d=4100,u=0,m=2000)
	
	//MAX = 4096;
	//MID = 2048;
	//MIN = 0;
	
	#define AREA = 40;
	
	#define INV_X_LEFT 1
	#define INV_Y_LEFT 0
	#define INV_X_RIGHT 0
	#define INV_Y_RIGHT 1
	
	int i = 0;
	float percentage[4];
	volatile uint32_t NewValues[4];
	volatile float PreRotateValues[2];

	for(i = 0; i < 4; i++)
	{
		NewValues[i] = ADCValues[i] > 4100 ? 4100 : ADCValues[i];
	}

	if(INV_X_LEFT)
	{
		NewValues[0] = abs(4100-ADCValues[0]);
	}
	if(INV_Y_LEFT)
	{
		NewValues[1] = abs(4100-ADCValues[1]);
	}
	if(INV_X_RIGHT)
	{
		NewValues[2] = abs(4100-ADCValues[2]);
	}
	if(INV_Y_RIGHT)
	{
		NewValues[3] = abs(4100-ADCValues[3]);
	}
	
	PreRotateValues[0] = NewValues[0];
	PreRotateValues[0] = PreRotateValues[0] / 4100 * 100 - 50;
	
	PreRotateValues[1] = NewValues[1];
	PreRotateValues[1] = PreRotateValues[1] / 4100 * 100 - 50;
	
	//Left stick rotate 45 CCW
	percentage[0] = (PreRotateValues[0]*Rotate45 - PreRotateValues[1]*Rotate45);  //left x
	percentage[1] = (PreRotateValues[0]*Rotate45 + PreRotateValues[1]*Rotate45);  //left y
	
	percentage[2] = NewValues[2];
	percentage[2] = percentage[2] / 4100 * 100 - 50;
	
	percentage[3] = NewValues[3];
	percentage[3] = percentage[3] / 4100 * 100 - 50;
	
	/*percentage[0] -= 50;
	percentage[1] -= 50;
	percentage[2] -= 50;
	percentage[3] -= 50;*/
	
	
	for(i = 0; i!= 4; i++)
	{
		if(percentage[i] > 50)
		{
			percentage[i] = 50;
		}
		else if(percentage[i] < -50)
		{
			percentage[i] = -50;
		}
		if(percentage[i] <= 5 && percentage[i] >= -5)
		{
			percentage[i] = 0;
		}
	}
	
	
	for(i = 0; i!= 4; i++)
	{
		JS_Values[i] = percentage[i] * 2;
	}

	JS_Values[0] = JS_Values[0]*(-1);

	char ConBuffer[50];
	char DTS[50];
	for(i = 0; i < 50; i++)
	{
		DTS[i] = '\0';
	}

	sprintf(ConBuffer,"%i",JS_Values[0]);
	strcat(DTS, "A");
	strcat(DTS, ConBuffer);
	//COM_TX(ConBuffer);
	//COM_TX(" ");

	sprintf(ConBuffer,"%i",JS_Values[1]);
	strcat(DTS, "B");
	strcat(DTS, ConBuffer);
	//COM_TX(ConBuffer);
	//COM_TX(" ");

	sprintf(ConBuffer,"%i",JS_Values[2]);
	strcat(DTS, "C");
	strcat(DTS, ConBuffer);
	//COM_TX(ConBuffer);
	//COM_TX(" ");

	sprintf(ConBuffer,"%i",JS_Values[3]);
	strcat(DTS, "D");
	strcat(DTS, ConBuffer);
	//COM_TX(ConBuffer);
	//COM_TX("\r\n");



	COM_TX(DTS);
	COM_TX("\r\n");
	
	//Lora_DTS(1,'D', JS_Values[2], JS_Values[3], JS_Values[1]);
	//joystick_ready(1,JS_Values[0], JS_Values[2]);
	for(i = 0; i < 50; i++)
	{
		if(DTS[i] == '-') DTS[i] = 'F';
	}

	if(mainLOOP)
	{
		lora_DTS(1, DTS);
	}

}

/*
 * pos: 1: left_topleft
 * 		2: left_topright
 * 		3: right_x
 * 		4: right_y
 *
 * value: -100-100[%]
 *
 * aboveAllowed: def: value = js_value
 * 				 1: value < js_value
 * 				 2: value > js_value
 *
 * returns: 0 = true
 * 			1 = false
 */
char joystick_PosCheck(char pos, signed char value, char aboveAllowed)
{
	pos = pos > 3 ? 3 : pos;
	
	if(aboveAllowed == 1)
	{
		if(JS_Values[pos] >= value)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else if(aboveAllowed == 2)
	{
		if(JS_Values[pos] <= value)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		if(JS_Values[pos] == value)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
}
