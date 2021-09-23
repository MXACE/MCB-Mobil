#include "main.h"
#include "CMDHandler.h"
#include "COM.h"
#include "bat.h"

void CH_BUFFER(char alpha[1],char uart)
{
	char chooseuart = uart-2;
	static char BUFFER[50][3];
	char StringToSend[50];
	static uint8_t BufPos = 0;
	uint8_t CMDdone = 0;
	
	if(alpha[0] == ';')
	{
		
		CMDdone = 1;
	}
	else if(alpha[0] == '\r')
	{
		
		
	}
	else
	{
		BUFFER[BufPos][chooseuart] = alpha[0];
		
		BufPos++;
	}
	
	if(CMDdone)
	{
		char i;
		for(i = 0; i!= 50; i++)
		{
			StringToSend[i] = BUFFER[i][chooseuart]; 
		}
		
		CH_HANDLER(1,StringToSend,chooseuart);
		BufPos = 0;
		
		
		for(i = 0; i!= 50; i++)
		{
			BUFFER[i][chooseuart] = 0;
		}
	}
}

void CH_HANDLER(char set, char string[], char uart)
{
	static uint8_t rdy[3] = {0,0,0};
	static char COM_BUFFER[50];
	static char ADD_BUFFER[50];
	static char ARD_BUFFER[50];
	
	if(set)
	{
		switch(uart)
		{
			case 0:
				strcpy(COM_BUFFER, string);
				rdy[0] = 1;
			
				/*COM_TX("[COM RX]: ");
				COM_TX(string);
				COM_TX("\r\n");*/
				break;
			
			case 1:
				strcpy(ADD_BUFFER, string);
				rdy[1] = 1;
				
				COM_TX("[ADD RX]: ");
				COM_TX(string);
				COM_TX("\r\n");
				break;
			
			case 2:
				strcpy(ARD_BUFFER, string);
				rdy[2] = 1;
			
				COM_TX("[ARD RX]: ");
				COM_TX(string);
				COM_TX("\r\n"); 
				break;
		}
	}
	else
	{
		//COM
		if(rdy[0])
		{
			rdy[0] = 0;
			if(!(strcmp(COM_BUFFER, "test")))
			{
				COM_TX("true\r\n");
			}
			if(!(strcmp(COM_BUFFER, "led")))
			{
				BatLED(4);
				COM_TX("LED set\r\n");
			}
		}
		//ADDITIONAL
		if(rdy[1])	
		{
			rdy[1] = 0;
		}	
		//ARDUINO
		if(rdy[2])	
		{
			rdy[2] = 0;
			if(!(strcmp(ARD_BUFFER, "start")))
			{
				Ardunio_Ready(1);
			}
			if(!(strcmp(ARD_BUFFER, "pong")))
			{
				Ardunio_Ready(1);
			}
			if(!(strcmp(ARD_BUFFER, "R")))
			{
				Arduino_responded(1);
			}
		}	
	}
}

void LORA_BUFFER(char alpha[1])
{
	static char BUFFER[50];
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

void LORA_HANDLER(char set, char string[])
{
	static uint8_t rdy = 0;
	
	static char LORA_BUFFER[50];
	static char LORA_RX_BUFFER[50];
	static char LORA_RX_EX_BUFFER[50];
	
	int pos = 0;
	
	if(set)
	{
		strcpy(LORA_BUFFER, string);
		strcpy(LORA_RX_BUFFER, string);
		
		LORA_RX_BUFFER[8] = '\0';
					
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
				for(pos = 8; LORA_BUFFER[pos] == '\r' || LORA_BUFFER[pos] == '\n' ; pos++)
				{
					LORA_RX_EX_BUFFER[pos-8] = LORA_BUFFER[pos];
				}
				Lora_RxFlag(1,5);
			}
			else
			{
				Lora_RxFlag(1,0);
			}
		}	
	}
}	
