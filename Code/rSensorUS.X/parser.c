#include "protocol.h"
#include "parser.h"
#include <pic18f2620.h>

void parserMessage(void)
{
    switch (packetCommand)
    {
        case 0x01:
            PORTAbits.RA2=0;
            break;
        case 0x02:
            PORTAbits.RA3=0;
            break;
        case 0x03:
            PORTAbits.RA2=1;
            break;
        case 0x04:
            PORTAbits.RA3=1;
            break;

    }
}