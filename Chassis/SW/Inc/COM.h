#ifndef _COM_h_
#define _COM_h_

#include "main.h"
#include <string.h>

void COM_TX(char string[]);
void ARD_TX(char string[]);
void LORA_TX(char string[]);
void ADD_TX(char string[]);

char Lora_RxFlag(unsigned char set, unsigned char pos);

char Lora_Received(char rx, char check);

char Lora_Init(void);
void Lora(void);

void Lora_DTS(char name, char batLVL);
char Lora_delay(void);

char Ardunio_Ready(char set);
void Arduino_Light_Fill(char value1, char value2, char value3);
void Arduino_Light_Clear(void);
void Arduino_Light_Tansmitt(void);

char scheinwerfer(char mode);

char Arduino_responded(char set);

char Arduino_Light_Mode_Normal(void);
void Arduino_Light_Mode_Connecting(void);
#endif
