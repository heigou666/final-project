

#include "lpc11xx.h"



#define KEY1_DOWN (LPC_GPIO3->DATA&(1<<0))!=(1<<0)      //���尴��1����
#define KEY2_DOWN (LPC_GPIO3->DATA&(1<<1))!=(1<<1)      //���尴��2����
#define KEY3_DOWN (LPC_GPIO3->DATA&(1<<2))!=(1<<2)      //���尴��3����
#define KEY4_DOWN (LPC_GPIO3->DATA&(1<<3))!=(1<<3)      //���尴��4����
#define KEY5_DOWN (LPC_GPIO3->DATA&(1<<4))!=(1<<4)      //���尴��5����







