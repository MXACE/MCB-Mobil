#include "main.h"
#include "com.h"
#include "lora.h"
#include "CMDHandler.h"

void lora_err(void);

char lora_init()
{
	const char txlist[8][30] =
	{{'s','y','s',' ','r','e','s','e','t','\r','\n','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',},
	 {'r','a','d','i','o',' ','s','e','t',' ','f','r','e','q',' ','8','7','0','0','0','0','0','0','0','\r','\n','\0','\0','\0','\0',},
	 {'r','a','d','i','o',' ','s','e','t',' ','p','w','r',' ','1','5','\r','\n','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',},
	 {'r','a','d','i','o',' ','s','e','t',' ','s','f',' ','s','f','7','\r','\n','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',},
	 {'r','a','d','i','o',' ','s','e','t',' ','a','f','c','b','w',' ','1','0','0','\r','\n','\0','\0','\0','\0','\0','\0','\0','\0','\0',},
	 //{'r','a','d','i','o',' ','s','e','t',' ','w','d','t',' ','3','0','0','\r','\n','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',},
	 {'r','a','d','i','o',' ','s','e','t',' ','w','d','t',' ','0','\r','\n','\0','0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',},
	 {'m','a','c',' ','p','a','u','s','e','\r','\n','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',},
	 {'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',}};

	unsigned char cmd = 1;
	unsigned char stringCounter = 0;
	unsigned int counter = 0;

	char tempString[30];
	LORA_TX("sys reset\r\n");
	HAL_Delay(500);

	for(cmd = 1 ; cmd <= 5; cmd++)
	{
		for(stringCounter = 0; stringCounter <= 30; stringCounter++)
		{
			tempString[stringCounter] = txlist[cmd][stringCounter];
		}
		LORA_TX(tempString);

		while(counter < 60000 && !Lora_RxFlag(0,1) && cmd != 6)
		{
			LORA_HANDLER(0,"0");
			HAL_Delay(1);
			counter++;
		}
		if(counter >= 60000)
		{
			return 0;
		}
		counter = 0;
	}
	return 1;
}


char Lora_RxFlag(unsigned char set, unsigned char pos)
{
	static unsigned int LoraRxFlags[10] = {0,0,0,0,0,0,0,0,0,0}; // 0: (random), 1: OK, 2: invalid_param, 3: radio_tx_ok, 4: radio_err, 5: radio_rx....
	char buffer[50];
	int i = 0;
	
	/*for(i=0; i!= 10; i++)
	{
		buffer[i] = LoraRxFlags[i] + 48;
	}
	buffer[pos] = LoraRxFlags[pos] + 48;
	COM_TX(buffer);
	COM_TX("\r\n");*/

	if(set)
	{
		i = 0;
		for(i=0; i!= 10; i++)
		{
			LoraRxFlags[i] = 0;
		}
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

#define NAME_1 'D'

void lora_err(void)
{
	HAL_GPIO_WritePin(LED_C_GPIO_Port,LED_C_Pin,GPIO_PIN_SET);
	COM_TX("SHUTDOWN");
	while(1);
}

char lora_addDATA(int pos, char set, int value);

void lora_DTS(char sendStore, char dataJS[])
{
	static char buff[50];
	static char init = 1;
	int counter = 0;

	if(sendStore)
	{
		for(counter = 0; counter < 50; counter++)
		{
			buff[counter] = '\0';
		}

		strcat(buff, "radio tx ");
		strcat(buff, dataJS);

		if(lora_addDATA(0,0,0))
		{
			strcat(buff, "E1");
		}
		else
		{
			strcat(buff, "E0");
		}
		if(lora_addDATA(1,0,0))
		{
			strcat(buff, "F1");
		}
		else
		{
			strcat(buff, "F0");
		}
		__NOP();
		strcat(buff, "\r\n");
	}
	else
	{
		if(buff[0] != '\0')
		{
			char flagtemp = 0;

			LORA_TX("sys set pindig GPIO10 1\r\n");
			HAL_Delay(10);

			LORA_TX("mac pause\r\n");
			while(counter < 500 && !Lora_RxFlag(0,0))
			{
				counter++;
				HAL_Delay(1);
				LORA_HANDLER(0,"0");
			}
			if(counter >= 500)
			{
				lora_err();
			}
			counter = 0;

			LORA_TX(buff);
			//LORA_TX("radio tx AF90B0C0D53E0F1\r\n");
			while(!flagtemp && !Lora_RxFlag(0,4))
			{
				HAL_Delay(1);
				LORA_HANDLER(0,"0");
				flagtemp = Lora_RxFlag(0,3);
			}
			if(flagtemp)
			{
				COM_TX("[TX]: ");
				//COM_TX(LORA_RX_EX_BUFFER);
				COM_TX("\r\n");
			}
			else
			{
				lora_err();
			}
			LORA_TX("sys set pindig GPIO10 0\r\n");
		}
	}
}

// 0: headlight
// 1: handbreak
char lora_addDATA(int pos, char set, int value)
{
	static char init = 1;
	int counter = 0;
	static char values[20];

	if(init)
	{
		for(counter = 0; counter < 20; counter++)
		{
			values[counter] = 0;
		}
		init = 0;
	}


	if(set) values[pos] = value;
	else return values[pos];
	return 0;
}
