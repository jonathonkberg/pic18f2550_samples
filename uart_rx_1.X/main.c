/*
* LAB Number: 15
* LAB Name: UART_Basic_Communication (Slave Code)
* Author: Khaled Magdy
* For More Information Visit My Website @ DeepBlueMbedded.com
*

 
//#include <xc.h>
#include <stdint.h>
#include "config.h"
#define _XTAL_FREQ 48000000
//--------------------------------
// Functions Declarations
void UART_RX_Init(void);
uint8_t UART_Read(void);
// Globals
uint8_t UART_Buffer = 0;
//--------------------------------
// Main Routine
void main(void)
{
  //--[ Peripherals & IO Configurations ]--
  UART_RX_Init(); // Initialize The UART in Master Mode @ 9600bps
  TRISB4 = 0; // Output Port (4-Pins)
  LATB4 = 0; // Initially OFF
  //---------------------------
  while(1)
  {
    // Stay Idle, Everything is handled in the ISR !
  }
  return;
}
//--------------------------------
// Functions Definitions
 
void UART_RX_Init()
{
  BRGH = 1; // Set For High-Speed Baud Rate
  BRG16 = 0;
  RX9 = 0;
  SPBRGH = 0x01;
  SPBRG = 0x38; // Set The Baud Rate To Be 9600 bps
  // Enable The Ascynchronous Serial Port
  SYNC = 0;
  SPEN = 1;
  // Set The RX-TX Pins to be in UART mode (not io)
  TRISC6 = 1; // As stated in the datasheet
  TRISC7 = 1; // As stated in the datasheet
  //--[ Enable UART Receiving Interrupts ]--
  RCIE = 1; // UART Receving Interrupt Enable Bit
  PEIE = 1; // Peripherals Interrupt Enable Bit
  GIE = 1; // Global Interrupt Enable Bit
  //------------------
  CREN = 1; // Enable Data Continous Reception
}
 
void __interrupt() ISR(void)
{
  if (RCIF == 1)
  {
    UART_Buffer = RCREG; // Read The Received Data Buffer
    PORTB = UART_Buffer; // Display The Received Data On LEDs
    RCIF = 0; // Clear The Flag
  }
}
*/


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