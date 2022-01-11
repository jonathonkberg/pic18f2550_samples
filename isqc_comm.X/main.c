/*
 * File:   main.c
 * Author: Jonathon Kreinberg
 *
 * Created on January 9, 2021, 6:55 PM
 */

#include <stdint.h>
#include "config.h"
#include "isqc_tools.h"

#define _XTAL_FREQ 48000000
#define led RB4
#define slave_addr 0x00

unsigned char RX_Data = 0x00;

void blink();
//isqc_slave_init(unsigned char);

void main(void) {

    TRISB4 = 0; //OUTPUT for LED
    isqc_slave_init(slave_addr);
    
    while(1)
    {
        //Write I2C code here
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

/*
void __interrupt() ISR(void)
{
    if(SSPIF)
    {
        CKP = 0;
        if(SSPOV || WCOL) //check for overflow or collision
        {
            char msg = SSPBUF; //clear BF
            SSPOV = 0; //clear overflow bit
            WCOL = 0; //clear collision bit
            CKP = 1;
        }
        if(!R_nW)
        {
            char msg = SSPBUF; //clear BF
            while(!BF); //wait for buffer to clear
            RX_Data = SSPBUF; //set data to global variable (declare RX_Data as unsigned char)
            //CKP = 1;
        }
        CKP = 1;
        SSPIF = 0;
    }
}
 */