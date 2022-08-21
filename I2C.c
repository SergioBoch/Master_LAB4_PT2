
#include "I2C.h"

void I2C_Master_Init(const unsigned long c)
{
    SSPCON = 0b00101000;
    SSPCON2 = 0;
    SSPADD = (_XTAL_FREQ/(4*c))-1; //Esto nos da los 100 kHz que necesitamos para la comunicacion
    SSPSTAT = 0;
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;
}

void I2C_Master_Wait()
{
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F)); //revisamos el bit 2 de stat que es RW

}
 
//Iniciamos la comunicacion I2C PIC
void I2C_Master_Start()
{
    I2C_Master_Wait();      //Esperamos el cumplimiento de las condiciones adecuadas
    SSPCON2bits.SEN = 1;    //Inicia la comunicacion I2C
}

//Reinicio de la comunicacion i2c
void I2C_Master_RepeatedStart()
{
    I2C_Master_Wait();      //Esperamos el cumplimiento de las condiciones adecuadas
    SSPCON2bits.RSEN = 1;   //Reiniciamos la comunicacion I2C
}

//Parada de la comunicacion I2C
void I2C_Master_Stop()
{
    I2C_Master_Wait();      //Esperamos el cumplimiento de las condiciones adecuadas
    SSPCON2bits.PEN = 1;    //Se detiene la comunicacion I2C, stop condition initiate
}

void I2C_Master_Write(unsigned d)
{
    I2C_Master_Wait();
    SSPBUF = d;             
}

unsigned short I2C_Master_Read(unsigned short a)
{
    unsigned short temp;
    I2C_Master_Wait();      //Espera que se cumplan las condiciones adecuadas
    SSPCON2bits.RCEN = 1;   //Encendemos Receive Enable Bit
    I2C_Master_Wait();      //Espera que se cumplan las condiciones adecuadas
    temp = SSPBUF;          //Leemos dato
    I2C_Master_Wait();      //Espera que se cumplan las condiciones adecuadas
    if(a == 1){
        SSPCON2bits.ACKDT = 0; //Respondemos con el ACK
    }else{
        SSPCON2bits.ACKDT = 1; //Respondemos sin el ACK
    }
    SSPCON2bits.ACKEN = 1;  //Inicia secuencia
    return temp;
}

void I2C_Slave_Init(uint8_t address)
{ 
    SSPADD = address;
    SSPCON = 0x36;
    SSPSTAT = 0x80;
    SSPCON2 = 0x01;
    TRISC3 = 1;
    TRISC4 = 1;
    SSPIF = 0;
    SSPIE = 1;
    PEIE = 1;
    GIE = 1;
}