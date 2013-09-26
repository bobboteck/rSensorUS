#include "serial.h"
#include "protocol.h"

#define PACKET_START    0
#define PACKET_ADDRESS  1
#define PACKET_COMMAND  2
#define PACKET_DATALEN  3
#define PACKET_DATA     4
#define PACKET_CHECK    5
#define PACKET_END      6

static unsigned char packetElementCursor=PACKET_START;
static unsigned char packetNextElement=PACKET_START;
static unsigned char packetDataCounter=0;
static unsigned char packetDataCheck=0;
static unsigned char ProtocolLowLevelError=0;

unsigned char ProtocolCheckData(unsigned char checkData, unsigned char data)
{
    return checkData ^= data;
}

void ProtocolGetData(unsigned char data)
{
    ProtocolLowLevelError=SerialCheckError();
    if(ProtocolLowLevelError>0)
    {
        // Si è verificato un errore
        protocolStatus.ErrorLowLevel=1;
        //TODO: Qui va tutta una gestione dell'errore in funzione del byte che si sta analizzando in questo momento
        //....
    }
    else
    {
        // Non ci sono stati errori sul livello fisico il byte ricevuto è buono
        switch (packetElementCursor)
        {
            case PACKET_START:
                // Check if data received is a Start Byte
                if(data==0x40)
                {
                    // Sta arrivando un pacchetto
                    protocolStatus.PacketIncoming=1;
                    // Imposta il prossimo elemento del pacchetto da verificare
                    packetNextElement=PACKET_ADDRESS;
                }
                else
                {
                    protocolStatus.PacketIncoming=0;    //TODO: Azzerare solo alla fine o in caso di errore?
                }
                break;
            case PACKET_ADDRESS:
                // Check the address data
                if(data==BOARD_ADDRESS)
                {
                    // Si tratta di un pacchetto destinato a questo Slave
                    protocolStatus.DataForUS=1;
                    // Imposta il prossimo elemento del pacchetto da verificare
                    packetNextElement=PACKET_COMMAND;
                }
                else if(data==BROADCAST)
                {
                    // Si tratta di un pacchetto broadcast
                    protocolStatus.BroadCast=1;
                    // Imposta il prossimo elemento del pacchetto da verificare
                    packetNextElement=PACKET_COMMAND;
                }
                else
                {
                    // Si tratta di un pacchetto destinato ad altri
                    protocolStatus.DataForUS=0;
                    protocolStatus.BroadCast=0;
                    // Imposta il prossimo elemento del pacchetto da verificare
                    packetNextElement=PACKET_COMMAND;
                }
                break;
            case PACKET_COMMAND:
                // Command received
                packetCommand=data;
                // Se il packet e per lo Slave valorizza il byte per il controllo del Check
                if(protocolStatus.DataForUS)
                {
                    packetDataCheck=ProtocolCheckData(0, data);
                }
                // Imposta il prossimo elemento del pacchetto da verificare
                packetNextElement=PACKET_DATALEN;
                break;
            case PACKET_DATALEN:
                // Data lenght
                packetDataLen=data;
                // Imposta il prossimo elemento del pacchetto da verificare
                if(packetDataLen==0)
                {
                    protocolStatus.NoData=1;
                    // Non ci sono dati, quindi il prossimo byte è il Check
                    packetNextElement=PACKET_CHECK;
                }
                else
                {
                    protocolStatus.NoData=0;
                    // Ci sono dati, quindi i prossimi sono da gestire come dati
                    packetNextElement=PACKET_DATA;
                }
                break;
            case PACKET_DATA:
                // Colleziona i dati solo se sono destinati a questo Slave
                if(protocolStatus.DataForUS)
                {
                    packetDataBufferReceived[packetDataCounter]=data;
                    // Aggiorna il byte per il controllo del check
                    packetDataCheck=ProtocolCheckData(packetDataCheck, data);
                }

                packetDataCounter++;
                // Verifica se è stata raggiunta la lunghezza del pacchetto
                if(packetDataCounter>=packetDataLen)
                {
                    // Il prossimo byte del pacchetto è il check
                    packetNextElement=PACKET_CHECK;
                }
                break;
            case PACKET_CHECK:
                // Verifica il byte di check se il packet è dello Slave
                if(protocolStatus.DataForUS)
                {
                    if(packetDataCheck==data)
                    {
                        protocolStatus.ErrorCheck=0;
                    }
                    else
                    {
                        protocolStatus.ErrorCheck=1;
                    }
                }
                packetNextElement=PACKET_END;
                break;
            case PACKET_END:
                // Questo deve valere 0x0D (return) altrimenti il pacchetto non è buono
                if(data!=0x0D)
                {
                    protocolStatus.ErrorEndPacket=1;
                    protocolStatus.PacketComplete=1;
                }
                else
                {
                    protocolStatus.ErrorEndPacket=0;
                    protocolStatus.PacketComplete=1;
                }
                break;
        }

        packetElementCursor=packetNextElement;
    }
}
