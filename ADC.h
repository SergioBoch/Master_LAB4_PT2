
#ifndef ADC_CONFIG_H
#define	ADC_CONFIG_H
#ifndef _XTAL_FREQ 
#define _XTAL_FREQ 8000000
#endif
#include <stdint.h>
#include <xc.h>
#include "ADC.h"

void adc_init (uint8_t adc_cs, uint8_t vref_plus, uint8_t vref_minus);
void adc_start (uint8_t channel);
uint16_t adc_read (void);

#endif	/* ADC_CONFIG_H */