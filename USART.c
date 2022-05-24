#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char str[50];
GPIO_InitTypeDef RXTX;
USART_InitTypeDef USARTStructure;

uint16_t delay_cnt = 0;

void SysTick_Handler(void){
	if (delay_cnt > 0){
		delay_cnt--;
	}
}

void delay_ms(uint16_t delay){
	delay_cnt = delay;

	while(delay_cnt){
	}
}

void USART_Puts(USART_Typedef* USARTx, volatile char *s){
	while(*s){
		while(!(USARTx -> SR & 0x00000040));
		
		USART_SendData(USARTx, *s);
		*s++;
	}
}

void config(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	RXTX.GPIO_Mode = GPIO_Mode_AF;
	RXTX.GPIO_OType = GPIO_OType_PP;
	RXTX.GPIO_Pin = GPIO_Pin_2;
	RXTX.GPIO_PuPd = GPIO_PuPd_UP;
	RXTX.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOA, &RXTX);
	GPIO_PinAFConfig(GPIOA, GPIOA_PinSource2, GPIO_AF_USART2);

	USARTStructure.USART_BaudRate = 115200;
	USARTStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USARTStructure.USART_Mode = USART_Mode_Tx;
	USARTStructure.USART_Parity = USART_Parity_No;
	USARTStructure.USART_StopBits = USART_StopBits_1;
	USARTStructure.USART_WordLength = USART_WordLength_8b;

	USART_Init(USART2, &USARTStructure);
	USART_Cmd(USART2, ENABLE);
}

int main(void)
{
    SysTick_Config(SystemCoreClock/1000); 
    config();

    while (1){
    	sprintf(str, "Merhaba \n");
    	USART_Puts(USART2, str);
    	delay_ms(100);
  }
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
	return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
	return -1;
}
