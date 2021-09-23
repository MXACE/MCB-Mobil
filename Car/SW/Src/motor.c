#include "main.h"
#include "motor.h"
#include "math.h"
#include "com.h"

////////////////////////////////////////////////////////////////////////
//Controll All
////////////////////////////////////////////////////////////////////////
	
void MOTOR_INIT(void)
{
	MOTOR_RESET(1);
	
	HAL_Delay(100);
	MOTOR_RESET(0);
	
	HAL_Delay(100);
	MOTOR_RESET(1);
	
	MOTOR_CURRENT(0);
	MOTOR_DECAY(1);
	
	MOTOR_SLEEP(1);
	
	MOTOR_ENABLE(1);
}

void MOTOR_STOP()
{
	MOTOR_CURRENT(0);
	MOTOR_RESET(0);
	MOTOR_ENABLE(0);
	MOTOR_SLEEP(0);
	
	COM_TX("Motor STOP");
}

void MOTOR_DRIVE(char FirstX, char FirstY, char SecX)
{
		/*
				1 ______ 4		 _
				 | 			|			/ \
				 | 	  	|			 |
				 | 	  	|			 |
				2|______|3
	
	DIR(0)
			1 = CK
			2 = CK
			3 = C
			4 = C
		*/
}

void MOTOR_STATE(char state)
{
	MOTOR_1_SLEEP(state);
	MOTOR_2_SLEEP(state);
	MOTOR_3_SLEEP(state);
	MOTOR_4_SLEEP(state);
	
}
void MOTOR_DECAY(uint8_t brake)
{
	MOTOR_1_BRAKE(brake);
	MOTOR_2_BRAKE(brake);
	MOTOR_3_BRAKE(brake);
	MOTOR_4_BRAKE(brake);
}
void MOTOR_CURRENT(uint8_t uCurrent)
{
	MOTOR_1_CURRENT(uCurrent);
	MOTOR_2_CURRENT(uCurrent);
	MOTOR_3_CURRENT(uCurrent);
	MOTOR_4_CURRENT(uCurrent);
}
void MOTOR_ENABLE(uint8_t enable)
{
	MOTOR_1_ENABLE(enable);
	MOTOR_2_ENABLE(enable);
	MOTOR_3_ENABLE(enable);
	MOTOR_4_ENABLE(enable);
}
void MOTOR_RESET(uint8_t reset)
{
	MOTOR_1_RESET(reset);
	MOTOR_2_RESET(reset);
	MOTOR_3_RESET(reset);
	MOTOR_4_RESET(reset);
}

void MOTOR_SLEEP(uint8_t sleep)
{
	MOTOR_1_SLEEP(sleep);
	MOTOR_2_SLEEP(sleep);
	MOTOR_3_SLEEP(sleep);
	MOTOR_4_SLEEP(sleep);
}

char MOTOR_FAULT()
{
	if(MOTOR_1_FAULT())
	{
		return 1;
	}
	if(MOTOR_1_FAULT())
	{
		return 2;
	}
	if(MOTOR_1_FAULT())
	{
		return 3;
	}
	if(MOTOR_1_FAULT())
	{
		return 4;
	}
	return 0;
}
////////////////////////////////////////////////////////////////////////
//MOTOR 1
////////////////////////////////////////////////////////////////////////

void MOTOR_1_CURRENT(uint8_t uCurrent)
{
	if(uCurrent > 100)
	{
		uCurrent = 100;
	}
	
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);
	
	if(uCurrent & 0x01)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_SET);
	}
	
	if(uCurrent & 0x02)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);
	}
	
	if(uCurrent & 0x04)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET);
	}
	
	if(uCurrent & 0x08)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
	}
	
	if(uCurrent & 0x10)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET);
	}
}

//-------------------------------------------------

void MOTOR_1_ENABLE(uint8_t EN)
{
	if(EN)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	}
}

//-------------------------------------------------

void MOTOR_1_DIR(uint8_t dir)
{
	if(dir)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET);
	}
}

//-------------------------------------------------

void MOTOR_1_BRAKE(uint8_t brake)
{
	if(brake)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);
	}
}

//-------------------------------------------------

void MOTOR_1_SLEEP(uint8_t sleep)
{
	if(sleep)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	}
}

//-------------------------------------------------

void MOTOR_1_RESET(uint8_t reset)
{
	if(reset)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
	}
}

//-------------------------------------------------

uint8_t MOTOR_1_FAULT(void)
{
	uint8_t temp = HAL_GPIO_ReadPin(GPIOC, 0);
	return temp;
}

////////////////////////////////////////////////////////////////////////
//MOTOR 2
////////////////////////////////////////////////////////////////////////

void MOTOR_2_CURRENT(uint8_t uCurrent)
{
	if(uCurrent > 100)
	{
		uCurrent = 100;
	}
	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
	
	if(uCurrent & 0x01)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	}
	
	if(uCurrent & 0x02)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
	}
	
	if(uCurrent & 0x04)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
	}
	
	if(uCurrent & 0x08)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
	}
	
	if(uCurrent & 0x10)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
	}
}

//-------------------------------------------------

void MOTOR_2_ENABLE(uint8_t EN)
{
	if(EN)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
	}
}

//-------------------------------------------------

void MOTOR_2_DIR(uint8_t dir)
{
	if(dir)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
	}
}

//-------------------------------------------------

void MOTOR_2_BRAKE(uint8_t brake)
{
	if(brake)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
	}
}

//-------------------------------------------------

void MOTOR_2_SLEEP(uint8_t sleep)
{
	if(sleep)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET);
	}
}

//-------------------------------------------------

void MOTOR_2_RESET(uint8_t reset)
{
	if(reset)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
	}
}

//-------------------------------------------------

uint8_t MOTOR_2_FAULT(void)
{
	uint8_t temp = HAL_GPIO_ReadPin(GPIOE, 8);
	return temp;
}

////////////////////////////////////////////////////////////////////////
//MOTOR 3
////////////////////////////////////////////////////////////////////////

void MOTOR_3_CURRENT(uint8_t uCurrent)
{
	if(uCurrent > 100)
	{
		uCurrent = 100;
	}
	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
	
	if(uCurrent & 0x01)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	}
	
	if(uCurrent & 0x02)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_SET);
	}
	
	if(uCurrent & 0x04)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);
	}
	
	if(uCurrent & 0x08)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);
	}
	
	if(uCurrent & 0x10)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);
	}
}

//-------------------------------------------------

void MOTOR_3_ENABLE(uint8_t EN)
{
	if(EN)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
	}
}

//-------------------------------------------------

void MOTOR_3_DIR(uint8_t dir)
{
	if(dir)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	}
}

//-------------------------------------------------

void MOTOR_3_BRAKE(uint8_t brake)
{
	if(brake)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	}
}

//-------------------------------------------------

void MOTOR_3_SLEEP(uint8_t sleep)
{
	if(sleep)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
	}
}

//-------------------------------------------------

void MOTOR_3_RESET(uint8_t reset)
{
	if(reset)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);
	}
}

//-------------------------------------------------

uint8_t MOTOR_3_FAULT(void)
{
	uint8_t temp = HAL_GPIO_ReadPin(GPIOB, 14);
	return temp;
}

////////////////////////////////////////////////////////////////////////
//MOTOR 4
////////////////////////////////////////////////////////////////////////

void MOTOR_4_CURRENT(uint8_t uCurrent)
{
	if(uCurrent > 100)
	{
		uCurrent = 100;
	}
	
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
	
	if(uCurrent & 0x01)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
	}
	
	if(uCurrent & 0x02)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
	}
	
	if(uCurrent & 0x04)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
	}
	
	if(uCurrent & 0x08)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
	}
	
	if(uCurrent & 0x10)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);
	}
}

//-------------------------------------------------

void MOTOR_4_ENABLE(uint8_t EN)
{
	if(EN)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
	}
}

//-------------------------------------------------

void MOTOR_4_DIR(uint8_t dir)
{
	if(dir)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
	}
}

//-------------------------------------------------

void MOTOR_4_BRAKE(uint8_t brake)
{
	if(brake)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
	}
}

//-------------------------------------------------

void MOTOR_4_SLEEP(uint8_t sleep)
{
	if(sleep)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	}
}

//-------------------------------------------------

void MOTOR_4_RESET(uint8_t reset)
{
	if(reset)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);
	}
}

//-------------------------------------------------

uint8_t MOTOR_4_FAULT(void)
{
	uint8_t temp = HAL_GPIO_ReadPin(GPIOC, 9);
	return temp;
}
