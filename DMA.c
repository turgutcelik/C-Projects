#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#define BufferLenght 1 	

GPIO_InitTypeDef GPIO_Structure;
ADC_InitTypeDef ADC_Structure;
ADC_CommonInitTypeDef ADC_CommonStructure;
DMA_InitTypeDef DMA_Structure;

uint16_t ADC1ConvertedValue[BufferLenght]; 

void config(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_Structure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_Structure.GPIO_Pin = GPIO_Pin_0;	
	GPIO_Init(GPIOA, &GPIO_Structure);
}

void ADC_DMA_config(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	

	DMA_DeInit(DMA2_Stream0);	
	DMA_Structure.DMA_Channel = DMA_Channel_0;	
	DMA_Structure.DMA_PeripheralBaseAddr = (uint32_t) &ADC1->DR; 	
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	  
	DMA_Structure.DMA_Memory0BaseAddr = (uint32_t) &ADC1ConvertedValue;
	DMA_Structure.DMA_DIR = DMA_DIR_PeripheralToMemory;		
	DMA_Structure.DMA_BufferSize = BufferLenght;	
	DMA_Structure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;																		   																												   bu sebeple disable edilmeli */
	DMA_Structure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	DMA_Structure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	
	DMA_Structure.DMA_MemoryDataSize = DMA_PeripheralDataSize_HalfWord;	
	DMA_Structure.DMA_Mode = DMA_Mode_Circular;		
	DMA_Structure.DMA_Priority = DMA_Priority_High;		
	DMA_Structure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_Structure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_Structure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_Structure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

	DMA_Init(DMA2_Stream0, &DMA_Structure);
	DMA_Cmd(DMA2_Stream0, ENABLE);

	ADC_DeInit();
	ADC_CommonStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;
	ADC_CommonInit(&ADC_CommonStructure);

	ADC_Structure.ADC_Resolution = ADC_Resolution_12b;
	ADC_Structure.ADC_ScanConvMode = ENABLE;
	ADC_Structure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_Structure.ADC_ExternalTrigConv = 0;
	ADC_Structure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_Structure.ADC_NbrOfConversion = BufferLenght;
	ADC_Init(ADC1, &ADC_Structure);

	ADC_DMACmd(ADC1, ENABLE);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_56Cycles);
	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
}

int main(void){
	config();
	ADC_DMA_config();
	ADC_SoftwareStartConv(ADC1);	

	while (1){
	}
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  return -1;
}
