#ifndef OSCILADOR_CONFIG_H
#define	OSCILADOR_CONFIG_H
#pragma config FOSC = INTRC_NOCLKOUT //Oscillator Selection bits

#include <stdint.h>
#include <xc.h>
#include "Oscilador.h"

void int_osc_MHz (uint8_t frec);
#endif	/* OSCILADOR_CONFIG_H */
