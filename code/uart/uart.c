#include <xc.h>
#include <stdlib.h>
#include <p32xxxx.h>
#include <plib.h>

#include "uart.h"


#define UART_RX_BUF_SIZE 256 // definiujemy bufor o rozmiarze 32 bajt�w
// definiujemy mask? dla naszego bufora
#define UART_RX_BUF_MASK ( UART_RX_BUF_SIZE - 1)

volatile char UART_RxBuf[UART_RX_BUF_SIZE];
volatile uint16_t UART_RxHead; // indeks oznaczaj?cy ?g?ow? w??a?
volatile uint16_t UART_RxTail; // indeks oznaczaj?cy ?ogon w??a?


// Zdarzenie do odbioru danych ?a?cucha tekstowego z bufora cyklicznego
void MINITEL_RX_EVENT(void) {
    char data;
	if( data = uart_getc()) {
        putcUART2(data);
	}
}


void uart_init (void) {
    TRISBSET = _TRISB_TRISB2_MASK;
    TRISBCLR = _TRISB_TRISB3_MASK;
    U1RXRbits.U1RXR = 0b0100;   //RPB2 RX
    RPB3Rbits.RPB3R = 0b0001;   //RPA0 TX
    
//    U1BRG = (SYSCLK/16/UART1BAUD-1);
    
//    IPC8bits.U1IP = 1;
    INTSetVectorPriority(INT_VECTOR_UART(UART1), INT_PRIORITY_LEVEL_1);
    INTSetVectorSubPriority(INT_VECTOR_UART(UART1), INT_SUB_PRIORITY_LEVEL_1);
//    IPC8bits.U1IS = 1;    
//    IFS1CLR = (_IFS1_U1RXIF_MASK | _IFS1_U1TXIF_MASK);
    INTClearFlag(INT_SOURCE_UART_RX(UART1));
    INTClearFlag(INT_SOURCE_UART_TX(UART1));
//    IEC1SET = _IEC1_U1RXIE_MASK;
    INTEnable(INT_SOURCE_UART_RX(UART1), INT_ENABLED);
 //   U1MODE = (UART_EN | UART_NO_PAR_8BIT | UART_1STOPBIT | UART_DIS_BCLK_CTS_RTS);
 //   U1STA = (UART_RX_ENABLE | UART_TX_ENABLE);
    OpenUART1(UART_EN | UART_EVEN_PAR_8BIT | UART_1STOPBIT | UART_DIS_BCLK_CTS_RTS, UART_RX_ENABLE | UART_TX_ENABLE, SYSCLK/16/UART1BAUD-1);
}


// definiujemy funkcj? pobieraj?c? jeden bajt z bufora cyklicznego
int uart_getc(void) {
	int data = -1;
    // sprawdzamy czy indeksy s? r�wne
    if ( UART_RxHead == UART_RxTail ) return data;
    // obliczamy i zapami?tujemy nowy indeks ?ogona w??a? (mo?e si? zr�wna? z g?ow?)
    UART_RxTail = (UART_RxTail + 1) & UART_RX_BUF_MASK;
    // zwracamy bajt pobrany z bufora  jako rezultat funkcji
    data = UART_RxBuf[UART_RxTail];
    return data;
}


void __ISR(_UART1_VECTOR, IPL1AUTO) IntUart1Handler (void) {
    
    uint16_t tmp_head;
    char data;
    
    if (INTGetFlag(INT_SOURCE_UART_RX(UART1))) {
        while(U1STAbits.URXDA) {
            data = U1RXREG;
            tmp_head = ( UART_RxHead + 1) & UART_RX_BUF_MASK;
            if ( tmp_head == UART_RxTail ) {
                UART_RxHead = UART_RxTail;
            } else {
                switch( data ) {
                    case 0:					// ignorujemy bajt = 0
                    default : UART_RxHead = tmp_head; UART_RxBuf[tmp_head] = data;
                }

            }
        }
 //       IFS1CLR = _IFS1_U1RXIF_MASK;
          INTClearFlag(INT_SOURCE_UART_RX(UART1));
    }
    
    if (INTGetFlag(INT_SOURCE_UART_TX(UART1))) {

 //       IFS1CLR = _IFS1_U1TXIF_MASK;
        INTClearFlag(INT_SOURCE_UART_TX(UART1));
    }
}