/*
 * Created: 2/2/2026 11:43:19 PM
 * Nombre de archivo: SPI.c
 * Description: Libreria para inicializar comunicacion SPI
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "SPI.h"

void SPI_init(SPI_type stype,SPI_data_order sdorder, SPI_MODE smode, SPI_osc_div spifosc)
{
	if (stype & (1 << MSTR)) //MASTER MODE
	{
		DDRB |= (1 << DDB3) | (1 << DDB5) | (1 << DDB2); //MOSI, SCK
		DDRB &= ~(1 << DDB4); //MISO
		SPCR |= (1 << MSTR);
		switch (spifosc) //Elegir el divisor de frecuencia para el SCK rate
		{
		case 0: // fosc/2
			SPSR |= (1 << SPI2X);
			SPCR &= ~((1 << SPR0) | (1 << SPR1));
			break;
		case 1: // fosc/4
			SPSR &= ~(1 << SPI2X);
			SPCR &= ~((1 << SPR0) | (1 << SPR1));
			break;
		case 2: // fosc/8
			SPSR |= (1 << SPI2X);
			SPCR |= (1 << SPR0);
			SPCR &= ~(1 << SPR1);
			break;
		case 3: // fosc/16
			SPCR |= (1 << SPR0);
			SPCR &= ~(1 << SPR1);
			SPSR &= ~(1 << SPI2X);
			break;
		case 4: // fosc/32
			SPSR |= (1 << SPI2X);
			SPCR |= (1 << SPR1);
			SPCR &= ~((1 << SPR0));
			break;
		case 5: // fosc/64
			SPSR &= ~(1 << SPI2X);
			SPCR &= ~((1 << SPR0));
			SPCR |= (1 << SPR1);
			break;
		case 6: // fosc/128
			SPSR &= ~(1 << SPI2X);
			SPCR |= (1 << SPR0) | (1 << SPR1);
			break;
		}
	}
	else //SLAVE MODE
	{
		DDRB |= (1 << DDB4); //MISOsoup
		DDRB &= ~((1 << DDB3) | (1 << DDB5) | (1 << DDB2)); //MOSI, SCK y SS
		SPCR &= ~(1 << MSTR); //MSTR --> 0 
	}
	//ENABLE, DATA ORDER, MODE
	SPCR |= (1 << SPE) | sdorder | smode;
}
uint8_t SPI_read(void)
{
	while(!(SPSR &(1 << SPIF))); //Esperar a recibir data
	return(SPDR); //Leer data proviniente del buffer
}
void SPI_write(uint8_t data)
{
	SPDR = data;
	//while(!(SPSR &(1 << SPIF)));
}
