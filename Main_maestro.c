/*
 * File:   Main_Maestro.c
 * Author: Sergio Boch 20887
 *
 * Created on August 17, 2022, 5:16 PM
 */

// CONFIG1
//#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include "Oscilador.h" 
#include "ADC.h"  
#include "TMR0.h"
#include "I2C.h"
#include "LCD.h"
#include <string.h>

#include <xc.h>
#include <stdint.h>
#include <pic16f887.h>

#define _XTAL_FREQ 8000000

uint8_t contador = 0; 
uint8_t tmr0_flag = 0;
uint8_t val_lcd_adc = 0;
uint8_t val_lcd_RTC = 0;

void setup(void);

void __interrupt() isr (void){

    if (T0IF){    
        
        tmr0_reload_v2();
        tmr0_flag = 1;
        contador++; 
        if(contador>10){
            contador = 0;
            tmr0_flag = 0;
        }
    }
      
    if (INTCONbits.RBIF){
  
        if (!PORTBbits.RB1){
        I2C_Master_Start();     
        I2C_Master_Write(0x50); 
        I2C_Master_Write(2);    
        I2C_Master_Stop();
        __delay_ms(10);
        }
        else
            I2C_Master_Start();     
            I2C_Master_Write(0x50); 
            I2C_Master_Write(0);   
            I2C_Master_Stop();
            __delay_ms(10);

        if (!PORTBbits.RB3){
            I2C_Master_Start();    
            I2C_Master_Write(0x50); 
            I2C_Master_Write(8);    
            I2C_Master_Stop();
            __delay_ms(10);
        }
        else
            I2C_Master_Start();    
            I2C_Master_Write(0x50);
            I2C_Master_Write(0);   
            I2C_Master_Stop();
            __delay_ms(10);
            
        INTCONbits.RBIF = 0;
        
    }
    
    return;
}

void main(void) {     
    setup();
    while(1){        

        I2C_Master_Start();
        I2C_Master_Write(0x60); 
        I2C_Master_Read(1);
        I2C_Master_Write(0); 
        val_lcd_RTC = I2C_Master_Read(1); 
        I2C_Master_Stop();
        __delay_us(200);

         Lcd_Set_Cursor(1,1);
        Lcd_Write_String("POT   Tiempo");
        Lcd_Set_Cursor(2,1);
        Lcd_Write_Char(val_lcd_adc);
        Lcd_Set_Cursor(2,8);
        Lcd_Write_Char(val_lcd_RTC); 
        } 
}
void setup (void){
    ANSEL = 0;       //Entrada analogica
    ANSELH = 0;        // Usaremos solo I/O digitales
   
    TRISA = 0b00000000;           
    TRISB = 0b00001111;                        
    TRISD = 0b00000000;
    TRISC = 0b00000000;

    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    OPTION_REGbits.nRBPU = 0;
    WPUB = 0b00001111;
    IOCB = 0b00001111;
    I2C_Master_Init(100000); 
    tmr0_init(7);
    int_osc_MHz (3); //Config a 8MHz
    adc_init(1,0,0);   //  FOSC/32,Vdd,Vss

    unsigned int a;
    Lcd_Init(1);
    INTCONbits.RBIF = 0;        //Habilitamos interrupciones Puerto B
    INTCONbits.RBIE = 1;
    INTCONbits.PEIE = 1;        // Habilitamos interrupciones perifericas
    INTCONbits.GIE = 1;         // Habilitamos interrupciones globales  
    
    return;
}

