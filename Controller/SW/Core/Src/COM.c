#include "main.h"
#include <string.h>
#include "COM.h"
#include <stdio.h>
#include "lora.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;

void COM_TX(char string[])
{
	HAL_UART_Transmit(&huart3, (uint8_t *)string, strlen(string), 2000);
}
void LORA_TX(char string[])
{
	COM_TX("[LORA TX]: ");
	COM_TX(string);
	//COM_TX("\r\n");
	
	HAL_UART_Transmit(&huart1, (uint8_t *)string, strlen(string), 2000);
}

//char Lora_RxFlag(unsigned char set, unsigned char pos);

//char Lora_Received(char rx, char check);
//char Lora_Transmitted(char tx, char check);

