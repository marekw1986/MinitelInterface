/* 
 * File:   uart.h
 * Author: Marek
 *
 * Created on 7 grudnia 2015, 15:43
 */

#ifndef UART_H
#define	UART_H

#include <stdint.h>

#define UART1BAUD (1200)

#ifdef	__cplusplus
extern "C" {
#endif


void uart_init (void);
int uart_getc(void);
char * uart_get_str(char * buf);
void MINITEL_RX_EVENT(void);


#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

