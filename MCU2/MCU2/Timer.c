/*
 * Timer.c
 *
 * Created: 9/29/2023 3:08:33 PM
 *  Author: a3abd
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "STD_MacRos.h"
#include "Timer.h"


void Timer0_Fast_PWM_INIT()
{
	setbit(TCCR0,WGM00);// Set mode to Fast PWM
	setbit(TCCR0,WGM01);
	
	setbit(DDRB,3);// Set OC0 as output
	
	clrbit(TCCR0,CS00);// PreScalar = 8
	setbit(TCCR0,CS01);
	clrbit(TCCR0,CS02);
	
	clrbit(TCCR0,COM00);// non_Inverting mode
	setbit(TCCR0,COM01);
	
	OCR0 = 0;
}

void Timer2_Servo_Motor_INIT()
{
	 // Set mode to Fast PWM
	 setbit(TCCR2, WGM20);
	 setbit(TCCR2, WGM21);
	 
	 // Set OC2 (PD7) as output
	 setbit(DDRD, PD7);
	 
	 // Set Prescaler to 64
	 clrbit(TCCR2, CS22);
	 setbit(TCCR2, CS21);
	 setbit(TCCR2, CS20);
	 
	 // Set to non-inverting mode
	 clrbit(TCCR2, COM20);
	 setbit(TCCR2, COM21);
	 
	 OCR2 = 0;
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

void Timer2_Set_Duty_Cycle(float DC) {
	
	if (DC > 0 && DC <= 1) 
	{
		DC = DC * 256;
		OCR2 = DC - 1;
	} 
		else if (DC <= 0) 
	{
		OCR2 = 0;
	}
}
