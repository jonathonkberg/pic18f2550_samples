/*
 * File:   main.c
 * Author: Jonathon Kreinberg
 *
 * Created on December 26, 2021, 6:55 PM
 */


#include "config.h"


#define _XTAL_FREQ 48000000

void main(void) {
    
    //LATB1 = 0;
    TRISB1 = 0; //0 for out, 1 for in
    
    while(1)
    {
        LATB1 = 1; //or LATC |= (1<<2); or LATCbits.LATC2 = 1
        __delay_ms(500); //function for XC compiler
        LATB1 = 0; //or LATC &= ~(1<<2); or LATCbits.LATC2 = 0
        __delay_ms(500);
    }
    
    return;
}
