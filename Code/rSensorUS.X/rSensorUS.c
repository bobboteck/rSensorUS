/* 
 * File  : rSensorUS.c
 * Author: bobboteck
 *
 * Created on 4 settembre 2013, 12.58
 */
#include <pic18f2620.h>
#include "settings.h"
#include "interrupts.h"
#include "serial.h"
#include "protocol.h"

/*
 * 
 */
int main(void)
{
    BoardSettings();

    while(1)
    {
        if(protocolStatus.PacketComplete)
        {
            //TODO: Call command parser
        }
        if(serialStatus.DataReceived && !protocolStatus.PacketComplete)
        {
            // Call method of protocol class to analize packet
            ProtocolGetData(serialBuffer);
            serialStatus.DataReceived=0;
        }
    }
}
