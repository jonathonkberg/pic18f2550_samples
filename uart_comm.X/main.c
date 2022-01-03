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

void blink();

void main(void) {

    uint8_t send_message = 0;
    TRISB4 = 0; //LED is output
    uart_init();
    
    
    while(1)
    {
        blink();
        __delay_ms(3000);
        uart_send(send_message);
        send_message++;
        
        
    }
    
    return;
}

void blink()
{
        //Make sure TRISB4 is set to 0
        LATB4 = 1; //or LATC |= (1<<2); or LATCbits.LATC2 = 1
        __delay_ms(500); //function for XC compiler
        LATB4 = 0; //or LATC &= ~(1<<2); or LATCbits.LATC2 = 0
        __delay_ms(500);
}
