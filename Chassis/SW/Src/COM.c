#include "main.h"
#include <string.h>
#include "COM.h"
#include <stdio.h>
#include "lora.h"
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

void COM_TX(char string[])
{
	HAL_UART_Transmit(&huart2, (uint8_t *)string, strlen(string), 2000);
}	
void ARD_TX(char string[])
{
	char com_string[50];
	strcpy(com_string,string);
	int i = 0;
	for(i = 0; i!= strlen(string); i++)
	{
		if(com_string[i] == 0)
		{
			com_string[i] = '0';
		}
	}
	COM_TX("[ARD TX]: ");
	COM_TX(com_string);
	COM_TX("\r\n");
	
	HAL_UART_Transmit(&huart4, (uint8_t *)string, strlen(string), 1000);
}
void LORA_TX(char string[])
{
	COM_TX("[LORA TX]: ");
	COM_TX(string);
	//COM_TX("\r\n");
	
	HAL_UART_Transmit(&huart1, (uint8_t *)string, strlen(string), 1000);
}
void ADD_TX(char string[])
{
	COM_TX("[ADD TX]: ");
	COM_TX(string);
	COM_TX("\r\n");
	
	HAL_UART_Transmit(&huart3, (uint8_t *)string, strlen(string), 1000);
}	


char Lora_RxFlag(unsigned char set, unsigned char pos);

char Lora_Received(char rx, char check);
char Lora_Transmitted(char tx, char check);

char Lora_Init(void)
{
	static char SwitchPosInit = 1;
	volatile static char TX = 1;
	switch(SwitchPosInit)
	{
		case 1:
							if(TX)
							{
								TX = 0;
								LORA_TX("sys reset\r\n");
							}
							else
							{
								if(Lora_RxFlag(0,0))	//OK
								{									
									TX = 1;
									SwitchPosInit++;
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
		default:
			break;
		
		
	}
	return 0;
}

char Lora_RxFlag(unsigned char set, unsigned char pos)
{
	static unsigned char LoraRxFlags[10] = {0,0,0,0,0,0,0,0,0,0}; // 0: (random), 1: OK, 2: invalid_param, 3: radio_tx_ok, 4: radio_err, 5: radio_rx....
	
	if(set)
	{
		LoraRxFlags[pos] = 1;
		return 0;
	}
	else
	{
		char temp = LoraRxFlags[pos];
		LoraRxFlags[pos] = 0;
		return temp;
	}
}
extern TIM_HandleTypeDef htim3;
void Lora(void)
{
	static char InitDone = 1;
	static char Rx_Tx = 0;
	static char RxDone = 0;
	static char TxDone = 0;
	static char TxDone2 = 0;
	static char okreceived = 0;
	static char okreceived2 = 0;
	static char onetime = 0;
	static char wdtfirst = 1;
	static char rdydelay = 0;
	
	switch(InitDone)
	{
		case 1:
				if(lora_initial())
				{
					InitDone = 0;
					Rx_Tx = 1;
				}
				break;
		default:
				break;
			
	}
	
	if(InitDone == 0 && onetime == 1)
	{
		onetime = !(scheinwerfer(1));
	}
	
	switch(Rx_Tx)
	{
		case 1:
				if(!RxDone)
				{
					LORA_TX("radio rx 0\r\n");
					RxDone = 1;
				}
				else
				{
					if(Lora_RxFlag(0,1))
					{
						okreceived = 1;
						
					}
					if(okreceived)
					{
						if(Lora_RxFlag(0,5))
						{
							if(wdtfirst)
							{
								Rx_Tx = 3;
								RxDone = 0;
								okreceived = 0;
							}
							else
							{
								Rx_Tx++;
								
							}
							lora_delay(1);
						}
					}
				}
				break;
				
		case 2:
					if(!TxDone)
					{
						//if(Timer_reached(0))
						if(lora_delay(0))
						{
							Lora_DTS('D',52);
							
							//okreceived = 0;
							TxDone = 1;
						}
					}
					else
					{
						if(Lora_RxFlag(0,1))
						{
							okreceived = 1;
							
						}
						if(okreceived)
						{
							if(Lora_RxFlag(0,3))
							{
								//rdydelay = 1;
								okreceived = 0;
								TxDone = 0;
								Rx_Tx = 4;
							}
						}
					}
					/*if(rdydelay)
					{
						if(Lora_delay())
						{
							okreceived = 0;
							TxDone = 0;
							Rx_Tx--;
							rdydelay = 0;
						}
					}*/
					break;
		
		case 3:
					/*if(lora_setwdt())
					{	
						Rx_Tx = 2;
						onetime = 1;
						wdtfirst = 0;
					}*/
					Rx_Tx = 2;
		
		case 4:
					if(!TxDone2)
					{
						//if(Timer_reached(0))
						if(lora_delay(0))
						{
							Lora_DTS('D',52);
							
							//okreceived = 0;
							TxDone2 = 1;
						}
					}
					else
					{
						if(Lora_RxFlag(0,1))
						{
							okreceived2 = 1;
							
						}
						if(okreceived2)
						{
							if(Lora_RxFlag(0,3))
							{
								//rdydelay = 1;
								okreceived2 = 0;
								TxDone2 = 0;
								Rx_Tx = 1;
							}
						}
					}
					/*if(rdydelay)
					{
						if(Lora_delay())
						{
							okreceived = 0;
							TxDone = 0;
							Rx_Tx--;
							rdydelay = 0;
						}
					}*/
					break;
		default:
		break;
	}
	Send_Tim3Value();
}

void Lora_DTS(char name, char batLVL)
{
	char DTS[13] = {'r','a','d','i','o',' ','t','x',' ',name,batLVL,'\r','\n'}; 
	
	LORA_TX(DTS);
}

char Lora_delay(void)
{
	static uint32_t counter = 0;
	if(counter == 120000)
	{
		counter = 0;
		return 1;
	}
	else
	{
		counter++;
		return 0;
	}
}

char Ardunio_Ready(char set)
{
	static char ARDstate = 0;
	if(set)
	{
		ARDstate = 1;
	}
	return ARDstate;
}

void Arduino_Light_Fill(char value1, char value2, char value3)
{
	char ARDString[] = {'F', value1,value2,value3, value1,value2,value3, value1,value2,value3, value1,value2,value3, ';'};
	ARD_TX(ARDString);
}

void Arduino_Light_Clear()
{
	char ARDString[] = {'C'};
	ARD_TX(ARDString);
							
}

char Arduino_Light_Mode_Normal()
{
	static char ARDString[] = {'F', 255,255,255, 1,1,1, 252,117,3, 252,117,3, ';'};
	static char ARDString1[] = {'S', 15, 255,0,0,';'};
	static char ARDString2[] = {'S', 12, 255,0,0,';'};
	static char state = 1;
	
	switch(state)
	{
		case 1:
							if(Arduino_responded(0))
							{
								ARD_TX(ARDString);
								state++;
							}
							break;
		case 2: 	
							if(Arduino_responded(0))
							{
								ARD_TX(ARDString1);
								state++;
							}
							break;
		case 3:
							if(Arduino_responded(0))
							{
								ARD_TX(ARDString2);
								return 1;
							}
							break;
	}
	return 0;
}
void Arduino_Light_Mode_Connecting()
{
	char ARDString[] = {'F', 1,1,1, 1,1,1, 252,117,3, 252,117,3, ';'};
	ARD_TX(ARDString);
}
void Arduino_Light_Tansmitt()
{
	char ARDString[] = {'T'};
	ARD_TX(ARDString);
}

char scheinwerfer(char mode)
{
	static char state = 1;
	switch(state)
	{
		case 1:
							Arduino_Light_Clear();
							state++;
							break;
		case 2: 	
							if(Arduino_responded(0))
							{
								Arduino_Light_Tansmitt();
								switch(mode)
								{
									case 1: //normal
													state = 3;
													break;
									case 2: //ready/connecting
													state = 5;
													break;
									case 3: //all_white
													state = 7;
													break;
									default: state = 0;
								}
							}
							break;
		//----------------
		case 3:		
							if(Arduino_Light_Mode_Normal())
							{
								state++;
							}
							break;
		case 4: 	
							if(Arduino_responded(0))
							{
								Arduino_Light_Tansmitt();
								state = 0;
								return 1;
							}
							break;
		//----------------
		case 5:		if(Arduino_responded(0))
							{
								Arduino_Light_Mode_Connecting();
								state++;
							}
							break;
		case 6: 	
							if(Arduino_responded(0))
							{
								Arduino_Light_Tansmitt();
								state = 0;
								return 1;
							}
							break;
		//----------------
		case 7:		if(Arduino_responded(0))
							{
								Arduino_Light_Fill(255, 255, 255);
								state++;
							}
							break;
		case 8: 	
							if(Arduino_responded(0))
							{
								Arduino_Light_Tansmitt();
								state = 0;
								return 1;
							}
							break;
						
							
		default:
			break;
	}
	return 0;
}

char Arduino_responded(char set)
{
	static char state = 0;
	char temp = 0;
	if(set)
	{
		state = set;
		return 0;
	}
	else
	{
		temp = state;
		state = 0;
		return temp;
	}
}
