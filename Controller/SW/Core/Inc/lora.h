#ifndef _LORA_h_
#define _LORA_h_

#include "main.h"

extern char LORA_RX_EX_BUFFER;

char lora_init(void);

char Lora_RxFlag(unsigned char set, unsigned char pos);

void lora_err(void);


void lora_DTS(char sendStore, char dataJS[]);

char lora_addDATA(int pos, char set, int value);

#endif
