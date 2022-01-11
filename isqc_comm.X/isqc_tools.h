/* 
 * File:   isqc_tools.h
 * Author: jpk12
 *
 * Created on January 9, 2022, 12:42 AM
 */

#ifndef ISQC_TOOLS_H
#define	ISQC_TOOLS_H

#define _XTAL_FREQ 48000000
#define BAUD_RATE 9600

//* MASTER MODE ONLY *//

/* 1. WAIT 
 * Makes sure ACKEN, RCEN, PEN, RSEN, SEN off 
 * Makes sure transmit not in progress
 * If all conditions are proper the program continues */
void isqc_wait()
{
    while((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

/* 2. MASTER INIT
 * Set SCL and SDA instead of IO with SSPCON1
 * Choose Master mode with SSPCON1
 * Set SCL and SDA as INPUTS with TRIS
 * Set baud rate to SSPSTAT
 * SSPSTAT and SSPCON2 cleared and used later in wait function
 * SSPCON1 */
void isqc_master_init()
{
    TRISB0 = 1;
    TRISB1 = 1;
    SSPADD = ((_XTAL_FREQ*4)/BAUD_RATE)-1;
    SSPSTAT = 0x00;
    SSPCON1 = 0x28;
    SSPCON2 = 0x00;
}

/* 3. START TRANSMISSION SUBSYSTEM
 * Wait for proper state
 * Set start bit SEN
 * To transmit load message to buffer after start */
void isqc_start()
{
    isqc_wait();
    SEN = 1;
}

/* 4. STOP
 * Wait for proper state
 * Set stop bit PEN */
void isqc_stop()
{
    isqc_wait();
    PEN = 1;
}

/* 5. RESTART
 * Wait for proper state
 * Set restart bit RSEN */
void isqc_RSEN()
{
    isqc_wait();
    RSEN = 1;
}

/* 6. ACK
 * Master receive mode only */
void isqc_ack()
{
    isqc_wait();
    ACKDT = 0; // (0,1) = ('ack', 'nack')
    ACKEN = 1; //send 'ack'
}

/* 7. NACK
 * Master receive mode only */
void isqc_nack()
{
    isqc_wait();
    ACKDT = 1; // (1,0) = ('nack', 'ack')
    ACKEN = 1; //send 'nack'
}

/* 8. SEND BYTE AND CHECK FOR ACK
 * Wait for proper state
 * Place message in buffer to send
 * Will only send if start bit SEN was previously set
 * Wait for proper state after slave responds
 * Return ACK status */
unsigned char isqc_sendByte(unsigned char msg)
{
    isqc_wait();
    SSPBUF = msg;
    isqc_wait();
    return ACKSTAT;
}

/* 9. REQUEST AND RECIEVE BYTE
 * Request for byte
 * Wait for a response from slave by checking interrupt
 * Clear interrupt
 * Return the message */
unsigned char isqc_recieveByte()
{
    RCEN = 1;
    while(!SSPIF);
    SSPIF = 0;
    return SSPBUF;
}

//* SLAVE MODE ONLY *//

/* 1. SLAVE INIT */
void isqc_slave_init(unsigned char slave_address)
{
    TRISB0 = 1;
    TRISB1 = 1;
    SSPADD = slave_address; //set address
    SSPSTAT = 0x80; //slew rate control disabled
    SSPCON1 = 0x36; //Seven bit mode
    SSPCON2 = 0x01; //enable clock stretching
    SSPIF = 0; //message interrupt; set to wait state (see p. 106)
    SSPIE = 1; //enables MSSP interrupt (p.108))
    PEIE = 1; //enables interrupt set (p.102-103)
    GIE = 1; //enables interrupt set (p.102-103)    
}


/* 2. INTERRUPT VERSION A
 * Use this interrupt slave reading only */
/*
void __interrupt() ISR(void)
{
    if(SSPIF)
    {
        CKP = 0;
        if(SSPOV || WCOL) //check for overflow or collision
        {
            char msg = SSPBUF; //to clear BF
            SSPOV = 0; //clear overflow bit
            WCOL = 0; //clear collision bit
            CKP = 1;
        }
        if(!R_nW)
        {
            char msg = SSPBUF; //to clear BF
            while(!BF); //wait for buffer to clear
            RX_Data = SSPBUF; //set data to global variable (declare RX_Data as unsigned char)
            //CKP = 1;
        }
        CKP = 1;
        SSPIF = 0;
    }
} */

 /* 3. INTERRUPT VERSION B
 * Use this interrupt for slave writing only
 * 
 * //Have not written this code yet
 * 
*/

#endif	/* ISQC_TOOLS_H */

