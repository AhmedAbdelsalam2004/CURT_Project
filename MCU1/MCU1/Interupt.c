/*
 * Interupt.c
 *
 * Created: 9/22/2023 3:59:09 PM
 *  Author: a3abd
 */ 

#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "STD_MacRos.h"

volatile int flag=0;

void External_Interupt0_Init()
{
	clrbit(DDRD, 2);// Make this pin Input
	setbit(MCUCR, ISC01);// Interrupt flag will set in the rising edge interrupt 0
	setbit(MCUCR, ISC00);
	setbit(GICR, INT0);//Enable PIE
}

void External_Interupt1_Init()
{
	clrbit(DDRD, 3);
	setbit(MCUCR, ISC11);// Interrupt flag will set in the rising edge interrupt 1
	setbit(MCUCR, ISC10);
	setbit(GICR, INT1);//Enable PIE
}