#include <stdint.h>
#include <pic16f887.h>
#include "TMR0.h"

void tmr0_init (uint8_t prescaler)
{
    INTCONbits.T0IE = 1;
    OPTION_REGbits.PSA = 0;  
    OPTION_REGbits.T0CS = 0;  
    OPTION_REGbits.T0SE = 0; 
    
    
    
    switch(prescaler){
        case 0:
            OPTION_REGbits.PS2 = 0; // 1:2
            OPTION_REGbits.PS1 = 0;
            OPTION_REGbits.PS0 = 0;
            break;
        case 1:
            OPTION_REGbits.PS2 = 0; // 1:4
            OPTION_REGbits.PS1 = 0;
            OPTION_REGbits.PS0 = 1;
            break;
        case 2:
            OPTION_REGbits.PS2 = 0; // 1:8
            OPTION_REGbits.PS1 = 1;
            OPTION_REGbits.PS0 = 0;
            break;
        case 3:
            OPTION_REGbits.PS2 = 0; // 1:16
            OPTION_REGbits.PS1 = 1;
            OPTION_REGbits.PS0 = 1;
            break;
        case 4:
            OPTION_REGbits.PS2 = 1; // 1:32
            OPTION_REGbits.PS1 = 0;
            OPTION_REGbits.PS0 = 0;
            break;
        case 5:
            OPTION_REGbits.PS2 = 1; // 1:64
            OPTION_REGbits.PS1 = 0;
            OPTION_REGbits.PS0 = 1;
            break;
        case 6:
            OPTION_REGbits.PS2 = 1; // 1:128
            OPTION_REGbits.PS1 = 1;
            OPTION_REGbits.PS0 = 0;
            break;
        case 7:
            OPTION_REGbits.PS2 = 1; // 1:256
            OPTION_REGbits.PS1 = 1;
            OPTION_REGbits.PS0 = 1;
            break;
        default:
            OPTION_REGbits.PS2 = 1; // 1:256
            OPTION_REGbits.PS1 = 1;
            OPTION_REGbits.PS0 = 1;
    }
}

uint8_t tmr0_reload_v2 (void)
{   
  
  TMR0 = _tmr0_value;
  INTCONbits.T0IF = 0;//tmr0 int
  return TMR0;
}