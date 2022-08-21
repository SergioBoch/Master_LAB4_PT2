/* 
 * File: LCD.c  
 * Se utilizó y se adaptaron las librerías de Ligo George 
 * de la página www.electrosome.com
 * Enlace: https://electrosome.com/lcd-pic-mplab-xc8/
 * Revision history: 
 */

#include <stdint.h>
#include <pic16f887.h>
#include "LCD.h"

void Lcd_Port(char a)
{
    PORTD = a;
    
}

void Lcd_Cmd(char a)
{
    RS = 0;
    Lcd_Port(a);
    EN = 1;
    __delay_ms(4);
    EN = 0;
}

void Lcd_Clear(void) {
    Lcd_Cmd(0x01);
}

void Lcd_Set_Cursor(char a, char b)
{
    char temp;
    if (a == 1) {
        temp = 0x80 + b - 1;
        Lcd_Cmd(temp);
    } else if (a == 2) {
        temp = 0xC0 + b - 1;
        Lcd_Cmd(temp);
    }
}

void Lcd_Init(uint8_t modo) {
    switch(modo){
        case 0:
            Lcd_Port(0x00); //declarar salidas
            __delay_ms(20); //esperar mas de 15ms
            Lcd_Cmd(0x03);  //activamos bits D5,D4
            __delay_ms(5);  //
            Lcd_Cmd(0x03);
            __delay_us(11);
            Lcd_Cmd(0x03);
            Lcd_Cmd(0x02);
            Lcd_Cmd(0x02);
            Lcd_Cmd(0x08);
            Lcd_Cmd(0x00);
            Lcd_Cmd(0x0C);
            Lcd_Cmd(0x00);
            Lcd_Cmd(0x06);
            break;
        case 1:
            Lcd_Port(0b00000000);//Encendido
            __delay_ms(20);     //Espero 20ms
            Lcd_Cmd(0b00110000);
            __delay_ms(4);      //espero 4ms
            Lcd_Cmd(0b00110000);
            __delay_us(110);
            Lcd_Cmd(0b00110000);
            Lcd_Cmd(0b00110000);
            Lcd_Cmd(0b00111000);
            Lcd_Cmd(0b00001100);
            Lcd_Cmd(0b00000001);
            Lcd_Cmd(0b00000110);
            break;
            
        default:
            Lcd_Port(0x00); //declarar salidas
            __delay_ms(20); //esperar mas de 15ms
            Lcd_Cmd(0x03);  //activamos bits D5,D4
            __delay_ms(5);  //
            Lcd_Cmd(0x03);
            __delay_us(11);
            Lcd_Cmd(0x03);
            Lcd_Cmd(0x02);
            Lcd_Cmd(0x02);
            Lcd_Cmd(0x08);
            Lcd_Cmd(0x00);
            Lcd_Cmd(0x0C);
            Lcd_Cmd(0x00);
            Lcd_Cmd(0x06);
            break;
    }          
}

void Lcd_Write_Char(char a) {
    char temp, y;
    RS = 1;
    Lcd_Port(a);
    EN = 1;
    __delay_us(40);
    EN = 0;
}

void Lcd_Write_String(char *a) {
    int i;
    for (i = 0; a[i] != '\0'; i++)
        Lcd_Write_Char(a[i]);
}

void Lcd_Shift_Right(void) {
    Lcd_Cmd(0xC8);
}

void Lcd_Shift_Left(void) {
    Lcd_Cmd(0x18);
}

