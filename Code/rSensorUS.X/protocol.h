/* 
 * File:   protocol.h
 * Author: roberto
 *
 * Created on 10 settembre 2013, 13.34
 */

#ifndef PROTOCOL_H
#define	PROTOCOL_H

#define BROADCAST   0xFF    // Bus broadcast address

unsigned char BOARD_ADDRESS=0x15; //TODO: This value must be read from the EEPROM
unsigned char packetCommand;
unsigned char packetDataLen;
unsigned char packetDataBufferReceived[20]; //TODO: Definire il corretto dimensionamento del buffer

struct
{
    unsigned PacketIncoming:1;
    unsigned DataForUS:1;
    unsigned BroadCast:1;
    unsigned NoData:1;
    unsigned PacketComplete:1;
    unsigned ErrorEndPacket:1;
    unsigned ErrorCheck:1;
    unsigned ErrorLowLevel:1;
} protocolStatus;

void ProtocolGetData(unsigned char data);

#endif	/* PROTOCOL_H */

