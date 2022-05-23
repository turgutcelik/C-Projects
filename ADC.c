#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef Pot;
ADC_InitTypeDef ADCStructure;
ADC_CommonInitTypeDef ADC_CommonStructure;

uint8_t ADC_DATA; 	

uint8_t Read_ADC(void){																			
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_56Cycles);	
	ADC_SoftwareStartConv(ADC1);	

	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET){
	}
	return ADC_GetConversionValue(ADC1);
}

void config(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	Pot.GPIO_Mode = GPIO_Mode_AN;	
	Pot.GPIO_OType = GPIO_OType_PP;
	Pot.GPIO_Pin = GPIO_Pin_0;	
	Pot.GPIO_PuPd = GPIO_PuPd_NOPULL;
	Pot.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &Pot);

	Pot.GPIO_Mode = GPIO_Mode_OUT;
	Pot.GPIO_OType = GPIO_OType_PP;
	Pot.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	Pot.GPIO_PuPd = GPIO_PuPd_NOPULL;
	Pot.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &Pot);

	ADC_CommonStructure.ADC_Mode = ADC_Mode_Independent;	
	ADC_CommonStructure.ADC_Prescaler = ADC_Prescaler_Div4;															  
	ADC_CommonInit(&ADC_CommonStructure);
	ADCStructure.ADC_Resolution = ADC_Resolution_8b; 	
	ADC_Init(ADC1, &ADCStructure);
	ADC_Cmd(ADC1, ENABLE);	
}

int main(void){
	config();
	GPIO_ResetBits(GPIOD, GPIO_Pin_All);	

    while (1){
    	ADC_DATA = Read_ADC();		

    	switch(ADC_DATA){
    		case 25:
    			GPIO_ResetBits(GPIOD, GPIO_Pin_All);
    			break;

    		case 75:
    			GPIO_SetBits(GPIOD, GPIO_Pin_12);
    			GPIO_ResetBits(GPIOD, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
    			break;

    		case 125:
    			GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13);
    			GPIO_ResetBits(GPIOD, GPIO_Pin_14 | GPIO_Pin_15);
    			break;

    		case 175:
    			GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
    			GPIO_ResetBits(GPIOD, GPIO_Pin_15);
    			break;

    		case 200:
    			GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
    			break;
    	}
    }
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  return -1;
}
