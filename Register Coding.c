#include "stm32f4xx.h"	
#include "stm32f4_discovery.h"

GPIO_InitTypeDef LED;

void config(void){
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    GPIOD->MODER = 0b01010101000000000000000000000000; 
    GPIOD->OSPEEDR = 0b11111111000000000000000000000000;
    GPIOD->OTYPER = 0x00000000; 
    GPIOD->ODR = 000000000000000; 
}

void Delay(uint32_t time){
	while (time --){
	}
}

int main(void)
{
	config();
	
	while (1){
		GPIOD->ODR = 1111000000000000;	
		Delay(16805552);	
		GPIOD->ODR = 0000000000000000;	
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
