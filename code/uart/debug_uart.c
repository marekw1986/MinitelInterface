#include <xc.h>
#include <stdlib.h>
#include <p32xxxx.h>
#include <plib.h>

#include "debug_uart.h"


#define DEBUG_UART_RX_BUF_SIZE 64 // definiujemy bufor o rozmiarze 32 bajtów
// definiujemy mask? dla naszego bufora
#define DEBUG_UART_RX_BUF_MASK ( DEBUG_UART_RX_BUF_SIZE - 1)


volatile uint8_t debug_ascii_line;

volatile char debug_UART_RxBuf[DEBUG_UART_RX_BUF_SIZE];
volatile uint16_t debug_UART_RxHead; // indeks oznaczaj?cy ?g?ow? w??a?
volatile uint16_t debug_UART_RxTail; // indeks oznaczaj?cy ?ogon w??a?


void debug_uart_init (void) {
    TRISBbits.TRISB8 = 1; //RPB8 input
    TRISBbits.TRISB9 = 0; //RPB9 output  
    U2RXRbits.U2RXR = 0b0100;   //RPB8 is U2 RX
    RPB9Rbits.RPB9R = 0b0010;   //RPB9 is U2 TX  
    
    INTSetVectorPriority(INT_VECTOR_UART(UART2), INT_PRIORITY_LEVEL_1);
    INTSetVectorSubPriority(INT_VECTOR_UART(UART2), INT_SUB_PRIORITY_LEVEL_1);

    INTClearFlag(INT_SOURCE_UART_RX(UART2));
    INTClearFlag(INT_SOURCE_UART_TX(UART2));

    INTEnable(INT_SOURCE_UART_RX(UART2), INT_ENABLED);

    OpenUART2(UART_EN | UART_NO_PAR_8BIT | UART_1STOPBIT | UART_DIS_BCLK_CTS_RTS, UART_RX_ENABLE | UART_TX_ENABLE, SYSCLK/16/DEBUG_UART1BAUD-1);
}


// definiujemy funkcj? pobieraj?c? jeden bajt z bufora cyklicznego
int debug_uart_getc(void) {
	int data = -1;
    // sprawdzamy czy indeksy s? równe
    if ( debug_UART_RxHead == debug_UART_RxTail ) return data;
    // obliczamy i zapami?tujemy nowy indeks ?ogona w??a? (mo?e si? zrówna? z g?ow?)
    debug_UART_RxTail = (debug_UART_RxTail + 1) & DEBUG_UART_RX_BUF_MASK;
    // zwracamy bajt pobrany z bufora  jako rezultat funkcji
    data = debug_UART_RxBuf[debug_UART_RxTail];
    return data;
}


char * debug_uart_get_str(char * buf) {
	char c;
	char * wsk = buf;
	if( debug_ascii_line ) {
		while( (c = debug_uart_getc()) ) {
			if( 13 == c || c < 0) break;
			*buf++ = c;
		}
		*buf=0;
		debug_ascii_line--;
	}
	return wsk;
}


void __ISR(_UART2_VECTOR, IPL1AUTO) IntUart2Handler (void) {
    
    uint16_t tmp_head;
    char data;
    
    if (INTGetFlag(INT_SOURCE_UART_RX(UART2))) {
        while(U2STAbits.URXDA) {
            data = U2RXREG;
            tmp_head = ( debug_UART_RxHead + 1) & DEBUG_UART_RX_BUF_MASK;
            if ( tmp_head == debug_UART_RxTail ) {
                debug_UART_RxHead = debug_UART_RxTail;
            } else {
                switch( data ) {
                    case 0:					// ignorujemy bajt = 0
                    case 10: break;			// ignorujemy znak LF
                    case 13: debug_ascii_line++;	// sygnalizujemy obecno?? kolejnej linii w buforze
                    default : debug_UART_RxHead = tmp_head; debug_UART_RxBuf[tmp_head] = data;
                }

            }
        }
 //       IFS1CLR = _IFS1_U1RXIF_MASK;
          INTClearFlag(INT_SOURCE_UART_RX(UART2));
    }
    
    if (INTGetFlag(INT_SOURCE_UART_TX(UART2))) {
        INTClearFlag(INT_SOURCE_UART_TX(UART2));
    }
}