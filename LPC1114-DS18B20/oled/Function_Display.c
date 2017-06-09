#include "oled.h"
#include "ds18b20.h"
#include "key.h"
#include "uart.h"
#include "delay.h"
#include "lpc11xx.h"
#include "Function_Display.h"

uint8_t next = 0;
int16_t temp;   //串口变量

short temperature;      //定义摄氏
short hua;  //定义华氏

void Display_1(void)            //显示主菜单
{
    OLED_Clear();
    OLED_ShowString(0,0,"LPC");    //显示字符串"LPC"	
    OLED_ShowCHinese(24,0,0);      //显示日语“の”
    OLED_ShowCHinese(40,0,1);      //显示汉字“温”
    OLED_ShowCHinese(56,0,2);      //显示汉字“度”
    OLED_ShowCHinese(72,0,3);      //显示汉字“表”
    OLED_ShowCHinese(88,0,4);      //显示汉字“示”
    OLED_ShowString(16,2,"Display ");       //显示字符串"Display :"
    OLED_ShowCHinese(80,2,7);               //显示符号"℃"
    OLED_ShowString(16,4,"Display ");       //显示字符串"Display :"
    OLED_ShowCHinese(80,4,8);               //显示符号"℉"
    OLED_ShowString(16,6,"Voltage ");       //显示字符串"Voltage :"
}
void Display_2(void)            //显示功能1
{   
    OLED_Clear();
    OLED_ShowString(0,2,"Display: ");       //显示字符串"Display :"
    OLED_ShowChar(48,4,'.');       //显示字符
    while(1)
    {
        if(next%10==0)			//每100ms读取一次
        {
        temperature=DS18B20_Get_Temp();
        temp = DS18B20_Get_Temp(); // 例如串口调试助手上显示：00 C0 ,转换成十进制为：192。代表19.2摄氏度
            if(temperature<0)
            {
                OLED_ShowChar(8,4,'-');        //显示负号
                temperature=-temperature;       //转为正数
            }
            else OLED_ShowChar(8,4,'+');       //否则，显示正数

        UART_send_byte(temp>>8);
		UART_send_byte(temp);
		delay_ms(500);

        OLED_ShowNum(24,4,temperature/10,3,16);
        OLED_ShowNum(56,4,temperature%10,1,16);
        OLED_ShowCHinese(80,4,7);               //显示符号"℃"
                if((LPC_GPIO3->RIS&(1<<3))==(1<<3))
                    break;
        }
        
    }
   
}
//		//测量温度
//		temp = DS18B20_Get_Temp(); // 例如串口调试助手上显示：00 C0 ,转换成十进制为：192。代表19.2摄氏度
//		UART_send_byte(temp>>8);
//		UART_send_byte(temp);
//		delay_ms(500);
void Display_3(void)            //显示功能2
{
    OLED_Clear();
    OLED_ShowString(0,2,"Display: ");       //显示字符串"Display :"
    while(1)
    {
        if(next%10==0)			//每100ms读取一次
        {
        temperature=DS18B20_Get_Temp();
            if(hua < 0)
            {
                OLED_ShowChar(8,4,'-');        //显示负号
                hua=-hua;       //转为正数
            }
            else OLED_ShowChar(8,4,'+');       //否则，显示正数
        hua = 32 + (temperature/10)*1.8;
        OLED_ShowNum(48,4,hua,3,16);
        OLED_ShowCHinese(80,4,8);               //显示符号"℉"
                if((LPC_GPIO3->RIS&(1<<3))==(1<<3))
                    break;
        }
        
    }
}
void Display_4(void)            //显示功能3
{
    OLED_Clear();
    OLED_ShowString(0,2,"Voltage: ");       //显示字符串"Voltage :"
    OLED_ShowString(80,4,"V ");            //显示字符"V :"
}




