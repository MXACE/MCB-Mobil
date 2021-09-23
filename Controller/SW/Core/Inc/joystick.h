#ifndef _JOYSTICK_h_
#define _JOYSTICK_h_

#include "main.h"
#include <string.h>
#include "stdio.h"
#include "COM.h"
#include "joystick.h"
#include "Math.h"
#include <stdlib.h>

#define Rotate45 0.707f
int JS_Values[4];

void Joystick (uint32_t *ADCValues, char mainLOOP);
char joystick_PosCheck(char pos, signed char value, char aboveAllowed);

#endif
