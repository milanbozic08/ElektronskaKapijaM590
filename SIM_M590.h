/*
 * SIM_M590.h
 *
 * Created: 11.5.2017 21:36:49
 *  Author: Bozic
 */ 
#include "Uartavr.h"
#include <string.h>
#include <stdbool.h>

#define sms_end 0x1A
#define sim_reset 4 //D4
#define  simOff  PORTD&=~(1<<4)
#define  simOn  PORTD|=(1<<4)


#ifndef SIM_M590_H_
#define SIM_M590_H_

extern char Message[],Number[];


bool while_tmp=false,ok=false;
char Message[100],Number[100];//Resive[200],ResiveBack[200];
int StringLength=0;

//&Resive=Resivee();
//&ResiveBack=ResiveBackk();

void Parsiranje();

bool SIM_ON();


bool Sredi()
{	
	int t;
	
	for(int m=0;m<100;m++)
	{
		if(Resive[m]<32 && Resive[m]!='\0') 
			Resive[m]=34;
	}
	
	for(int m=0;m<100;m++)
	{
		if(Resive[m-1]==Resive[m] && Resive[m]=='"')
		{
			for(t=m;t<99;t++)
			Resive[t]=Resive[t+1];
			Resive[99]='\0';
			m=0;
		}
	}

	int Len=strlen(Resive);
	if(Resive[Len-2]=='K' && Resive[Len-3]=='O')
	{
		Parsiranje();
		return true;
	}
	
	return false;
}


void SIM_Inic()
{
	simOff;
	_delay_ms(100);
	DDRD|=(1<<4);
	_delay_ms(100);
	SIM_ON();
	
}

void clearNumANDMess()
{
	for(int i=0;i<=99;i++)
	{Message[i]='\0';
	Number[i]='\0';}
}

bool SIM_ON()
{	
	bool state_sim=false;
	_delay_ms(1000);
	
	simOn;
	_delay_ms(1500);
	uart_clear();
	while(!state_sim)
	{
		if(uart_full())
		{
			//uart_send_string(Resive);
			if(strcmp("\r\n+PBREADY\r\n",Resive)==0) 
			state_sim=true;
		}
	}
	return true;
}

void SIM_OFF()
{
	simOff;
}
void SIM_SendSms(char *Message,char *Number)
{
	
		char num[50]="AT+CMGS=\"";
		strcat(num,Number);
		strcat(num,"\"\r");
		
		
		uart_send_string("AT+CSCS=\"GSM\"\r");
		_delay_ms(2000);
		uart_send_string("AT+CMGF=1\r");
		_delay_ms(2000);
		
		uart_send_string(num);
		_delay_ms(1000);
		uart_send_string(Message);
		_delay_ms(20);
		UDR=sms_end;
		_delay_ms(1000);
}
bool SIM_ReciveSms()
{
	_delay_ms(200);
	uart_send_string("AT+CSCS=\"GSM\"\r");
	_delay_ms(200);
	uart_send_string("AT+CMGF=1\r");
	_delay_ms(200);
	
	uart_clear();
	
	uart_send_string("AT+CMGR=1\r");
	
	while(!uart_full());
	if(Sredi())
	{
		return true;
	}
	return false;
}

void SIM_delate_message()
{
	_delay_ms(500);
	uart_send_string("AT+CMGD=0\r");
	_delay_ms(500);
	uart_send_string("AT+CMGD=1\r");
	_delay_ms(500);
	uart_send_string("AT+CMGD=2\r");
	_delay_ms(500);
	uart_send_string("AT+CMGD=3\r");	
	_delay_ms(500);
	uart_send_string("AT+CMGD=4\r");
	_delay_ms(500);
}






void Parsiranje()
{
	int upper=0,num=1,txt=0;
	Number[0]='+';
	//AT+CMGR=1"+CMGR: "REC READ","+381649293159",","18/04/25,22:34:49+08"Text"OK"
	for(int g=0;g<100;g++)
	{
		if(upper==4 && Resive[g]!='"')
		{
			Number[num]=Resive[g];
			num++;
		}
		if(upper==4 && Resive[g]=='"')
		{
			Number[num]='\0';
		}
		
		if(upper==8 && Resive[g]!='"')
		{
			Message[txt]=Resive[g];
			txt++;
		}
		if(upper==8 && Resive[g]!='"')
		{
			Message[txt]='\0';
		}
		
		if(Resive[g]=='"')
		{
			upper++;
		}
		
	}
}


#endif /* SIM_M590_H_ */