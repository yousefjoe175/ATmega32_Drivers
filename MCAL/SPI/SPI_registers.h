#ifndef    SPI_REGISTERS_H
#define    SPI_REGISTERS_H

#define SPI_SPCR	*((volatile u8*)(0x2D))
#define SPI_SPSR	*((volatile u8*)(0x2E))
#define SPI_SPDR	*((volatile u8*)(0x2F))
#define SPI_SREG	*((volatile u8*)(0x2F))

/* SPCR */
#define SPI_SPR0	0
#define SPI_SPR1	1
#define SPI_CPHA	2
#define SPI_CPOL	3
#define SPI_MSTR	4
#define SPI_DORD	5
#define SPI_SPE		6
#define SPI_SPIE	7

/* SPSR */
#define SPI_SPI2X	0
#define SPI_WCOL	6
#define SPI_SPIF	7

/* pin assignment */
#define SPI_MOSI	DIO_PORTB,DIO_PIN5
#define SPI_MISO	DIO_PORTB,DIO_PIN6
#define SPI_SCK		DIO_PORTB,DIO_PIN7
#define SPI_SS		DIO_PORTB,DIO_PIN4

#endif