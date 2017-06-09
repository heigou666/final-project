#include "ds18b20.h"
#include "lpc11xx.h"

uint8_t temp_sign;

//��ʱ
void delay_ds(uint16_t zz)          
{
	uint8_t xx;
	uint16_t yy; 
	
	for(xx=0;xx<1;xx++)
		for(yy=0;yy<zz;yy++);
}

//��λDS18B20
void DS18B20_Rst(void)	   
{   
	LPC_GPIO2->DIR|=(1<<5);	        //P2_5���
	DQ_LOW;         //����DQ
	delay_ds(500);    //�����������ߣ�520us��480~960uS��
	DQ_HIGH;                //DQ����
	delay_ds(70);    //�ͷ����ߣ���15~60uS��
}

//�ȴ�DS18B20�Ļ�Ӧ
//����1:δ��⵽DS18B20�Ĵ���
//����0:����
uint8_t DS18B20_Check(void) 	   
{   
	uint8_t retry=0;
	
	LPC_GPIO2->DIR&=~(1<<5);	// ����P2.5����Ϊ�������� 
	while(DQ_UP&&retry<200)
	{
		retry++;
		delay_ds(1);            //��ʱ
	};	 
	if(retry>=200)return 1;
	else retry=0;
  while(DQ_DOWN&&retry<250)
	{
		retry++;
		delay_ds(1);            //��ʱ
	};
	if(retry>=250)return 1;	    
	return 0;
}

//��ʼ��DS18B20
uint8_t DS18B20_Init(void)          
{
	LPC_GPIO2->DIR|=(1<<5);		   // P2.5Ϊ���������DS18B20��������
	LPC_GPIO2->DATA|=(1<<5);	   // P2.5�ø�
	DS18B20_Rst();                  //��λDS18B20
	return DS18B20_Check();         //���� ����Ƿ����DS18B20
} 

//дһ���ֽڵ�DS18B20
//dat��Ҫд����ֽ�
void DS18B20_Write_Byte(uint8_t dat)     
{             
  uint8_t j;
  uint8_t testb;
	LPC_GPIO2->DIR|=(1<<5);	            // P2.5Ϊ���
  for(j=1;j<=8;j++) 
	{
		testb=dat&0x01;
		dat=dat>>1;
		if (testb) 
		{
			DQ_LOW;         // Write 1
			delay_ds(2);      //��ʱ                      
			DQ_HIGH;        //��
			delay_ds(60);     //��ʱ        
		}
		else 
		{
			DQ_LOW;         // Write 0
			delay_ds(60);    //��ʱ         
			DQ_HIGH;        //��
			delay_ds(2);         //��ʱ                 
		}
  }
}

//��ʼ�¶�ת��
void DS18B20_Start(void)// ds1820 start convert
{   						               
    DS18B20_Rst();        //��λDS18B20	   
	DS18B20_Check();	    //�ȴ�DS18B20�Ļ�Ӧ
    DS18B20_Write_Byte(0xcc);   // skip rom
    DS18B20_Write_Byte(0x44);   // convert
} 

//��DS18B20��ȡһ��λ
//����ֵ��1/0
uint8_t DS18B20_Read_Bit(void) 			 
{
    uint8_t data;
	
	LPC_GPIO2->DIR|=(1<<5);	        //P2.5���
    DQ_LOW;         //����DQ
	delay_ds(2);        //��ʱ
    DQ_HIGH;                    //����DQ
	LPC_GPIO2->DIR&=~(1<<5);        //P2.5����
	delay_ds(12);           //��ʱ
	if(DQ_UP)   data=1;
        else data=0;	 
    delay_ds(50);           //��ʱ
    return data;
}

//��DS18B20��ȡһ���ֽ�
//����ֵ������������
uint8_t DS18B20_Read_Byte(void)    
{        
  uint8_t i,j,dat;
	
  dat=0;
	for(i=1;i<=8;i++) 
	{
    j=DS18B20_Read_Bit();
    dat=(j<<7)|(dat>>1);
  }						    
  return dat;
}

//��ds18b20�õ��¶�ֵ
//���ȣ�0.1C
//����ֵ���¶�ֵ ��-55~125��
int16_t DS18B20_Get_Temp(void)
{
  uint8_t TL,TH;
	int16_t tem;
	DS18B20_Start();                    // ds1820 start convert
	DS18B20_Rst();          //��λDS18B20
	DS18B20_Check();	    //����Ƿ����DS18B20
	DS18B20_Write_Byte(0xcc);   // skip rom
	DS18B20_Write_Byte(0xbe);   // convert	    
	TL=DS18B20_Read_Byte();     // LSB   
	TH=DS18B20_Read_Byte();     // MSB  
				
	if(TH>7)
	{
			TH=~TH;
			TL=~TL; 
			temp_sign=0;        //�¶�Ϊ��
	}else temp_sign=1;	        //�¶�Ϊ��
	tem=TH;             //��ø߰�λ
	tem<<=8;    
	tem+=TL;            //��õװ�λ
	tem=(float)tem*0.625;           //ת��
	if(temp_sign)return tem;        //�����¶�ֵ
	else return -tem;    
}






