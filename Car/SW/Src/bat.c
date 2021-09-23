#include "main.h"
#include "bat.h"
#include "com.h"
#include "stdio.h"
extern ADC_HandleTypeDef hadc1;

//extern ADC_ChannelConfTypeDef sConfig;
int BATCheck(uint32_t BatValues[6]);

void BatLED(char ADD)
{
	HAL_GPIO_WritePin(GPIOD, 0x1F, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, 0x00, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
	
	switch(ADD)
	{
		case 0x20:
			HAL_GPIO_WritePin(GPIOD, 0x01, GPIO_PIN_SET);
			break;
		
		case 0x10:
			HAL_GPIO_WritePin(GPIOD, 0x02, GPIO_PIN_SET);
		
		
		case 8:
			HAL_GPIO_WritePin(GPIOD, 0x04, GPIO_PIN_SET);
			
		
		case 4:
			HAL_GPIO_WritePin(GPIOD, 0x08, GPIO_PIN_SET);
			
		
		case 2:
			HAL_GPIO_WritePin(GPIOD, 0x10, GPIO_PIN_SET);
			
		
		case 1:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
			break;
	}
}

int SumBAT(uint32_t BatValues[6])
{
	static unsigned char Counter = 0;
	
	static uint32_t LastValues[6] = {0,0,0,0,0,0};
	
	static char FirstTime = 1;
	
	if(FirstTime)
	{
		LastValues[0] = BatValues[0];
		LastValues[1] = BatValues[1];
		LastValues[2] = BatValues[2];
		LastValues[3] = BatValues[3];
		LastValues[4] = BatValues[4];
		LastValues[5] = BatValues[5];
		
		FirstTime = 0;
	}
	else
	{
		LastValues[0] = (LastValues[0] + BatValues[0])/2;
		LastValues[1] = (LastValues[1] + BatValues[1])/2;
		LastValues[2] = (LastValues[2] + BatValues[2])/2;
		LastValues[3] = (LastValues[3] + BatValues[3])/2;
		LastValues[4] = (LastValues[4] + BatValues[4])/2;
		LastValues[5] = (LastValues[5] + BatValues[5])/2;
		
	}
	if(Counter >= 100)
	{
		Counter = 0;
		FirstTime = 1;
		
		/*LastValues[0] += 			//Cell6
		LastValues[1] += 				//cell5
		LastValues[2] += 				//cell4
		LastValues[3] += 				//cell3
		LastValues[4] += 				//cell2
		LastValues[5] += 74*/		//cell1
		
		if(BATCheck(LastValues))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		Counter++;
		return 0;
	}
}

/*

	S1 => 3.5V  = 2170				 4.2V  = 2610 | 2170	2258	2346	2434	2522
	S2 => 7V 	  = 277					 8.4V  = 333	| 277		288		299		310		322
	S3 => 10.5V = 255					 12.6V = 306	|	255		265		275		285		295
	S4 => 14V   = 257 				 16.8V = 308	|	257		267		277		286		296
	S5 => 17.5V = 236					 21V	 = 287	|	236		246		256		267		277
	S6 => 21V   = 235					 25.2V = 282	|	235		244		254		263		273

*/
int BATCheck(uint32_t BatValues[6])
{	
	char batOK[6] = {0,0,0,0,0,0};
	char batOK_Count = 0;
	
	char BatVoltageLVL[6] = {0,0,0,0,0,0};
	char CellAmount = 0;
	
	char BatLowest = 0;
	char stg[10];
	
	//Check Cell amount (4,5 or 6)
	if(257 < BatValues[2])	//Check for 4
	{
		if(236 < BatValues[1])	//Check for 5
		{
			if(235 < BatValues[0])	//Check for 6
			{
				CellAmount = 6;
			}
			else
			{
				CellAmount = 5;
			}
		}
		else
		{
			CellAmount = 4;
		}
	}
	CellAmount = 4;
	/*else
	{
		BatLED(0x20);
		return 0;
	}*/
	

	////////////////////////////////////////////////////////
	//Cell ok?
	if(235 < BatValues[0])			//Cell 6 ok?
	{
		if(244 < BatValues[0])
		{
			if(254 < BatValues[0])
			{
				if(263 < BatValues[0])
				{
					if(273 < BatValues[0])
					{
						BatVoltageLVL[0] = 5;
					}
					else
					{
						BatVoltageLVL[0] = 4;
					}
				}
				else
				{
					BatVoltageLVL[0] = 3;
				}
			}
			else
			{
				BatVoltageLVL[0] = 2;
			}
		}
		else
		{
			BatVoltageLVL[0] = 1;
		}
		batOK[0] = 1;
	}
	////////////////////////////////////////////////////////
	if(236 < BatValues[1])			//Cell 5 ok?
	{
		if(246 < BatValues[1])
		{
			if(256 < BatValues[1])
			{
				if(267 < BatValues[1])
				{
					if(277 < BatValues[1])
					{
						BatVoltageLVL[1] = 5;
					}
					else
					{
						BatVoltageLVL[1] = 4;
					}
				}
				else
				{
					BatVoltageLVL[1] = 3;
				}
			}
			else
			{
				BatVoltageLVL[1] = 2;
			}
		}
		else
		{
			BatVoltageLVL[1] = 1;
		}
		batOK[1] = 1;
	}
	////////////////////////////////////////////////////////
	if(257 < BatValues[2])			//Cell 4 ok?
	{	
		if(267 < BatValues[2])
		{
			if(277 < BatValues[2])
			{
				if(286 < BatValues[2])
				{
					if(296 < BatValues[2])
					{
						BatVoltageLVL[2] = 5;
					}
					else
					{
						BatVoltageLVL[2] = 4;
					}
				}
				else
				{
					BatVoltageLVL[2] = 3;
				}
			}
			else
			{
				BatVoltageLVL[2] = 2;
			}
		}
		else
		{
			BatVoltageLVL[2] = 1;
		}
		batOK[2] = 1;
	}
	batOK[2] = 1;
	BatVoltageLVL[2] = 5;
	////////////////////////////////////////////////////////
	if(255 < BatValues[3])			//Cell 3 ok?
	{
		if(265 < BatValues[3])
		{
			if(275 < BatValues[3])
			{
				if(285 < BatValues[3])
				{
					if(295 < BatValues[3])
					{
						BatVoltageLVL[3] = 5;
					}
					else
					{
						BatVoltageLVL[3] = 4;
					}
				}
				else
				{
					BatVoltageLVL[3] = 3;
				}
			}
			else
			{
				BatVoltageLVL[3] = 2;
			}
		}
		else
		{
			BatVoltageLVL[3] = 1;
		}
		batOK[3] = 1;
	}
	
	////////////////////////////////////////////////////////
	if(277 < BatValues[4])			//Cell 2 ok?
	{
		if(288 < BatValues[4])
		{
			if(299 < BatValues[4])
			{
				if(310 < BatValues[4])
				{
					if(322 < BatValues[4])
					{
						BatVoltageLVL[4] = 5;
					}
					else
					{
						BatVoltageLVL[4] = 4;
					}
				}
				else
				{
					BatVoltageLVL[4] = 3;
				}
			}
			else
			{
				BatVoltageLVL[4] = 2;
			}
		}
		else
		{
			BatVoltageLVL[4] = 1;
		}
		batOK[4] = 1;
	}
	/*sprintf(stg,"%i",BatValues[4]);
	COM_TX(stg);
	COM_TX("\r\n");*/
	////////////////////////////////////////////////////////
	if(2170 < BatValues[5])			//Cell 1 ok?
	{
		if(2258 < BatValues[5])
		{
			if(2346 < BatValues[5])
			{
				if(2434 < BatValues[5])
				{
					if(2522 < BatValues[5])
					{
						BatVoltageLVL[5] = 5;
					}
					else
					{
						BatVoltageLVL[5] = 4;
					}
				}
				else
				{
					BatVoltageLVL[5] = 3;
				}
			}
			else
			{
				BatVoltageLVL[5] = 2;
			}
		}
		else
		{
			BatVoltageLVL[5] = 1;
		}
		batOK[5] = 1;
	}
	
	////////////////////////////////////////////////////////
	
	//Check if all cells ok
	for(int i = 0; i != 6; i++)
	{
		if(batOK[i] == 1)
		{
			batOK_Count++;
		}
	}
	
	if(batOK_Count == CellAmount)
	{
		BatLowest = BatVoltageLVL[5];
		
		for(int i = 5; i != 6-CellAmount; i--)
    {
        if (BatVoltageLVL[i] < BatLowest)
        {
           BatLowest = BatVoltageLVL[i];
        }
    }
	}
	
	switch(BatLowest)
	{
		case 1:
			BatLED(0x01);
			break;
		case 2:
			BatLED(0x02);
			break;
		case 3:
			BatLED(0x04);
			break;
		case 4:
			BatLED(0x08);
			break;
		case 5:
			BatLED(0xf);
			break;
		default:
			BatLED(0x20);
	}
	
	if(batOK_Count == CellAmount)
	{
		return BatLowest;
	}
	else
	{
		return 0;
	}
}


// ZELLEN WERDEN RÜCKWÄRTS BERECHNET!

