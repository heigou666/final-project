#ifndef __DS18B20_H__
#define __DS18B20_H__

#include "lpc11xx.h"
//IO�������ã���������

#define DQ_LOW  LPC_GPIO2->DATA&=~(1<<5)        //DQ����  P2.5
#define DQ_HIGH  LPC_GPIO2->DATA|=(1<<5)        //DQ����  P2.5
#define DQ_DOWN ((LPC_GPIO2->DATA&(1<<5))!=(1<<5))
#define DQ_UP ((LPC_GPIO2->DATA&(1<<5))==(1<<5))

extern uint8_t temp1;
extern uint8_t temp2;

extern void delay_ds(uint16_t us);
extern void init_ds18b20(void);
extern uint8_t ds18b20_reset(void);
extern void convert_T(void);
extern short read_T(void); 

extern void DS18B20_Rst(void);	        //��λDS18B20
extern uint8_t DS18B20_Check(void);     //����Ƿ����DS18B20
extern uint8_t DS18B20_Init(void);      //��ʼ��DS18B20
extern short DS18B20_Get_Temp(void);      //��ȡ�¶�  





#endif








