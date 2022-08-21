#include <stdint.h>
#include <pic16f887.h>
#include "ADC.h"

void adc_init (uint8_t adc_cs, uint8_t vref_plus, uint8_t vref_minus)
{
    switch(adc_cs){
        case 0:
            ADCON0bits.ADCS1 = 0; //    FOSC/2
            ADCON0bits.ADCS0 = 0;
            break;
        case 1:
            ADCON0bits.ADCS1 = 0; //    FOSC/8
            ADCON0bits.ADCS0 = 1;
            break;
        case 2:
            ADCON0bits.ADCS1 = 1; //    FOSC/32
            ADCON0bits.ADCS0 = 0;
            break;
        case 3:
            ADCON0bits.ADCS1 = 1; //    FRC  (clock derived from a dedicated internal oscillator = 500 kHz max)
            ADCON0bits.ADCS0 = 1;
            break;
        default:
            ADCON0bits.ADCS1 = 1; //    FOSC/32
            ADCON0bits.ADCS0 = 0;
            
    }
    switch (vref_plus){
        case 0:
            ADCON1bits.VCFG0 = 0;       //Vdd
            break;
        case 1:
            ADCON1bits.VCFG0 = 1;      //Vref + pin
            break;
        default:
            ADCON1bits.VCFG0 = 0;  
        
    }
    
    switch (vref_minus){
        case 0:
            ADCON1bits.VCFG1 = 0;       //Vss
            break;
        case 1:
            ADCON1bits.VCFG1 = 1;       //Vref-pin
            break;
        default:
            ADCON1bits.VCFG1 = 0;
    }
    
    
}

void adc_start (uint8_t channel)
{
    ADCON0bits.ADON = 1;        //se enciende el modulo ADC
    __delay_us(50);             //delay de 50uS 
    ADCON0bits.GO = 1;          //Se inicializa la conversion de valores

    PIE1bits.ADIE = 1;      // activar interrupcion por ADC

    switch(channel){
        case 0:
            ADCON0bits.CHS = 0b0000;//AN0
            break;
        case 1:
            ADCON0bits.CHS = 0b0001;//AN1
            break;
        case 2:
            ADCON0bits.CHS = 0b0010;//AN2
            break;
        case 3:
            ADCON0bits.CHS = 0b0011;//AN3
            break;
        case 4:
            ADCON0bits.CHS = 0b0100;//AN4
            break;  
        case 5:
            ADCON0bits.CHS = 0b0101;//AN5
            break;
        case 6:
            ADCON0bits.CHS = 0b0110;//AN6
            break;
        case 7:
            ADCON0bits.CHS = 0b0111;//AN7
            break;
        case 8:
            ADCON0bits.CHS = 0b1000;//AN8
            break;
        case 9:
            ADCON0bits.CHS = 0b1001;//AN9
            break;  
        case 10:
            ADCON0bits.CHS = 0b1010;//AN10
            break;
        case 11:
            ADCON0bits.CHS = 0b1011;//AN11
            break;
        case 12:
            ADCON0bits.CHS = 0b1100;//AN12
            break;
        case 13:
            ADCON0bits.CHS = 0b1101;//AN13
            break;
        default:
            ADCON0bits.CHS = 0b0000;//AN0
            break;
            
    }

}

uint16_t adc_read (void)
{
    ADCON1bits.ADFM = 1;        //justificacion a la derecha

    uint16_t val = 0;
    val = ADRESH;
    val = val << 8;
    val = val | ADRESL;
    
    PIR1bits.ADIF = 0;      // bajar bandera de interrupcion del ADC
    return val;
}

