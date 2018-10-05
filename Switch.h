/*
 * Switch.h
 *
 * Created: 10.5.2017 22:20:25
 *  Author: Bozic
 */ 


#ifndef SWITCH_H_
#define SWITCH_H_

#define SW_DDR  DDRC
#define SW_PIN  PINC

void Switch_inic(uint8_t pin)
{
	SW_DDR &= ~(1<<pin);
}




#endif /* SWITCH_H_ */