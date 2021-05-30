#ifndef _BAT_h_
#define _BAT_h_

#include "main.h"
#include "bat.h"

void BatLED(char ADD);

void InitADC(void);
int BATCheck(uint32_t BatValues[6]);
void BATNextChannel(void);

int SumBAT(uint32_t BatValues[6]);

#endif
