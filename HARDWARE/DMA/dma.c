#include "dma.h"
volatile uint16_t ADCConvertedValue[10][4];
void MyDMA_Init(void)//配置DMA1_CHx
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA传输
	
	DMA_DeInit(DMA1_Channel1) ; //将DMA的通道1寄存器重设为缺省值

	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR);  //DMA外设基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue;  //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //数据传输方向，从外设发送到内存，该参数规定了外设是作为数据传输的目的地还是来源，此处作为来源
	DMA_InitStructure.DMA_BufferSize = 4*10;  //DMA通道的DMA缓存的大小,单位为数据单位。这里也就是ADCConvertedValue的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //数据宽度为16位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //数据宽度为16位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  //工作在循环模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMA通道 x拥有中优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMA通道x没有设置为内存到内存传输
	
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);  //根据DMA_InitStructure中指定的参数初始化DMA的通道
	  	
  DMA_Cmd(DMA1_Channel1,ENABLE);//启动DMA通道
}

