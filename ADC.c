/*
 * 
 *
 * Created: 1/27/2026 10:57:12 AM
 *  Author: willi
 */ 

#include <avr/io.h>
#include <stdint.h>
#include "ADC.h"

void init_ADC(void){
	 ADMUX = (1<<REFS0) | (1<<ADLAR); 
	 ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	 
}

uint16_t leer_ADC(uint8_t canal)
{
// inicio de conversión

ADMUX = (ADMUX & 0xF8) | (canal & 0x07);
ADCSRA |= (1<<ADSC);

// fin de conversión
while (ADCSRA & (1<<ADSC));

// lectura del resultado
return ADC;
}
