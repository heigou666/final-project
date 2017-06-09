#ifndef __DS18B20_H__
#define __DS18B20_H__

#include "lpc11xx.h"
//IO方向设置，操作函数

#define DQ_LOW  LPC_GPIO2->DATA&=~(1<<5)        //DQ拉低  P2.5
#define DQ_HIGH  LPC_GPIO2->DATA|=(1<<5)        //DQ拉高  P2.5
#define DQ_DOWN ((LPC_GPIO2->DATA&(1<<5))!=(1<<5))
#define DQ_UP ((LPC_GPIO2->DATA&(1<<5))==(1<<5))

extern uint8_t temp1;
extern uint8_t temp2;

extern void delay_ds(uint16_t us);
extern void init_ds18b20(void);
extern uint8_t ds18b20_reset(void);
extern void convert_T(void);
extern short read_T(void); 

extern void DS18B20_Rst(void);	        //复位DS18B20
extern uint8_t DS18B20_Check(void);     //检测是否存在DS18B20
extern uint8_t DS18B20_Init(void);      //初始化DS18B20
extern short DS18B20_Get_Temp(void);      //获取温度  





#endif








