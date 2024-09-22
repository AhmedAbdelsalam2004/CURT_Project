/*
 * MCU2.c
 *
 * Created: 8/13/2024 4:11:30 AM
 * Author : a3abd
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "STD_MacRos.h"
#include "UART.h"
#include "Timer.h"
#include "ADC.h"


/*Function to control LEDs based on received temperature from MCU1*/
void Control_Leds(unsigned char Temperature)
{
	if(Temperature < 20)
	{
		setbit(PORTC, 2);  // Turn on Green LED
		clrbit(PORTC, 4);  // Turn off Yellow LED
		clrbit(PORTC, 6);  // Turn off Red LED
		clrbit(PORTA, 1);  // Turn off Buzzer
	}
	
	else if(Temperature >= 20 && Temperature < 40)
	{
		setbit(PORTC, 4);  // Turn on Yellow LED
		clrbit(PORTC, 2);  // Turn off Green LED
		clrbit(PORTC, 6);  // Turn off Red LED
		clrbit(PORTA, 1);  // Turn off Buzzer
	}
	
	else if(Temperature >= 40 && Temperature <= 50)
	{
		clrbit(PORTC, 2);  // Turn off Green LED
		clrbit(PORTC, 4);  // Turn off Yellow LED
		setbit(PORTC, 6);  // Turn on Red LED
		clrbit(PORTA, 1);  // Turn off Buzzer
	}
	
	else if(Temperature > 50)
	{
		Timer0_Set_Duty_Cycle(0.5);
		clrbit(PORTC, 2);  // Turn off Green LED
		clrbit(PORTC, 4);  // Turn off Yellow LED
		setbit(PORTC, 6);  // Turn on Red LED
		setbit(PORTA, 1);  //Activate Buzzer
	}	
}

/* Function to control servo motor in Abnormal state */
void Control_Servo_Motor(void)
{
	Timer2_Set_Duty_Cycle(0.075); // Set the Servo motor for 90 degrees
}

/* Function for all initializations needed */
void System_INITS(void)
{
	UART_INIT(51);//UBRR is 51 for BAUD rate of 9600 with 8MHz frequency
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
	
    while (1) 
    {
		Received_Data = UART_RX();
		
		Control_Leds(Received_Data);
		
		if(Received_Data == 'S')// Condition for press of button
		{
			Timer0_Set_Duty_Cycle(0);
			while(Received_Data >= 40);
		}
		
		else if(Received_Data == 'A')// Condition for Abnormal state
		{
			Control_Servo_Motor();
		}
		
		else
		{
			Potentiometer = ADC_Read(0);
			Duty_Cycle = (Potentiometer) / 1024;
			Timer0_Set_Duty_Cycle(Duty_Cycle);	
		}
		
    }
}

