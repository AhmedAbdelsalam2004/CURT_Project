/*
 * UART.c
 *
 * Created: 10/7/2023 2:50:29 PM
 *  Author: a3abd
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "UART.h"
#include "STD_MacRos.h"

void UART_INIT(int UBRR)
{
	UBRRL = (unsigned char) UBRR;
	UBRRH = (unsigned char) UBRR >> 8;
	setbit(UCSRB , RXEN); // Enable Receiver
	setbit(UCSRB , TXEN); // Enable Transmitter
	UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); //  Asynchronous Operation and 8 bit
}

void UART_TX(char data)
{
	while (Readbit(UCSRA,UDRE) == 0);
	UDR = data;
	while (Readbit(UCSRA,TXC) == 0);
}

char UART_RX()
{
	while (Readbit(UCSRA,RXC) == 0);
	return UDR;
}

void UART_Send_String(char *data)
{
	
	while (*data > 0)
	{
		UART_TX(*data++);
	}
}
