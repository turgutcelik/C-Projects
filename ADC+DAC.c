#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef LED;
ADC_InitTypeDef ADCStructure;
ADC_CommonInitTypeDef ADCCommonStructure;
DAC_InitTypeDef DACStructure;

uint8_t ADC_DATA;
uint16_t DAC_DATA;

uint32_t map(long A, long B, long C, long D, long E){
	return (A*E)/C;
}

uint16_t Read_ADC(void){
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_56Cycles);
	ADC_SoftwareStartConv(ADC1);

	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET){
	}

	return ADC_GetConversionValue(ADC1);
}

void config(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);	

	LED.GPIO_Mode = GPIO_Mode_OUT;
	LED.GPIO_OType = GPIO_OType_PP;
	LED.GPIO_Pin = GPIO_Pin_4;
	LED.GPIO_PuPd = GPIO_PuPd_NOPULL;
	LED.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &LED);

	LED.GPIO_Mode = GPIO_Mode_AN;
	LED.GPIO_OType = GPIO_OType_PP;
	LED.GPIO_Pin = GPIO_Pin_0;	
	LED.GPIO_PuPd = GPIO_PuPd_NOPULL;
	LED.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &LED);

	ADCCommonStructure.ADC_Mode = ADC_Mode_Independent;
	ADCCommonStructure.ADC_Prescaler = ADC_Prescaler_Div4;
	ADC_CommonInit(&ADCCommonStructure);
	ADCStructure.ADC_Resolution = ADC_Resolution_8b;
	ADC_Init(ADC1, &ADCStructure);
	ADC_Cmd(ADC1, ENABLE);

	DACStructure.DAC_Trigger = DAC_Trigger_None;
	DACStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DACStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_1, &DACStructure);
	DAC_Cmd(DAC_Channel_1, ENABLE);
}

int main(void){
	config();

	while (1){
		ADC_DATA = Read_ADC();
		DAC_DATA = map(ADC_DATA, 0 , 255, 0 , 4095);
		DAC_SetChannel1Data(DAC_Align_12b_R, DAC_DATA);
  }
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  return -1;
}
