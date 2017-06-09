#include "oled.h"
#include "ds18b20.h"
#include "key.h"
#include "uart.h"
#include "delay.h"
#include "lpc11xx.h"
#include "Function_Display.h"

uint8_t next = 0;
int16_t temp;   //���ڱ���

short temperature;      //��������
short hua;  //���廪��

void Display_1(void)            //��ʾ���˵�
{
    OLED_Clear();
    OLED_ShowString(0,0,"LPC");    //��ʾ�ַ���"LPC"	
    OLED_ShowCHinese(24,0,0);      //��ʾ����Ρ�
    OLED_ShowCHinese(40,0,1);      //��ʾ���֡��¡�
    OLED_ShowCHinese(56,0,2);      //��ʾ���֡��ȡ�
    OLED_ShowCHinese(72,0,3);      //��ʾ���֡���
    OLED_ShowCHinese(88,0,4);      //��ʾ���֡�ʾ��
    OLED_ShowString(16,2,"Display ");       //��ʾ�ַ���"Display :"
    OLED_ShowCHinese(80,2,7);               //��ʾ����"��"
    OLED_ShowString(16,4,"Display ");       //��ʾ�ַ���"Display :"
    OLED_ShowCHinese(80,4,8);               //��ʾ����"�H"
    OLED_ShowString(16,6,"Voltage ");       //��ʾ�ַ���"Voltage :"
}
void Display_2(void)            //��ʾ����1
{   
    OLED_Clear();
    OLED_ShowString(0,2,"Display: ");       //��ʾ�ַ���"Display :"
    OLED_ShowChar(48,4,'.');       //��ʾ�ַ�
    while(1)
    {
        if(next%10==0)			//ÿ100ms��ȡһ��
        {
        temperature=DS18B20_Get_Temp();
        temp = DS18B20_Get_Temp(); // ���紮�ڵ�����������ʾ��00 C0 ,ת����ʮ����Ϊ��192������19.2���϶�
            if(temperature<0)
            {
                OLED_ShowChar(8,4,'-');        //��ʾ����
                temperature=-temperature;       //תΪ����
            }
            else OLED_ShowChar(8,4,'+');       //������ʾ����

        UART_send_byte(temp>>8);
		UART_send_byte(temp);
		delay_ms(500);

        OLED_ShowNum(24,4,temperature/10,3,16);
        OLED_ShowNum(56,4,temperature%10,1,16);
        OLED_ShowCHinese(80,4,7);               //��ʾ����"��"
                if((LPC_GPIO3->RIS&(1<<3))==(1<<3))
                    break;
        }
        
    }
   
}
//		//�����¶�
//		temp = DS18B20_Get_Temp(); // ���紮�ڵ�����������ʾ��00 C0 ,ת����ʮ����Ϊ��192������19.2���϶�
//		UART_send_byte(temp>>8);
//		UART_send_byte(temp);
//		delay_ms(500);
void Display_3(void)            //��ʾ����2
{
    OLED_Clear();
    OLED_ShowString(0,2,"Display: ");       //��ʾ�ַ���"Display :"
    while(1)
    {
        if(next%10==0)			//ÿ100ms��ȡһ��
        {
        temperature=DS18B20_Get_Temp();
            if(hua < 0)
            {
                OLED_ShowChar(8,4,'-');        //��ʾ����
                hua=-hua;       //תΪ����
            }
            else OLED_ShowChar(8,4,'+');       //������ʾ����
        hua = 32 + (temperature/10)*1.8;
        OLED_ShowNum(48,4,hua,3,16);
        OLED_ShowCHinese(80,4,8);               //��ʾ����"�H"
                if((LPC_GPIO3->RIS&(1<<3))==(1<<3))
                    break;
        }
        
    }
}
void Display_4(void)            //��ʾ����3
{
    OLED_Clear();
    OLED_ShowString(0,2,"Voltage: ");       //��ʾ�ַ���"Voltage :"
    OLED_ShowString(80,4,"V ");            //��ʾ�ַ�"V :"
}




