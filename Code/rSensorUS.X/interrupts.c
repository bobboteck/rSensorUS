#include "interrupts.h"
#include "serial.h"
#include <pic18f2620.h>

/************************
 * Low Interrupt Vector *
 ************************/
/*
#pragma code InterruptVectorLow = 0x18
void InterruptVectorLow(void)
{
    _asm
            goto InterruptHandlerLow
    _endasm
}
#pragma code
#pragma interruptlow InterruptHandlerLow
 */
//void InterruptHandlerLow(void)
void interrupt low_priority InterruptHandlerLow(void)
{
    if(PIR1bits.RCIF==1)
    {
        if(RCSTAbits.FERR==0 && RCSTAbits.OERR==0)
        {
            SerialSetBuffer(RCREG);
        }
        else
        {
            SerialSetError(RCSTAbits.FERR, RCSTAbits.OERR);
        }

        PIR1bits.RCIF=0;
    }
}
/*************************
 * High Interrupt Vector *
 *************************/
/*#pragma code InterruptVectorHigh = 0x08
void InterruptVectorHigh(void)
{
    _asm
            goto InterruptHandlerHigh
    _endasm
}
#pragma code
#pragma interrupt InterruptHandlerHigh
void InterruptHandlerHigh(void)*/
void interrupt InterruptHandlerHigh(void)
{
    
}