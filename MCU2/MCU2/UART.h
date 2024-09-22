/*
 * UART.h
 *
 * Created: 10/7/2023 2:50:46 PM
 *  Author: a3abd
 */ 


#ifndef UART_H_
#define UART_H_

void UART_INIT(int UBRR);
void UART_TX(char data);
char UART_RX();



#endif /* UART_H_ */