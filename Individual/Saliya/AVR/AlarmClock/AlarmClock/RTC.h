/*
 * RTC.h
 *
 * Created: 4/25/2021 3:27:56 PM
 *  Author: Saliya
 */ 
#ifndef F_CPU
#define  F_CPU 1000000UL
#endif

#ifndef RTC_h
#define RTC_h
#include <avr/io.h>
#include <util/delay.h>

class RTC{
	public:
		RTC(int b);
		void command(unsigned char cmd);
		void init();
		void string(char *string_00);
		void character(unsigned char data_00);
		void clear();
		void SetCursor(char row, char col);
		void Blink();
		void NoBlink();
		void ds3231_init();
		void ReadTime(int *sec, int *min, int *hour, int *day, int *wday, int *month, int *year);
		
		void setTime(int sec, int min, int hour);
		void setTdate(int day, int month, int wday, int year);
		void DisplayTime(int sec,int min,int hour, int day, int wday, int month, int year);
		void DisplayTimeBlink(int sec,int min,int hour, int day, int wday, int month, int year, int mode);
		void alarmdisp(int min, int hour, int mode);
		void slotdisp(int slot);
	};

#endif