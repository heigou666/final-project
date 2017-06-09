#include "ds18b20.h"
#include "lpc11xx.h"

uint8_t temp_sign;

//延时
void delay_ds(uint16_t zz)          
{
	uint8_t xx;
	uint16_t yy; 
	
	for(xx=0;xx<1;xx++)
		for(yy=0;yy<zz;yy++);
}

//复位DS18B20
void DS18B20_Rst(void)	   
{   
	LPC_GPIO2->DIR|=(1<<5);	        //P2_5输出
	DQ_LOW;         //拉低DQ
	delay_ds(500);    //主机拉低总线，520us（480~960uS）
	DQ_HIGH;                //DQ拉高
	delay_ds(70);    //释放总线，（15~60uS）
}

//等待DS18B20的回应
//返回1:未检测到DS18B20的存在
//返回0:存在
uint8_t DS18B20_Check(void) 	   
{   
	uint8_t retry=0;
	
	LPC_GPIO2->DIR&=~(1<<5);	// 设置P2.5引脚为输入引脚 
	while(DQ_UP&&retry<200)
	{
		retry++;
		delay_ds(1);            //延时
	};	 
	if(retry>=200)return 1;
	else retry=0;
  while(DQ_DOWN&&retry<250)
	{
		retry++;
		delay_ds(1);            //延时
	};
	if(retry>=250)return 1;	    
	return 0;
}

//初始化DS18B20
uint8_t DS18B20_Init(void)          
{
	LPC_GPIO2->DIR|=(1<<5);		   // P2.5为输出，用作DS18B20数据引脚
	LPC_GPIO2->DATA|=(1<<5);	   // P2.5置高
	DS18B20_Rst();                  //复位DS18B20
	return DS18B20_Check();         //返回 检测是否存在DS18B20
} 

//写一个字节到DS18B20
//dat：要写入的字节
void DS18B20_Write_Byte(uint8_t dat)     
{             
  uint8_t j;
  uint8_t testb;
	LPC_GPIO2->DIR|=(1<<5);	            // P2.5为输出
  for(j=1;j<=8;j++) 
	{
		testb=dat&0x01;
		dat=dat>>1;
		if (testb) 
		{
			DQ_LOW;         // Write 1
			delay_ds(2);      //延时                      
			DQ_HIGH;        //高
			delay_ds(60);     //延时        
		}
		else 
		{
			DQ_LOW;         // Write 0
			delay_ds(60);    //延时         
			DQ_HIGH;        //高
			delay_ds(2);         //延时                 
		}
  }
}

//开始温度转换
void DS18B20_Start(void)// ds1820 start convert
{   						               
    DS18B20_Rst();        //复位DS18B20	   
	DS18B20_Check();	    //等待DS18B20的回应
    DS18B20_Write_Byte(0xcc);   // skip rom
    DS18B20_Write_Byte(0x44);   // convert
} 

//从DS18B20读取一个位
//返回值：1/0
uint8_t DS18B20_Read_Bit(void) 			 
{
    uint8_t data;
	
	LPC_GPIO2->DIR|=(1<<5);	        //P2.5输出
    DQ_LOW;         //拉低DQ
	delay_ds(2);        //延时
    DQ_HIGH;                    //拉高DQ
	LPC_GPIO2->DIR&=~(1<<5);        //P2.5输入
	delay_ds(12);           //延时
	if(DQ_UP)   data=1;
        else data=0;	 
    delay_ds(50);           //延时
    return data;
}

//从DS18B20读取一个字节
//返回值：读到的数据
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

//从ds18b20得到温度值
//精度：0.1C
//返回值：温度值 （-55~125）
int16_t DS18B20_Get_Temp(void)
{
  uint8_t TL,TH;
	int16_t tem;
	DS18B20_Start();                    // ds1820 start convert
	DS18B20_Rst();          //复位DS18B20
	DS18B20_Check();	    //检测是否存在DS18B20
	DS18B20_Write_Byte(0xcc);   // skip rom
	DS18B20_Write_Byte(0xbe);   // convert	    
	TL=DS18B20_Read_Byte();     // LSB   
	TH=DS18B20_Read_Byte();     // MSB  
				
	if(TH>7)
	{
			TH=~TH;
			TL=~TL; 
			temp_sign=0;        //温度为负
	}else temp_sign=1;	        //温度为正
	tem=TH;             //获得高八位
	tem<<=8;    
	tem+=TL;            //获得底八位
	tem=(float)tem*0.625;           //转换
	if(temp_sign)return tem;        //返回温度值
	else return -tem;    
}






