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

void Lora(void);

void Lora_DTS(char set, char name, int jy1_x, int jy1_y, int jy2_x);
#endif
