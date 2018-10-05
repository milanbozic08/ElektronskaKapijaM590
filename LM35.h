/*
 * LM35.h
 *
 * Created: 10.5.2017 20:01:34
 *  Author: Bozic
 */ 


#ifndef LM35_H_
#define LM35_H_

int ADCsingleREAD(uint8_t adctouse) //adctouse koji pin treba da se obradi
{
	int ADCval;

	ADMUX = adctouse;         // use #5 ADC
	ADMUX |= (1 << REFS0);    // use AVcc as the reference
	ADMUX &= ~(1 << ADLAR);   // clear for 10 bit resolution
	
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);    // 128 prescale brzina konverzije
	ADCSRA |= (1 << ADEN);    // Enable the ADC

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion

	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish


	ADCval = ADCL;
	ADCval = (ADCH << 8) + ADCval;    // ADCH is read so ADC can be updated again

	return ADCval;
}

uint16_t ReadADC(uint8_t ch)
{
	//Select ADC Channel ch must be 0-7
	ch=ch&0b00000111;
	ADMUX|=ch;

	//Start Single conversion
	ADCSRA|=(1<<ADSC);

	//Wait for conversion to complete
	while(!(ADCSRA & (1<<ADIF)));

	//Clear ADIF by writing one to it
	ADCSRA|=(1<<ADIF);

	return(ADC);
}

void InitADC()
{
	ADMUX=(1<<REFS0);                         // For Aref=AVcc;
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //Rrescalar div factor =128
}


void LM35_init(uint8_t SensorPin)
{
	DDRA&=~(1<<SensorPin);
}
double LM35_Temp(uint8_t SensorPin)
{
	int AdcVrednost=ADCsingleREAD(SensorPin);
	//AdcVrednost=AdcVrednost-153;
	//double temp=(((float)AdcVrednost)*0.048828125);
	double tmp=((AdcVrednost*0.483398)-273.15);
	return tmp;
}


#endif /* LM35_H_ */