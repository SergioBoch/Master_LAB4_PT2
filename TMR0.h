
#ifndef TMR0_CONFIG_H
#define	TMR0_CONFIG_H

#ifndef _tmr0_value
#define _tmr0_value 178 //Valor a cargar
#endif

#include <stdint.h>
#include <xc.h>
#include "TMR0.h"
void tmr0_init (uint8_t prescaler);
uint8_t tmr0_reload_v2 (void);

#endif	/* TMR0_CONFIG_H */