 /* File:   main.c
 * Author: Jonathon Kreinberg
 *
 * Created on December 26, 2021, 6:55 PM
 */

#include <stdint.h>
#include "config.h"
#include "uart_tools.h"

#define _XTAL_FREQ 48000000

void blink();

uint8_t rec_message = 0x00;

void main(void) {

    blink(); //show reset
    TRISB4 = 0; //LED is output
    LATB4 = 0;
    uart_rx_init();
    
    
    while(1)
    {
        __delay_ms(100);
    }
    
    return;
}

void blink()
{
        //Make sure TRISB4 is set to 0
        LATB4 = 1; //or LATC |= (1<<2); or LATCbits.LATC2 = 1
        __delay_ms(1000); //function for XC compiler
        LATB4 = 0; //or LATC &= ~(1<<2); or LATCbits.LATC2 = 0
        __delay_ms(1000);
}

void __interrupt() ISR(void)
{
    if(RCIF == 1)
    {
        rec_message = RCREG;
        if(rec_message == 0x00)
            LATB4 = 0;
        else if(rec_message == 0x01)
            LATB4 = 1;
        else
            LATB4 = 0;
        RCIF = 0;
    }
}