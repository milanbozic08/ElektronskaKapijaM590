/*
 * Reley.h
 *
 * Created: 16.7.2017 14:35:26
 *  Author: Bozic
 */ 


#ifndef RELEY_H_
#define RELEY_H_

#define Rel1 1
#define Rel2 2
#define rel1OFF PORTA&=~(1<<Rel1)
#define rel2OFF PORTA&=~(1<<Rel2)
#define rel1ON PORTA|=(1<<Rel1)
#define rel2ON PORTA|=(1<<Rel2)

void REL_inic()
{
	PORTA&=~(1<<Rel1);
	PORTA&=~(1<<Rel2);
	DDRA |= (1<<Rel1);
	DDRA |= (1<<Rel2);
	
}

void REL_1ON ()
{
	rel1ON;
}	
void REL_1OFF ()
{
	rel1OFF;
}
void REL_2ON ()
{
	rel2ON;
}
void REL_2OFF ()
{
	rel2OFF;
}



#endif /* RELEY_H_ */