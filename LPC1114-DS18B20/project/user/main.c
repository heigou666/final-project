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
	static int line = 0; //oled��ʾ��
    OLED_Init();    //OLED��ʼ��
	OLED_Clear();   //����
    delay_ms(10);   //�����ȴ�10ms
    UART_init(9600);    //������9600
    Display_1();    //���˵���ʼ��
	while(1)
	{
        if((LPC_GPIO3->RIS&(1<<0))==(1<<0))  // ��ȡRIS�Ĵ���
        {       
                delay_ms(10);       //������������ʱ10ms
                if((LPC_GPIO3->RIS&(1<<0))==(1<<0))
                {   
                    Display_1();        //��ʾ���˵�
                    while(KEY1_DOWN);   //������1���²��ɿ�ʱ
                    line+=2;
                    if(line > 6)   line=2;     
                    OLED_ShowString(0,line,"->");      //ָ�� ->                   
                    LPC_GPIO3->IC = 0XFFF;      //��RIS״̬λ             
                }           
        }
        else if((LPC_GPIO3->RIS&(1<<1))==(1<<1))  //��ȡRIS�Ĵ���
        {       
                delay_ms(10);       //��������   
                if((LPC_GPIO3->RIS&(1<<1))==(1<<1))
                {   
                    Display_1();        //��ʾ���˵�
                    while(KEY2_DOWN);      //������2���²��ɿ�ʱ 
                    line-=2;
                    if(line < 2)   line=6;     
                    OLED_ShowString(0,line,"->");   //ָ��->                     
                    LPC_GPIO3->IC = 0XFFF;  // ��RIS״̬λ                 
                }
        }
        else if((LPC_GPIO3->RIS&(1<<2))==(1<<2))
        {
                delay_ms(10);       //��������
                if((LPC_GPIO3->RIS&(1<<2))==(1<<2))
                {
                    if(line == 2)  Display_2();    //��ʾ����1
                    if(line == 4)  Display_3();    //��ʾ����2
                    if(line == 6)  Display_4();    //��ʾ����3
                }                   
        }            
    }
}






