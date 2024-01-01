/* 
 * File:   uart.h
 * Author: Marek
 *
 * Created on 7 grudnia 2015, 15:43
 */

#ifndef DEBUG_UART_H
#define	DEBUG_UART_H

#include <stdint.h>

#define DEBUG_UART1BAUD (115200)

#ifdef	__cplusplus
extern "C" {
#endif

extern volatile uint8_t ascii_line;


void debug_uart_init (void);
int debug_uart_getc(void);
char * debug_uart_get_str(char * buf);
//void DEBUG_UART_RX_STR_EVENT(char * rbuf);
//void register_uart_str_rx_event_callback(void (*callback)(char * pBuf));


#ifdef	__cplusplus
}
#endif

#endif	/* DEBUG_UART_H */

