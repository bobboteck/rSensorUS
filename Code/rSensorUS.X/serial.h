/* 
 * File:   serial.h
 * Author: roberto
 *
 * Created on 10 settembre 2013, 13.31
 */

#ifndef SERIAL_H
#define	SERIAL_H

#define BAUD_9600       0x0410
#define BIT_NUMBER_8    0
#define BIT_NUMBER_9    1

void SerialSettings(unsigned int baudrate, unsigned char dataBitNumber);

#endif	/* SERIAL_H */

