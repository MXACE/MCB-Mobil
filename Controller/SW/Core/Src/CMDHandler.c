#include "main.h"
#include "CMDHandler.h"
#include "COM.h"

void CH_BUFFER(char alpha[1])
{
	static char BUFFER[50];
	static uint8_t BufPos = 0;
	uint8_t CMDdone = 0;
	
	if(alpha[0] == ';')
	{
		
		CMDdone = 1;
	}
	else
	{
		BUFFER[BufPos] = alpha[0];
		
		BufPos++;
	}
	
	if(CMDdone)
	{		
		CH_HANDLER(1,BUFFER);
		BufPos = 0;
		
		int i = 0;
		for(i = 0; i!= 50; i++)
		{
			BUFFER[i] = 0;
		}
	}
}

void CH_HANDLER(char set, char string[])
{
	static uint8_t rdy = 0;
	static char COM_BUFFER[50];
	
	if(set)
	{
		strcpy(COM_BUFFER, string);
		rdy = 1;
	}
	else
	{
		//COM
		if(rdy)
		{
			rdy = 0;
			if(!(strcmp(COM_BUFFER, "test")))
			{
				COM_TX("true\r\n");
			}
			if(!(strcmp(COM_BUFFER, "led")))
			{
				COM_TX("LED set\r\n");
			}
			if(!(strcmp(COM_BUFFER, "reset")))
			{
				COM_TX("RESET\r\n");
				NVIC_SystemReset();
			}
		}
	}
}

void LORA_BUFFER(char alpha[1])
{
	static char BUFFER[100];
	static uint8_t BufPos = 0;
	uint8_t CMDdone = 0;
	
	if(alpha[0] == '\n')
	{
		
		CMDdone = 1;
	}
	else
	{
		BUFFER[BufPos] = alpha[0];
		
		BufPos++;
	}
	
	if(CMDdone)
	{
		BUFFER[BufPos-1] = '\0';
		LORA_HANDLER(1,BUFFER);
		BufPos = 0;
		
		char i;
		for(i = 0; i!= 50; i++)
		{
			BUFFER[i] = 0;
		}
	}
}

static char LORA_RX_EX_BUFFER[100];

void LORA_HANDLER(char set, char string[])
{

	static uint8_t rdy = 0;
	
	static char LORA_BUFFER[100];
	static char LORA_RX_BUFFER[100];
	

	unsigned int pos = 0;
	
	if(set)
	{
		strcpy(LORA_BUFFER, string);
		strcpy(LORA_RX_BUFFER, string);
		
		LORA_RX_BUFFER[8] = '\0';
		if(!(strcmp(LORA_RX_BUFFER, "radio_rx")))
		{
			for(pos = 9; LORA_BUFFER[pos] != '\r'; pos++)
			{
				LORA_RX_EX_BUFFER[pos-9] = LORA_BUFFER[pos];
			}
		}
			
		rdy = 1;
		
		COM_TX("[LORA RX]: ");
		COM_TX(string);
		COM_TX("\r\n");
		
	}
	else
	{
		if(rdy)
		{
			rdy = 0;
			
			if(!(strcmp(LORA_BUFFER, "ok")))
			{
				Lora_RxFlag(1,1);
			}
			else if(!(strcmp(LORA_BUFFER, "invalid_param")))
			{
				Lora_RxFlag(1,2);
			}
			else if(!(strcmp(LORA_BUFFER, "radio_tx_ok")))
			{
				Lora_RxFlag(1,3);
			}
			else if(!(strcmp(LORA_BUFFER, "radio_err")))
			{
				Lora_RxFlag(1,4);
			}
			else if(!(strcmp(LORA_RX_BUFFER, "radio_rx")))
			{
				Lora_RxFlag(1,5);
			}
			else
			{
				Lora_RxFlag(1,0);
			}
		}	
	}
}	
