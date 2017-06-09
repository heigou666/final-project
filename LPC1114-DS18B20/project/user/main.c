#include "lpc11xx.h"
#include "delay.h"
#include "oled.h"
#include "Function_Display.h"
#include "key.h"
#include "ds18b20.h"
#include "uart.h"

unsigned char tx_buf[]={"0123456789"};
unsigned char rx_buf[32];

int main(void)
{	
	static int line = 0; //oled显示行
    OLED_Init();    //OLED初始化
	OLED_Clear();   //清屏
    delay_ms(10);   //清屏等待10ms
    UART_init(9600);    //波特率9600
    Display_1();    //主菜单初始化
	while(1)
	{
        if((LPC_GPIO3->RIS&(1<<0))==(1<<0))  // 读取RIS寄存器
        {       
                delay_ms(10);       //按键消抖，延时10ms
                if((LPC_GPIO3->RIS&(1<<0))==(1<<0))
                {   
                    Display_1();        //显示主菜单
                    while(KEY1_DOWN);   //当按键1按下不松开时
                    line+=2;
                    if(line > 6)   line=2;     
                    OLED_ShowString(0,line,"->");      //指针 ->                   
                    LPC_GPIO3->IC = 0XFFF;      //清RIS状态位             
                }           
        }
        else if((LPC_GPIO3->RIS&(1<<1))==(1<<1))  //读取RIS寄存器
        {       
                delay_ms(10);       //按键消抖   
                if((LPC_GPIO3->RIS&(1<<1))==(1<<1))
                {   
                    Display_1();        //显示主菜单
                    while(KEY2_DOWN);      //当按键2按下不松开时 
                    line-=2;
                    if(line < 2)   line=6;     
                    OLED_ShowString(0,line,"->");   //指针->                     
                    LPC_GPIO3->IC = 0XFFF;  // 清RIS状态位                 
                }
        }
        else if((LPC_GPIO3->RIS&(1<<2))==(1<<2))
        {
                delay_ms(10);       //按键消抖
                if((LPC_GPIO3->RIS&(1<<2))==(1<<2))
                {
                    if(line == 2)  Display_2();    //显示功能1
                    if(line == 4)  Display_3();    //显示功能2
                    if(line == 6)  Display_4();    //显示功能3
                }                   
        }            
    }
}






