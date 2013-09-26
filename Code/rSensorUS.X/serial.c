#include <pic18f2620.h>
#include "serial.h"

/**
 * Setup the EUSART configuration register
 *
 * @param baudrate      The value for the SPBRG register to generate desired baudrate. Use the predefined value.
 * @param dataBitNumber The number of bit of len data
 */
void SerialSettings(unsigned int baudrate, unsigned char dataBitNumber)
{
    // Seting direction of used pin
    TRISCbits.RC5=0;                // TX/RX controller
    TRISCbits.RC6=0;                // TX
    TRISCbits.RC7=1;                // RX
    // Setting baud rate of ESART module
    SPBRG=(unsigned char)(baudrate && 0x00FF);
    SPBRGH=(unsigned char)(baudrate>>8);
    // 16-Bit Baud Rate Register Enabled
    BAUDCON=0b00001000;
    // Configuration of TX register
    //TXSTA=0b00100100;
    TXSTAbits.TX9=dataBitNumber;    // Number of bit data
    TXSTAbits.TXEN=0;               // Transmit disabled
    TXSTAbits.SYNC=0;               // Asynchronous mode
    TXSTAbits.BRGH=1;               // High Baud Rate Select bit
    // Configuration of RX register
    //RCSTA=0b10010000;
    RCSTAbits.SPEN=1;               // Serial Port Enable
    RCSTAbits.RX9=dataBitNumber;    // Number of bit data
    RCSTAbits.CREN=1;               // Receive enabled
    RCSTAbits.ADDEN=0;              //Disables address detection
    // Interrupt conffiguration
    PIR1bits.RCIF=0;                // Reset interrupt flag
    IPR1bits.RCIP=0;                // Low priority
    PIE1bits.RCIE=1;                // Enable interrupt on receive data
    
    //TODO: Check if need a interrupt for the trasmission data
}

/**
 * Set the new data in the Serial buffer
 *
 * @param data  Data to store in the Serial buffer
 */
void SerialSetBuffer(unsigned int data)
{
    serialBuffer=data;
    serialStatus.DataReceived=1;
    serialStatus.FramingError=0;
    serialStatus.OverrunError=0;
}

/**
 * Set error information of byte received
 *
 * @param framingError  Set it to 1 if error type is Framing, otherwise 0
 * @param overrunError  Set it to 1 if error type is Overrun, otherwise 0
 */
void SerialSetError(unsigned char framingError, unsigned char overrunError)
{
    serialBuffer=0;
    serialStatus.DataReceived=1;
    serialStatus.FramingError=framingError;
    serialStatus.OverrunError=overrunError;
}

/**
 * Return, if is an exception, a code of error catched:
 * 1- FramingError
 * 2- OverrunError
 *
 * @return 0 if no low level error detected, else a error code
 */
unsigned char SerialCheckError(void)
{
    if(serialStatus.FramingError)
    {
        return 1;
    }
    else if(serialStatus.OverrunError)
    {
        return 2;
    }
    else
    {
        return 0;
    }
}