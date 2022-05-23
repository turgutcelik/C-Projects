#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef LED;
DAC_InitTypeDef DACStructure;

int i = 0;

void config(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);		

	LED.GPIO_Mode = GPIO_Mode_OUT;
	LED.GPIO_OType = GPIO_OType_PP;
	LED.GPIO_PuPd = GPIO_PuPd_NOPULL;
	LED.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &LED);

	DACStructure.DAC_Trigger = DAC_Trigger_None;
	DACStructure.DAC_WaveGeneration	= DAC_WaveGeneration_None; 	
	DACStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;															 
	DAC_Init(DAC_Channel_1, &DACStructure);		
	DAC_Cmd(DAC_Channel_1, ENABLE);
}

void delay(uint32_t time){
	while(time--){
	}
}

int main(void){
    config();

    while(1){
    	for(i = 2000; i < 4095; i += 100){
    		DAC_SetChannel1Data(DAC_Align_12b_R, i);
    	}
    	i = 2000;
    }
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  return -1;
}
