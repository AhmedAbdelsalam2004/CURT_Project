/*
 * Timer.c
 *
 * Created: 9/29/2023 3:08:33 PM
 *  Author: a3abd
 */ 

#define F_CPU 1000000ul
#include <avr/io.h>
#include <util/delay.h>
#include "STD_MacRos.h"
#include "Timer.h"


void timer1_init() {
	// Set timer1 to normal mode
	setbit(TCCR1B,CS12);// Prescaler = 256
	TCNT1 = 63583; // Initialize counter to achieve 500ms overflow
	setbit(TIMSK,TOIE1);// Enable overflow interrupt
}

void Timer0_Fast_PWM_INIT()
{
	setbit(TCCR0,WGM00);// Set mode to Fast PWM
	setbit(TCCR0,WGM01);
	
	setbit(DDRB,3);// Set OC0 as output
	
	clrbit(TCCR0,CS00);// PreScalar = 8
	setbit(TCCR0,CS01);
	clrbit(TCCR0,CS02);
	
	clrbit(TCCR0,COM00);// nin_Inverting mode
	setbit(TCCR0,COM01);
	
	OCR0 = 0;
}

void Timer0_Set_Duty_Cycle(float DC)
{
	if(DC > 0 && DC <= 1)
	{
		DC = DC * 256;
		OCR0 = DC - 1;
	}

	else if(DC <= 0)
	{
		OCR0 = 0;
	}
	
}
