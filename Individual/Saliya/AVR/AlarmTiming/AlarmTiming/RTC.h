/*
 * CPPFile2.cpp
 *
 * Created: 5/3/2021 1:34:40 PM
 *  Author: Saliya
 */ 

#ifndef F_CPU
#define  F_CPU 16000000UL
#endif

#ifndef RTC_h
#define RTC_h
#include <avr/io.h>
#include <util/delay.h>

class RTC{
	public:
	#define RTC_WADDR 0b11010000
	#define RTC_RADDR 0b11010001
	#define rs PB0
	#define en PB1
	#define direction DDRD
	#define port PORTD
	RTC(int b);
	void init();
	void i2c_init();
	void i2c_start();
	void i2c_stop();
	void i2c_write(uint8_t data);
	unsigned char i2c_read();
	unsigned char i2c_lastread();
	unsigned char binTobcd(unsigned char data);
	unsigned char bcdTobin(unsigned char data);
	void clock_init();
	void command(unsigned char cmd);
	void lcd_init();
	void string(char *string_00);
	void character(unsigned char data_00);
	void clear();
	void SetCursor(char row, char col);
	void Blink();
	void NoBlink();
	void ReadTime(int *sec, int *min, int *hour, int *day, int *wday, int *month, int *year);
	void setTime(int sec, int min, int hour,int day, int mon,int wday, int year);
	void setDate(int day, int mon,int wday, int year);
	void DisplayTime(int sec,int min,int hour, int day, int wday, int month, int year);
	void DisplayTimeBlink(int sec,int min,int hour, int day, int wday, int month, int year, int mode);
	void alarmdisp(int min, int hour, int mode);
	void slotdisp(int slot);
};

#endif