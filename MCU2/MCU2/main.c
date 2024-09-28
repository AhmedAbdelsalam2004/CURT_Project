/*
 * MCU2.c
 *
 * Created: 8/13/2024 4:11:30 AM
 * Author : a3abd
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "STD_MacRos.h"
#include "UART.h"
#include "Timer.h"
#include "ADC.h"


unsigned char Mortor_flag = 0;


/* Function to control servo motor in Abnormal state */
void Control_Servo_Motor(void)
{
	Timer2_Set_Duty_Cycle(0.5); // Set the Servo motor for 90 degrees
}

/*Function to control LEDs based on received temperature from MCU1*/
void Control_System(unsigned char Received_data)
{
	switch(Received_data)
	{
		case 'G':
			setbit(PORTC, 2); //Turn on green led
			clrbit(PORTC, 4); //Turn off yellow led
			clrbit(PORTC, 6); //Turn off red led
			Mortor_flag = 0;
			break;
		case 'Y':
			clrbit(PORTC, 2); //Turn off green led
			setbit(PORTC, 4); //Turn on yellow led
			clrbit(PORTC, 6); //Turn off red led
			Mortor_flag = 0;
			break;
		case 'R':
			clrbit(PORTC, 2); //Turn off green led
			clrbit(PORTC, 4); //Turn off yellow led
			setbit(PORTC, 6); //Turn on red led
			Mortor_flag = 0;
			break;
		case 'S':
			Timer0_Set_Duty_Cycle(0);
			Mortor_flag = 1;
			break;
		case 'E':
			setbit(PORTA, 1);//Turn Buzzer on
			break;
		case 'A':
			Control_Servo_Motor();
			Timer0_Set_Duty_Cycle(0);
			Mortor_flag = 1;
			break;
	}
}

/* Function for all initializations needed */
void System_INITS(void)
{
	UART_INIT(12);//UBRR is 12 for BAUD rate of 9600 with 1MHz frequency
	Timer0_Fast_PWM_INIT();
	Timer2_Servo_Motor_INIT();
	ADC_Init();
}


int main(void)
{
	System_INITS();
	
	setbit(DDRC,2); //Green Led pin Output
	setbit(DDRC,4); //Yellow Led pin Output
	setbit(DDRC,6); //Red Led pin Output
	setbit(DDRA,1); //Buzzer pin Output
	clrbit(DDRA,0); //Potentiometer pin Input
	
	unsigned char Received_Data = 0;
	double Potentiometer = 0;
	float Duty_Cycle = 0;
	double temp = 0;
	
    while (1) 
    {

		Received_Data = UART_RX();
		
		Control_System(Received_Data);
		
		Potentiometer = ADC_Read(0);
		
		if(Potentiometer != temp)
		{
			temp = Potentiometer;
			Duty_Cycle = (Potentiometer) / 1023;
			
			if(Mortor_flag == 0)
			{
				Timer0_Set_Duty_Cycle(Duty_Cycle);
			}
		}
		
		
    }
}

