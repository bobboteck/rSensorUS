#include "settings.h"
#include "serial.h"
/**********************
 * DEFINIZIONE PRAGMA *
 **********************/
#pragma config OSC = HSPLL      // Usare con quarzo da 10MHz e PPL 4x
#pragma config FCMEN= OFF       // File-Safe clock monitor
#pragma config IESO = OFF       // Internal External OSC SwitchOver
#pragma config PWRT = ON        // Power Up timer
#pragma config BOREN= OFF       // Brown Out reset
#pragma config BORV = 0         // Brown Out voltage
#pragma config WDT = OFF        // WhatchDog timer
#pragma config WDTPS= 1         // WhatchDog postscaler
#pragma config MCLRE= ON        // MCLR enable
#pragma config LPT1OSC = OFF    // T1 Oscillator enable
#pragma config PBADEN = OFF     // PORTB A/D enable
#pragma config CCP2MX = PORTC   // CCP2 Multiplex with RB3 or RC1
#pragma config STVREN = ON      // Stack Overflow reset
#pragma config LVP = OFF        // Low Voltage ICSP
#pragma config XINST= OFF
#pragma config DEBUG= OFF       // Background Debugger enable
#pragma config CP0 = OFF        // Code Protection Block 0
#pragma config CP1 = OFF
#pragma config CP2 = OFF
#pragma config CP3 = OFF
#pragma config CPB = OFF        // Boot Block
#pragma config CPD = OFF        // Data EEPROM
#pragma config WRT0 = OFF       // Write Protection
#pragma config WRT1 = OFF
#pragma config WRT2 = OFF
#pragma config WRT3 = OFF
#pragma config WRTB = OFF       // Boot Block
#pragma config WRTC = OFF       // Configuration Register
#pragma config WRTD = OFF       // Data EEPROM
#pragma config EBTR0= OFF       // Table Read protection Block 0
#pragma config EBTR1= OFF
#pragma config EBTR2= OFF
#pragma config EBTR3= OFF
#pragma config EBTRB= OFF       // Boot Block Table Read protection


void BoardSettings(void)
{
    SerialSettings(BAUD_9600, BIT_NUMBER_8);
}