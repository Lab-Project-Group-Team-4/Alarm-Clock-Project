/*
 * Alarm_Keypad.c
 *
 * Created: 5/19/2021 10:41:23 AM
 * Author : USER
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "keypad.h"

int main(void)
{
	DDRD = 0XFF;
	char KeyVal= 0;
	while (1)
	{
		KeyVal = keyfind();
		PORTD = KeyVal;
		_delay_ms(100);
		PORTD = 0;
	}
}
