#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef LED;
EXTI_InitTypeDef EXT_INT;	
NVIC_InitTypeDef NVICstruct;	

void delay(uint32_t time){
	while(time--){
	}
}

void config(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);	

	LED.GPIO_Mode = GPIO_Mode_OUT;
	LED.GPIO_OType = GPIO_OType_PP;
	LED.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 | GPIO_Pin_0 | GPIO_Pin_1;
	LED.GPIO_PuPd = GPIO_PuPd_NOPULL;
	LED.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &LED);

	LED.GPIO_Mode = GPIO_Mode_IN;
	LED.GPIO_OType = GPIO_OType_PP;
	LED.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	LED.GPIO_PuPd = GPIO_PuPd_DOWN;	
	LED.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &LED);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource1);	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource2);	

	EXT_INT.EXTI_Line = EXTI_Line1;	
	EXT_INT.EXTI_LineCmd = ENABLE;
	EXT_INT.EXTI_Mode = EXTI_Mode_Interrupt;
	EXT_INT.EXTI_Trigger = EXTI_Trigger_Rising;	
	EXTI_Init(&EXT_INT);

	EXT_INT.EXTI_Line = EXTI_Line2;
	EXT_INT.EXTI_LineCmd = ENABLE;
	EXT_INT.EXTI_Mode = EXTI_Mode_Interrupt;
	EXT_INT.EXTI_Trigger = EXTI_Trigger_Rising;	
	EXTI_Init(&EXT_INT);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVICstruct.NVIC_IRQChannel = EXTI1_IRQn;	
												   
	NVICstruct.NVIC_IRQChannelCmd = ENABLE;		
	NVICstruct.NVIC_IRQChannelPreemptionPriority = 0;	
	NVICstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVICstruct);

	NVICstruct.NVIC_IRQChannel = EXTI2_IRQn;	
												
	NVICstruct.NVIC_IRQChannelCmd = ENABLE;		
	NVICstruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVICstruct.NVIC_IRQChannelSubPriority = 0;

	NVIC_Init(&NVICstruct);
}

void EXTI1_IRQHandler(void){

	if(EXTI_GetITStatus(EXTI_Line1) != RESET){
		int i = 0;

		do{
			GPIO_ToggleBits(GPIOD, GPIO_Pin_1);
			delay(16800000);	
			i++;
		}while(i < 5);		
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

void EXTI2_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line2) != RESET){
		int a = 0;
		
		do{
			GPIO_ToggleBits(GPIOD, GPIO_Pin_0);	
			delay(16800000);	
			a++;
		}while(a < 5);		

		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}

int main(void){
    config();

    while (1){
    	GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 );
    }
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  return -1;
}
