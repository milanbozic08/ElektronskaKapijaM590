/*
 * MotoriKapije.h
 *
 * Created: 27/09/2018 11:05:23
 *  Author: Bozic
 */ 
#define M1_ON1 PORTD |=(1<<7)
#define M1_ON2 PORTC |=(1<<0)
#define M1_OFF1 PORTD &=~(1<<7)
#define M1_OFF2 PORTC &=~(1<<0)

#define M2_ON1 PORTD |=(1<<5)
#define M2_ON2 PORTD |=(1<<6)
#define M2_OFF1 PORTD &=~(1<<5)
#define M2_OFF2 PORTD &=~(1<<6)

#ifndef MOTORIKAPIJE_H_
#define MOTORIKAPIJE_H_

extern bool TrenutnoStanje;

enum Kapija {Otvoreno,Zatvoreno,OtvLevo,OtvDesno};
	
extern enum Kapija Kapija1;


void OtvoriLevo()
{
	M1_ON1;
	M1_OFF2;
}
void OtvoriDesno()
{
	M2_ON1;
	M2_OFF2;
}
void ZatvoriLevo()
{
	M1_OFF1;
	M1_ON2;
}
void ZatvoriDesno()
{
	M2_OFF1;
	M2_ON2;
}

void OtvoriKapiju()
{
	if(Kapija1==Zatvoreno)
	{
		OtvoriLevo();
		OtvoriDesno();
		Kapija1=Otvoreno;
		_delay_ms(500);
	}	
	if(Kapija1==OtvLevo)
	{
		OtvoriDesno();
		Kapija1=Otvoreno;
		_delay_ms(500);
	}
	if(Kapija1==OtvDesno)
	{
		OtvoriLevo();
		Kapija1=Otvoreno;
		_delay_ms(500);
	}
}
void ZatvoriKapiju()
{
	if(Kapija1==Otvoreno)
	{
		ZatvoriLevo();
		ZatvoriDesno();
		Kapija1=Zatvoreno;
		_delay_ms(500);
	}
	if(Kapija1==OtvLevo)
	{
		ZatvoriLevo();
		Kapija1=Zatvoreno;
		_delay_ms(500);
	}
	if(Kapija1==OtvDesno)
	{
		ZatvoriDesno();
		Kapija1=Zatvoreno;
		_delay_ms(500);
	}
}

void OtvoriLevoKrilo()
{
	if(Kapija1==Otvoreno)
	{
		ZatvoriDesno();
		Kapija1=OtvLevo;
		_delay_ms(500);
	}
	if(Kapija1==Zatvoreno)
	{
		OtvoriLevo();
		Kapija1=OtvLevo;
		_delay_ms(500);
	}
	if(Kapija1==OtvDesno)
	{
		ZatvoriDesno();
		OtvoriLevo();
		Kapija1=OtvLevo;
		_delay_ms(500);
	}
}

void OtvoriDesnoKrilo()
{
	if(Kapija1==Otvoreno)
	{
		ZatvoriLevo();
		Kapija1=OtvDesno;
		_delay_ms(500);
	}
	if(Kapija1==Zatvoreno)
	{
		OtvoriDesno();
		Kapija1=OtvDesno;
		_delay_ms(500);
	}
	if(Kapija1==OtvLevo)
	{
		ZatvoriLevo();
		OtvoriDesno();
		Kapija1=OtvDesno;
		_delay_ms(500);
	}
}




#endif /* MOTORIKAPIJE_H_ */