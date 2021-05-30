#ifndef _motor_h_
#define _motor_h_

#include "main.h"
#include "motor.h"

void MOTOR_STATE(char state);
void MOTOR_DRIVE(char FirstX, char FirstY, char SecX);
void MOTOR_INIT(void);

void MOTOR_DECAY(uint8_t brake);
void MOTOR_ENABLE(uint8_t enable);
void MOTOR_CURRENT(uint8_t uCurrent);
void MOTOR_RESET(uint8_t reset);
void MOTOR_SLEEP(uint8_t sleep);
char MOTOR_FAULT(void);

void MOTOR_1_CURRENT(uint8_t uCurrent);
void MOTOR_1_ENABLE(uint8_t EN);
void MOTOR_1_DIR(uint8_t dir);
void MOTOR_1_BRAKE(uint8_t brake);
void MOTOR_1_SLEEP(uint8_t sleep);
void MOTOR_1_RESET(uint8_t reset);
uint8_t MOTOR_1_FAULT(void);

void MOTOR_2_CURRENT(uint8_t uCurrent);
void MOTOR_2_ENABLE(uint8_t EN);
void MOTOR_2_DIR(uint8_t dir);
void MOTOR_2_BRAKE(uint8_t brake);
void MOTOR_2_SLEEP(uint8_t sleep);
void MOTOR_2_RESET(uint8_t reset);
uint8_t MOTOR_2_FAULT(void);

void MOTOR_3_CURRENT(uint8_t uCurrent);
void MOTOR_3_ENABLE(uint8_t EN);
void MOTOR_3_DIR(uint8_t dir);
void MOTOR_3_BRAKE(uint8_t brake);
void MOTOR_3_SLEEP(uint8_t sleep);
void MOTOR_3_RESET(uint8_t reset);
uint8_t MOTOR_3_FAULT(void);

void MOTOR_4_CURRENT(uint8_t uCurrent);
void MOTOR_4_ENABLE(uint8_t EN);
void MOTOR_4_DIR(uint8_t dir);
void MOTOR_4_BRAKE(uint8_t brake);
void MOTOR_4_SLEEP(uint8_t sleep);
void MOTOR_4_RESET(uint8_t reset);
uint8_t MOTOR_4_FAULT(void);

#endif
