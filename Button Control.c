#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef LED;
int counter = 0;

void config(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 

	LED.GPIO_Mode = GPIO_Mode_OUT; 
	LED.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	LED.GPIO_OType = GPIO_OType_PP;
	LED.GPIO_PuPd = GPIO_PuPd_NOPULL;
	LED.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &LED); 

	LED.GPIO_Mode = GPIO_Mode_IN; 
	LED.GPIO_OType = GPIO_OType_PP; 
	LED.GPIO_PuPd = GPIO_PuPd_DOWN; 
	LED.GPIO_Speed = GPIO_Speed_100MHz; 
	LED.GPIO_Pin = GPIO_Pin_0; 
	GPIO_Init(GPIOA, &LED); 
}

void delay(uint32_t time){
	while(time--){
	}
}

int main(void){
	config();
	
	while (1){
		int ButtonValue = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0); 
		
		if (ButtonValue == 1){
			delay(1680000); 
			counter++;
		
			switch(counter){
			    case 1:
			        GPIO_SetBits(GPIOD, GPIO_Pin_12); 
			        break;
			
			    case 2:
			    	GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 ); 
					break;
			
			    case 3:
					GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 ); 
					break;
			
			    case 4:
					GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14| GPIO_Pin_15 ); 
					break;
			
			    case 5:
					GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14| GPIO_Pin_15 ); 
			    	counter = 0;
			    	break;
		    }
		}
   }
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
	return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
	return -1;
}
