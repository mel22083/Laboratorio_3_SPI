/*
 * Labo 3 digital 2.c
 *
 * Created: 2/8/2026 3:43:52 PM
 * Author : willi
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "SPI.h"
#include "ADC.h"

volatile uint8_t adc1 = 0;
volatile uint8_t adc2 = 0;
volatile uint8_t pot = 0;

int main(void)
{
	init_ADC();
	cli();

	
	ADCSRA |= (1 << ADIE);   // habilita interrupción ADC
	ADCSRA |= (1 << ADSC);	// arranca primera conversión
	
	SPI_init(SPI_slave, SPI_data_order_LSB, SPI_MODE_1, SPI_f_osc_div_32);
	// activamos la interrupcion del spi
	SPCR |= (1 << SPIE);
	//portd como salida
	DDRD = 0xFF;
	PORTD = 0x00;
	// potenciometros como entradas
	DDRC &= ~((1 << PORTC0) | (1 << PORTC1));
	 
	 sei();
    
	while (1) 
    {
		
    }
	}
ISR(ADC_vect){
	switch(pot){
		case 0:
			adc1 = ADCH;
			ADMUX = (ADMUX & 0xF8) | 1; 
			pot = 1;
			break; 
		case 1: 
			adc2 = ADCH;
			ADMUX = (ADMUX & 0xF8) | 0;
			pot = 0;
			break;
		default:
			break;
	}
	ADCSRA |= (1<<ADSC);
}

ISR(SPI_STC_vect){
	uint8_t valor_spi = SPDR;
	
	switch (valor_spi){
		case'1':
			SPDR = adc1;
			break; 
		case '2':
			SPDR = adc2;
			break;
		default:
			PORTD = valor_spi;
			break;
	}
}



