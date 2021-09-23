#include "main.h"
#include "com.h"
#include "lora.h"
char lora_initial()
{
	static char SwitchPosInit = 1;
	static char TX = 1;
	switch(SwitchPosInit)
	{
		case 1:
							if(TX)
							{
								//LORA_TX("\r\n");
								//HAL_Delay(100);
								LORA_TX("sys reset\r\n");
								
								TX = 0;
								
							}
							else
							{
								if(Lora_RxFlag(0,0))	//OK
								{									
									TX = 1;
									SwitchPosInit++;
									
								}
								else
								{
									
								}
							}
							break;
		case 2:
							if(TX)
							{
								
								LORA_TX("radio set freq 870000000\r\n");
								TX = 0;
							}
							else
							{
								if(Lora_RxFlag(0,1))	//OK
								{									
									TX = 1;
									SwitchPosInit++;
								}
							}
							break;
		case 3:
							if(TX)
							{
								LORA_TX("radio set pwr 15\r\n");
								TX = 0;
							}
							else
							{
								if(Lora_RxFlag(0,1))	//OK
								{									
									TX = 1;
									SwitchPosInit++;
								}
							}
							break;
		case 4:
							if(TX)
							{
								LORA_TX("radio set sf sf7\r\n");
								TX = 0;
							}
							else
							{
								if(Lora_RxFlag(0,1))	//OK
								{									
									TX = 1;
									SwitchPosInit++;
								}
							}
							break;
		case 5:
							if(TX)
							{
								LORA_TX("radio set afcbw 100\r\n");
								TX = 0;
							}
							else
							{
								if(Lora_RxFlag(0,1))	//OK
								{									
									TX = 1;
									SwitchPosInit++;
								}
							}
							break;
		case 6:
							if(TX)
							{
								LORA_TX("radio set wdt 0\r\n");
								TX = 0;
							}
							else
							{
								if(Lora_RxFlag(0,1))	//OK
								{									
									TX = 1;
									SwitchPosInit++;
								}
							}
							break;
		case 7:
							if(TX)
							{
								LORA_TX("mac pause\r\n");
								TX = 0;
							}
							else
							{
								if(Lora_RxFlag(0,0))	//OK
								{									
									TX = 1;
									SwitchPosInit++;
									return 1;
								}
							}
							break;
							
	}
	return 0;
}

char lora_setwdt()
{
	static char TX = 1;
	if(TX)
	{
		LORA_TX("radio set wdt 3000\r\n");
		TX = 0;
	}
	else
	{
		if(Lora_RxFlag(0,1))	//OK
		{									
			TX = 1;
			return 1;
		}
	}
	return 0;
}

extern TIM_HandleTypeDef htim3;

void Start_Timer()
{
	COM_TX("[TIM] start \r\n");
	HAL_TIM_Base_Start_IT(&htim3);
}

char Timer_reached(char set)
{
	char temp = 0;
	static char flag = 0;
	if(set)
	{
		//Send_Tim3Value();
		//COM_TX("[TIM] Limit reached \r\n");
		flag = set;
		return 0;
	}
	else
	{
		temp = flag;
		flag = 0;
		return temp;
	}
}

void Send_Tim3Value()
{
	char buffer[50];
	int timerValue = __HAL_TIM_GET_COUNTER(&htim3);
	sprintf(buffer,"%i",timerValue);
	//COM_TX(buffer);
	//COM_TX("\r\n");
}

char lora_delay(char set)
{
	static int newvalue = 0;
	char buffer[50];
	const int time = 800;
	int oldvalue = __HAL_TIM_GET_COUNTER(&htim3);
	
	/*sprintf(buffer,"%i",oldvalue);
	
	COM_TX(buffer);
	COM_TX("\r\n");*/
	if(set)
	{
		
		newvalue = oldvalue + time;
	
		if((oldvalue + time) > 1500)
		{
			newvalue = oldvalue - 1000;
		}
	}
	else
	{
		if( (newvalue+20 > oldvalue) && (newvalue-20 < oldvalue) )
		{
			return 1;
		}
	}
	return 0;
}
