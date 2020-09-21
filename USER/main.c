#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "adc.h"
#include "dma.h"
#include "stm32f10x.h"
float ADC_ConvertedValueLocal[4];

extern volatile uint16_t ADCConvertedValue[10][4];

int main(void)
{
	int sum;
	int i,j;
	float temp[4];
	u16 adcx[4];

	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	LCD_Init();			 	
 	Adc_Init();		  		//ADC��ʼ��
	MyDMA_Init();
	
	//ADC_SoftwareStartConvCmd(ADC1,ENABLE); //�������ADCת��
	
	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(60,70,200,16,16,"ADC TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2019/4/19");	
	//��ʾ��ʾ��Ϣ
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	LCD_ShowString(60,130,200,16,16,"ADC_CH0_VAL:");	      
	LCD_ShowString(60,150,200,16,16,"ADC_CH0_VOL:0.000V");		
	
	while(1)
	{
		
		for(i=0;i<4;i++)
	 {
		sum=0;
		for(j=0;j<10;j++)
		{
			sum+=ADCConvertedValue[j][i];
			//sum/=10;
		  //LCD_ShowxNum(156,130,sum/10,4,16,0);//��ʾADC��ֵ
		  delay_ms(100);
		}					
		  temp[i]=(float)sum*(3.3/4096/10);			
	  	LCD_ShowxNum(156,150,temp[i],1,16,0);//��ʾ��ѹֵ		  
		
		//��ʾ��ѹֵ��С������	
		adcx[i]=temp[i];
		temp[i]-=adcx[i];
		temp[i]*=1000;		
		LCD_ShowxNum(172,150,temp[i],3,16,0X80);	
		LED0=!LED0;		
	 }
		delay_ms(250);
  }
}
