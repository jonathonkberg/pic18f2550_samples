/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

void uart_init();
void uart_send(uint8_t data);
uint8_t uart_tx_empty();

void uart_init()
{
    BRGH = 1;
    BRG16 = 0;
    SPBRG = 3; //7812.5 baud rate
    SPEN = 1;
    SYNC = 0;
    TRISC6 = 1;
    TRISC7 = 1;
    TX9 = 0;
    TXEN = 1;
}

void uart_send(uint8_t data)
{
    while(!TRMT); //The only line that I do not understand
    TXREG = data;
}

uint8_t uart_tx_empty()
{
    return TRMT;
}

#endif	/* XC_HEADER_TEMPLATE_H */

