#ifndef _CMDHANDLER_h_
#define _CMDHANDLER_h_

#include "main.h"
#include <string.h>

void CH_HANDLER(char set, char string[]);
void CH_BUFFER(char alpha[1]);

void LORA_HANDLER(char set, char string[]);
void LORA_BUFFER(char alpha[1]);
#endif
