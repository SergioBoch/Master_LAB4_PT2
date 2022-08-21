#include <stdint.h>
#include <pic16f887.h>
#include "Oscilador.h"

void int_osc_MHz (uint8_t frec)
{

    switch (frec){
        case 0:
            OSCCONbits.IRCF0 = 0;   //1 MHz
            OSCCONbits.IRCF1 = 0;
            OSCCONbits.IRCF2 = 1;
            break;
        case 1:
            OSCCONbits.IRCF0 = 1;   //2 MHz
            OSCCONbits.IRCF1 = 0;
            OSCCONbits.IRCF2 = 1;
            break;
        case 2:
            OSCCONbits.IRCF0 = 0;   //4 MHz
            OSCCONbits.IRCF1 = 1;
            OSCCONbits.IRCF2 = 1;
            break;
        case 3:
            OSCCONbits.IRCF0 = 1;   //8 MHz
            OSCCONbits.IRCF1 = 1;
            OSCCONbits.IRCF2 = 1;
            break;
        default:
            OSCCONbits.IRCF0 = 0;   //2 MHz
            OSCCONbits.IRCF1 = 1;
            OSCCONbits.IRCF2 = 1;
    }
    OSCCONbits.SCS = 1;     //Se activa reloj interno

}

