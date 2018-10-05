/*
 * UartAVRc.c
 *
 * Created: 23.5.2017 14:11:19
 *  Author: Bozic

 */ 


#include "Uartavr.h"
#include <avr/interrupt.h>

char Resive[100],ResiveBack[100],newchar;
bool ResivedOK=false,writeInBaffer=false,end=false;
volatile bool StigliPodaci=false,MozeZavrsetak=false;
int i=0,combo=0;

void Uart_inic()
{
	UBRRH =(MYUBRR)>>8;
	UBRRL = MYUBRR;
	
	UCSRB |= (1 << RXEN) | (1 << TXEN);      // Enable receiver and transmitter
	UCSRB |= (1 << RXCIE);                   // Enable the receiver interrupt
	UCSRC |= (1 << URSEL) |(1 << UCSZ1) | (1 << UCSZ0);    // Set frame: 8data, 1 stp
	
	//UCSRA= 0x00;                 // Clear the UASRT status register
	//UCSRB= (1<<RXEN) | (1<<TXEN);     // Enable Receiver and Transmitter
	//UCSRC= (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);   // Async-mode
	
	
	for(int k=0;k<100;k++)
	{
		Resive[k]='\0';
	}
	
	/*
	//Tajmer za kraj uarta
	  // Prescaler = FCPU/1024
	  TCCR0|=(1<<CS02)|(1<<CS00);

	  //Enable Overflow Interrupt Enable
	  TIMSK|=(1<<TOIE0);

	  //Initialize Counter
	  TCNT0=0;
	  
	  sei();*/
	 // set up timer with prescaler = 8
	 TCCR1B |= (1 << CS11);  // okida na 1uS
	 
	 // initialize counter
	 TCNT1 =  0;
	 
	 // enable overflow interrupt
	 TIMSK |= (1 << TOIE1);
	 
	 // enable global interrupts
	 sei();
	  
}
void uart_send_string(char *Str)
{
	int x=strlen(Str),n=0;
	for(n=0;n<x;n++)
	{
		while ( !(UCSRA & (1 << UDRE)) );   // Wait until buffer is empty

		UDR = *Str;                     // Send the data to the TX buffer
		Str++;
	}
}
bool uart_full()
{
	return StigliPodaci;
}

void uart_clear()
{
	int b=0;
	for(b=0;b<100;b++)
	{
		Resive[b]='\0';
	}
	StigliPodaci=false;
	MozeZavrsetak=false;
	i=0;
}

ISR (USART_RXC_vect)
	{
	
		//if(StigliPodaci==false)
		//{
			StigliPodaci=false;
			
			Resive[i]=UDR;
			i++;
			
			if(i>99) i=99;
			
			MozeZavrsetak=true;
			TCNT1 =  0;
		//}
	
	
	
	
	}
	
	ISR(TIMER1_OVF_vect)		//Aktivira se svakih 2mS
	{
		TCNT1 =  0;
		
		if(MozeZavrsetak==true && StigliPodaci==false)
		{
			Resive[i]='\0';
			MozeZavrsetak=false;
			StigliPodaci=true;
			i=0;
		}
		
	}