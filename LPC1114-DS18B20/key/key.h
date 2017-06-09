

#include "lpc11xx.h"



#define KEY1_DOWN (LPC_GPIO3->DATA&(1<<0))!=(1<<0)      //定义按键1引脚
#define KEY2_DOWN (LPC_GPIO3->DATA&(1<<1))!=(1<<1)      //定义按键2引脚
#define KEY3_DOWN (LPC_GPIO3->DATA&(1<<2))!=(1<<2)      //定义按键3引脚
#define KEY4_DOWN (LPC_GPIO3->DATA&(1<<3))!=(1<<3)      //定义按键4引脚
#define KEY5_DOWN (LPC_GPIO3->DATA&(1<<4))!=(1<<4)      //定义按键5引脚







