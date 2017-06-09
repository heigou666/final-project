#include "lpc11xx.h"
#ifndef   __NXPLPC11XX_UART_H__
#define   __NXPLPC11XX_UART_H__

extern uint8_t Recived_data; // �����ֽ�

extern void UART_init(uint32_t baudrate);  // ��ʼ������
extern uint8_t UART_recive(void);   // ���ڽ����ֽ�����
extern void UART_send_byte(uint8_t byte); // ���ڷ����ֽ�����
extern void UART_send(uint8_t *Buffer, uint32_t Length); // ���ڷ�����������

extern void RS485_init(uint32_t baudrate);
extern uint16_t CalcChkSum(uint8_t *lpPack, uint8_t DataLen); // ����16λCRCУ��ֵ

#endif





