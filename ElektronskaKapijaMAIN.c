/*
 * BilbordTestAtmega32.c
 *
 * Created: 23.5.2017 13:59:24
 *  Author: Bozic
 */ 
float temp=0;

#define F_CPU 8000000UL
#include <avr/io.h>
#include "SIM_M590.h"
#include "StringConvert.h"
#include "Uartavr.h"
#include "LM35.h"
#include "MotoriKapije.h"


volatile bool SMSValid=false,RING=false;

enum Kapija Kapija1=Otvoreno;

volatile int M1ADC=250,M2ADC=250;

ISR(INT0_vect)
{
		RING=true;
}

int main(void)
{	
	PORTD |= (1 << 2);    // turn On the Pull-up
	MCUCR = 1<<ISC01 | 1<<ISC00;	// Trigger INT0 on falling edge// low lewel
	GICR = 1<<INT0;					// Enable INT0
	
	_delay_ms(100);
	DDRD&= ~(1<<0); //RX
	DDRD|= (1<<1); //TX
	DDRD&= ~(1<<2); //Ring
	
	M1_OFF1;
	M1_OFF2;
	M2_OFF1;
	M2_OFF2;
	DDRD|= (1<<7); //M1
	DDRC|= (1<<0); //M1
	DDRD|= (1<<6); //M2
	DDRD|= (1<<5); //M2
	
	DDRB&= ~(1<<1); // taster
	

	Uart_inic();

	uart_clear();

	SIM_Inic();


	SIM_delate_message();
	SIM_delate_message();
	
	uart_clear();
	
	clearNumANDMess();

	RING=false;
	
	sei();
		
    while(1)
    {
		if( (PINB & (1<<PINB1)) == 0)
		{
			RING=true;
			
			_delay_ms(20);
			while((PINB & (1<<PINB1)) == 0);
			_delay_ms(100);
		}
		
		if(ADCsingleREAD(3)>M2ADC)
		{
			M2_OFF1;
			M2_OFF2;
		}
		if(ADCsingleREAD(4)>M1ADC)
		{
			M1_OFF1;
			M1_OFF2;
		}
		
		if(RING)
		{
			if(SIM_ReciveSms())
			{
				
				if(Message[0]=='M' && Message[1]=='1')
				{
					int tmp=0;
					tmp+=(Message[2]-48)*100;
					tmp+=(Message[3]-48)*10;
					tmp+=(Message[4]-48);
					M1ADC=tmp;
				}
				if(Message[0]=='M' && Message[1]=='2')
				{
					int tmp=0;
					tmp+=(Message[2]-48)*100;
					tmp+=(Message[3]-48)*10;
					tmp+=(Message[4]-48);
					M2ADC=tmp;
				}
				if(Message[0]=='O' && Message[1]=='L')
				{
					OtvoriLevoKrilo();
				}
				if(Message[0]=='O' && Message[1]=='D')
				{
					OtvoriDesnoKrilo();
				}
				if(Message[0]=='O' && Message[1]=='T' && Message[2]=='V' && Message[3]=='O' && Message[4]=='R' && Message[5]=='I')
				{
					OtvoriKapiju();
				}
				if(Message[0]=='Z' && Message[1]=='A' && Message[2]=='T' && Message[3]=='V' && Message[4]=='O' && Message[5]=='R' && Message[6]=='I' )
				{
					ZatvoriKapiju();
				}
				
				RING=false;
				clearNumANDMess();
				uart_clear();
				SIM_delate_message();
				SIM_delate_message();
				
				
			}
			
			else
			{
				uart_clear();
				RING=false;
				if(Kapija1!=Otvoreno)
				{
					OtvoriKapiju();
				}
				else 
				{
					ZatvoriKapiju();
				}
				
			}
		}
				
	}	
		
}