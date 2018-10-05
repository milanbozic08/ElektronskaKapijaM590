/*
 * StringConvert.h
 *
 * Created: 10.5.2017 21:13:41
 *  Author: Bozic
 */ 


#ifndef STRINGCONVERT_H_
#define STRINGCONVERT_H_

extern char numberstring[];

#define SIZE 100
char numberstring[SIZE];

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


char* Conv_FloatToChar(float Number,int beforeDot,int afterDot)
{
	
	
	int Zaokruzeno=(int)Number,CeoDeo,RazlomljeniDeo;
	
	if(Zaokruzeno>Number) CeoDeo=Zaokruzeno-1;
	else CeoDeo=Zaokruzeno;
	
	RazlomljeniDeo=(int)((Number-(float)CeoDeo)*100);	
	
	if(RazlomljeniDeo>((Number-(float)CeoDeo)*100)) RazlomljeniDeo--;
	
	
	
	
	/*sprintf(Broj_char,"%d",CeoDeo);
	Broj_char[2]=',';
	sprintf(&Broj_char[3],"%d",RazlomljeniDeo);
	Broj_char[5]='\0';*/
	return NULL;
}
char* convert2string(double number, int decimal_size){
	int i=0;
	/*int i=0;
	for (i=0; i < SIZE; i++)
	numberstring[i] = '\0'; */
	numberstring[100]='\0';
	int digits = 0;
	int numberinteger = (int) number;
	while(numberinteger != 0){
		numberinteger /= 10;
		digits ++;
	}
	if (digits + decimal_size > SIZE){
		//ako je broj veci od celog niza
	}
	numberinteger = (int) number;

	i = 0;
	while(i<digits){
		int j = numberinteger % 10;
		numberstring[digits-i-1] = j + '0';
		numberinteger /= 10;
		i++;
	}
	numberinteger = (int) number;
	number -= numberinteger;
	numberinteger = number * pow(10,decimal_size);
	numberinteger++; numberstring[digits]=',';
	i = 0;


	while(i<decimal_size){
		int j = numberinteger % 10;
		numberstring[decimal_size-i+digits] = j + '0';
		numberinteger /= 10;
		i++;
	}
	numberstring[SIZE - 1] = '\0';
	return numberstring;
}


#endif /* STRINGCONVERT_H_ */