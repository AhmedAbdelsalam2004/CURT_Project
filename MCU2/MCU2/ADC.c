/*
 * ADC.c
 *
 * Created: 9/23/2023 2:40:45 PM
 *  Author: a3abd
 */ 

#define F_CPU 8000000ul
#include "STD_MacRos.h"
#include "ADC.h"
#include <avr/io.h>
#include <util/delay.h>

void ADC_Init()
{ 
	setbit(ADMUX, REFS0); // AVcc with external capacitor at AREF pin
	setbit(ADCSRA,ADEN);  // Enable ADC
	setbit(ADCSRA,ADPS0); //set Prescaler to 128
	setbit(ADCSRA,ADPS1);
	setbit(ADCSRA,ADPS2);
}

int ADC_Read(char ch)
{
	int value=-1;
	if(ch>=0 && ch<=8)
	{
		ADMUX = (ADMUX & 0xE0) | ch; //channel selection 
		setbit(ADCSRA,ADSC);
		while(Readbit(ADCSRA,ADIF) != 1);
		_delay_ms(1);
		value = (int)ADCL + (int)ADCH * 256;
	}
	return value;
}