/*
 * Created: 2/2/2026 11:43:05 PM
 * Nombre de archivo: SPI.h
 * Description: Include file de librería SPI
 */ 
//#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdint.h>

#ifndef SPI_H_
#define SPI_H_


///////Ennumeraciones para menu de usuario//////
//Tipos de controlador
typedef enum
{
	SPI_master = 0b01010000, //SPE -->1, MSTR -->1
	SPI_slave  = 0b01000000  //SPE -->1, MSTR -->0
	
}SPI_type;
//Tipos de modo de comunicacion
typedef enum
{
	SPI_MODE_1 = 0b00000000, //CPOL -->0, CPHA -->0
	SPI_MODE_2 = 0b00000100, //CPOL -->0, CPHA -->1
	SPI_MODE_3 = 0b00001000, //CPOL -->1, CPHA -->0
	SPI_MODE_4 = 0b00001100  //CPOL -->1, CPHA -->1
	
}SPI_MODE;
//Escoger el divisor de frecuencia para controlar SCK rate
typedef enum
{
	SPI_f_osc_div_2   = 0, //SPR0 --> 0, SPR1 --> 0, SPI2X --> 1
	SPI_f_osc_div_4   = 1, //SPR0 --> 0, SPR1 --> 0, SPI2X --> 0
	SPI_f_osc_div_8   = 2, //SPR0 --> 1, SPR1 --> 0, SPI2X --> 1
	SPI_f_osc_div_16  = 3, //SPR0 --> 1, SPR1 --> 0, SPI2X --> 0
	SPI_f_osc_div_32  = 4, //SPR0 --> 0, SPR1 --> 1, SPI2X --> 1
	SPI_f_osc_div_64  = 5, //SPR0 --> 0, SPR1 --> 1, SPI2X --> 0
	SPI_f_osc_div_128 = 6  //SPR0 --> 1, SPR1 --> 1, SPI2X --> 0
	
}SPI_osc_div;

typedef enum
{
	SPI_data_order_LSB = 0b00100000, //DORD --> 1
	SPI_data_order_MSB = 0b00000000  //DORD --> 0
	
}SPI_data_order;
///Function prototypes
void SPI_init(SPI_type, SPI_data_order, SPI_MODE, SPI_osc_div);
uint8_t SPI_read(void);
void SPI_write(uint8_t data);

#endif /* SPI_H_ */
