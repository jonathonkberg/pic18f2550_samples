/* 
 * File:   uart_tools.h
 * Author: jpk12
 *
 * Created on December 30, 2021, 7:40 PM
 */

#ifndef UART_TOOLS_H
#define	UART_TOOLS_H


void uart_init()
{
    BRGH = 1; //high speed baud
    BRG16 = 0; //8 bit
    SPBRGH = 0X01; //9615 baud rate
    SPBRG = 0X38;
    SYNC = 0; //set asynchronous
    SPEN = 1; //select TX and RX functionality
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

/*
void uart_send_string(char *text)
{
    uint16_t i;
    for(i=0; text[i]!='\0'; i++)
        uart_send(text[i]);
}
*/

uint8_t uart_tx_empty()
{
    return TRMT;
}

void uart_rx_init()
{
    BRGH = 1; //high speed baud
    BRG16 = 0; //8 bit
    RX9 = 0;
    SPBRG = 3;//sets baud rate to 7812.5
    SYNC = 0; //asynchronous mode
    SPEN = 1; //select TX and RX pin functionality
    TRISC6 = 1;
    TRISC7 = 1;
    RCIE = 1; //enable interrupts
    PEIE = 1;
    GIE = 1;
    CREN = 1; //enable reception
}

uint8_t uart_read()
{
    while(!RCIF);
    return RCREG;
}

void uart_read_string(uint8_t *Output, uint16_t length)
{
  uint16_t i;
  for(int i=0;i<length;i++)
    Output[i] = uart_read();
}

/*
//Can be included in ISR routine
//Can also be subbed for a read function
void interrupt ISR (void)
{
    if(RCIF == 1)
    {
        //Destination = RCREG;
        RCIF = 0;
    }
}
*/

#endif	/* UART_TOOLS_H */

