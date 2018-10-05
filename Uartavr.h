/*
 * UartC__.h
 *
 * Created: 9.5.2017 22:03:05
 *  Author: Bozic
 */
#include <stdbool.h>
#include <avr/io.h>
#include <string.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>


#ifndef UARTavr_H_
#define UARTavr_H_

#ifndef F_CPU1
#define F_CPU1 8000000
#endif

#ifndef BAUD
#define BAUD 9600
#endif

#define MYUBRR F_CPU1/16/BAUD -1

extern char Resive[];
extern char ResiveBack[];

void Uart_inic();
void uart_send_string(char *);
bool uart_full();
char* uart_full_string();
void uart_clear();





#endif
 /* UARTC++_H_ */