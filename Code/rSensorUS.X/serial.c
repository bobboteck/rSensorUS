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
    // Seting direction of RC6 and RC7
    TRISCbits.RC6=0;
    TRISCbits.RC7=1;
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
    RCSTA=0b10010000;
    RCSTAbits.SPEN=1;               // Serial Port Enable
    RCSTAbits.RX9=dataBitNumber;    // Number of bit data
    RCSTAbits.CREN=1;               // Receive enabled
    RCSTAbits.ADDEN=0;              //Disables address detection
}
