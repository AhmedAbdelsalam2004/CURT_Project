/*
 * EEPROM.h
 *
 * Created: 10/20/2023 2:32:35 PM
 *  Author: a3abd
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_


char EEPROM_Read(char Address);
void EEPROM_Write(char Address,char Data);


#endif /* EEPROM_H_ */