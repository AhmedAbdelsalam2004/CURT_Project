/*
 * MCU1.c
 *
 * Created: 8/12/2024 9:02:42 PM
 * Author : a3abd
 */ 

#define F_CPU 1000000UL
#define EEPROM_STATE_ADDRESS 0x00  // Address 0x00 in EEPROM for system state
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "STD_MacRos.h"
#include "UART.h"
#include "ADC.h"
#include "Timer.h"
#include "Interupt.h"
#include "EEPROM.h"

unsigned char temperature = 0;
unsigned char Over_Flow_Counter = 0;


/* Function to control fan speed based on temperature */
void Control_Fan(unsigned char temperature)
{
	if (temperature < 20)
	{
		Timer0_Set_Duty_Cycle(0);// DC motor off
		EEPROM_Write(EEPROM_STATE_ADDRESS, 1);// Write Normal mode to EEPROM
	}
	
	else if (temperature >= 20 && temperature < 30)
	{
		Timer0_Set_Duty_Cycle(0.25);// DC motor at 25%
		EEPROM_Write(EEPROM_STATE_ADDRESS, 1);// Write Normal mode to EEPROM
	}
	
	else if (temperature >= 30 && temperature < 35)
	{
		Timer0_Set_Duty_Cycle(0.5);// DC motor at 50%
		EEPROM_Write(EEPROM_STATE_ADDRESS, 1);// Write Normal mode to EEPROM
	}
	
	else if (temperature >= 35 && temperature < 40)
	{
		Timer0_Set_Duty_Cycle(0.75);// DC motor at 75%
		EEPROM_Write(EEPROM_STATE_ADDRESS, 1);// Write Normal mode to EEPROM
	}
	
	else if (temperature >= 40 && temperature <= 50)
	{
		Timer0_Set_Duty_Cycle(1);// DC motor at 100%
		EEPROM_Write(EEPROM_STATE_ADDRESS, 1);// Write Normal mode to EEPROM
	}
	
	else if (temperature > 50)
	{
		Timer0_Set_Duty_Cycle(1);// DC motor at 100%
		if(EEPROM_Read(EEPROM_STATE_ADDRESS) != 3)
		{
			EEPROM_Write(EEPROM_STATE_ADDRESS, 2);// Write Emergency mode to EEPROM
		}
		
	}
}

void Send_Data_MCU2(temperature)
{
	if(temperature < 20)
	{
		UART_TX('G');// G for green led
		_delay_ms(100);
	}
	else if(temperature >= 20 && temperature < 40)
	{
		UART_TX('Y');// Y for yellow led
		_delay_ms(100);
	}
	else if(temperature >= 40 && temperature <= 50)
	{
		UART_TX('R');// R for red led
		_delay_ms(100);
	}
	else if(temperature > 50)
	{
		if(EEPROM_Read(EEPROM_STATE_ADDRESS) == 3)
		{
			UART_TX('A');//Send to MCU2 for Abnormal state
			_delay_ms(100);
		}
		
		else
		{
			UART_TX('E');//Send to MCU2 for Emergency state
		}
		
	}
}

/* Function for all initializations needed */
void INITS_System(void)
{
	sei();         // Enable global interrupt (GIE)
	UART_INIT(12); //UBRR is 12 for BAUD rate of 9600 with 1MHz frequency
	ADC_Init();
	Timer0_Fast_PWM_INIT();
	External_Interupt1_Init();
	timer1_init();
	EEPROM_Write(EEPROM_STATE_ADDRESS, 1);// Write Normal mode to EEPROM
}

int main(void)
{
	INITS_System();
		
	clrbit(DDRA,0);//Temperature sensor pin Input
	
	
	long int x = 0 , temp = 0;
	int volt = 0;
	
    while (1) 
    {
		x = ADC_Read(0);// Read ADC value of Temperature sensor 
		
		if (x != temp)
		{
			temp = x;
			volt = (2560 * x) / 1024;
			temperature = volt / 10;// Calculate temperature using ADC value
			
			Control_Fan(temperature);
			
		}
		
		Send_Data_MCU2(temperature);
    }
}

ISR(INT1_vect)
{
	if(temperature >= 40 && temperature <= 50)
	{
		UART_TX('S');// Stop Machine
	}
}

ISR(TIMER1_OVF_vect)
{
	TCNT1 = 63583; // Reset counter to achieve 500ms overflow
	if (temperature > 50) 
	{
		Over_Flow_Counter++;
		
		if(Over_Flow_Counter >= 7) // 14 overflows * 500ms = 7 seconds
		{
			EEPROM_Write(EEPROM_STATE_ADDRESS, 3); //Write Abnormal State to EEPROM
			UART_TX('A');
			Over_Flow_Counter = 0;                 //Restart counter
		}
	}
	else
	{
		Over_Flow_Counter = 0; //Restart counter if condition is no longer met
	}
}
		

