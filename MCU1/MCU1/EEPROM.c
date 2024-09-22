/*
 * EEPROM.c
 *
 * Created: 10/20/2023 2:32:22 PM
 *  Author: a3abd
 */ 

#include <avr/io.h>
#include "STD_MacRos.h"
#include "EEPROM.h"

char EEPROM_Read(char Address)
{
	 while (EECR & (1 << EEWE)); // Wait for completion of previous write
	 EEAR = Address;             // Set up address register
	 EECR |= (1 << EERE);        // Start EEPROM read by writing EERE
	 return EEDR;                // Return the data from the EEPROM data register
}

void EEPROM_Write(char Address, char Data)
{
	while (EECR & (1 << EEWE)); // Wait for completion of previous write
	EEAR = Address;             // Set up address and data registers
	EEDR = Data;
	EECR |= (1 << EEMWE);       // Write logical one to EEMWE
	EECR |= (1 << EEWE);        // Start EEPROM write by setting EEWE
}
