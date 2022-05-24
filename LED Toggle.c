#include "stm32f4xx.h"	
#include "stm32f4_discovery.h"

GPIO_InitTypeDef LED;	

void config(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	LED.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	LED.GPIO_Mode = GPIO_Mode_OUT;
	LED.GPIO_OType = GPIO_OType_PP; 
	LED.GPIO_Speed = 0x03;	
	GPIO_Init(GPIOD, &LED);	
}

void Delay(uint32_t time){
	while (time --){
	}
}

int main(void)
{
	config();
	
	while (1){
		GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);	
		Delay(16805552);	
		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);	
		Delay(16805552);
		
		GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		Delay(16805552);
	}
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
	return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
	return -1;
}
