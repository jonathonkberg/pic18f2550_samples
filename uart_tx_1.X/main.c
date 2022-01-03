/*
 * File:   main.c
 * Author: Jonathon Kreinberg
 *
 * Created on December 26, 2021, 6:55 PM
 */

#include <stdint.h>
#include "config.h"
#include "uart_tools.h"

#define _XTAL_FREQ 48000000
#define sender RB3
#define changer RB2
#define led RB4

void blink();
void tx_blink();

void main(void) {

    uint8_t send_message = 0;
    TRISB = 0x0C; //4 out, 3 and 2 in
    uart_init();
    
    
    while(1)
    {
        __delay_ms(100);
        
        if(!changer)
        {
            LATB4 = 1;
            if(send_message == 0x00)
                send_message = 0x01;
            else
                send_message = 0x00;
            __delay_ms(1000);
            LATB4 = 0;
        }
        if(!sender)
        {
            tx_blink();
            uart_send(send_message);
        }
        
        
        /* //For testing I/O
        if(sender && changer)
            LATB4 = 0;
        else
            LATB4 = 1;
         */
        
    }
    
    return;
}

void blink()
{
        //Make sure TRISB4 is set to 0
        LATB4 = 1; //or LATC |= (1<<2); or LATCbits.LATC2 = 1
        __delay_ms(100); //function for XC compiler
        LATB4 = 0; //or LATC &= ~(1<<2); or LATCbits.LATC2 = 0
        __delay_ms(100);
}

void tx_blink()
{
    for(int i = 0; i < 5; i++)
    {
        blink();
    }
}