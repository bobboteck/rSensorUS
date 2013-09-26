/* 
 * File:   serial.h
 * Author: roberto
 *
 * Created on 10 settembre 2013, 13.31
 */

#ifndef SERIAL_H
#define	SERIAL_H

#define BAUD_9600       0x0410
#define BAUD_14400      0x0000 //TODO: To define this and more
#define BIT_NUMBER_8    0
#define BIT_NUMBER_9    1

unsigned char serialBuffer; //TODO: This was used in interrupt function, in possible to change whit array
struct
{
    unsigned FramingError:1;
    unsigned OverrunError:1;
    unsigned NotUsed:5;
    unsigned DataReceived:1;
    //unsigned BufferOverrun:1;
    //unsigned BufferLevel:5;
    //TODO: Si potrebbero usare questi due per gestire un buffer con uno spazio di 32 byte
} serialStatus;


/**
 * Setup the EUSART configuration register
 *
 * @param baudrate      The value for the SPBRG register to generate desired baudrate. Use the predefined value.
 * @param dataBitNumber The number of bit of len data
 */
void SerialSettings(unsigned int baudrate, unsigned char dataBitNumber);

/**
 * Set the new data in the Serial buffer
 *
 * @param data  Data to store in the Serial buffer
 */
void SerialSetBuffer(unsigned int data);

/**
 * Set error information of byte received
 *
 * @param framingError  Set it to 1 if error type is Framing, otherwise 0
 * @param overrunError  Set it to 1 if error type is Overrun, otherwise 0
 */
void SerialSetError(unsigned char framingError, unsigned char overrunError);

/**
 * Return, if is an exception, a code of error catched:
 * 1- FramingError
 * 2- OverrunError
 *
 * @return 0 if no low level error detected, else a error code
 */
unsigned char SerialCheckError(void);

#endif	/* SERIAL_H */

