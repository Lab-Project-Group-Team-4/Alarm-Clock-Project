/*
 * CPPFile2.cpp
 *
 * Created: 5/3/2021 1:34:22 PM
 *  Author: Saliya
 */ 
#ifndef F_CPU
#define  F_CPU 16000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>
#include "RTC.h"
#include <stdio.h>


int pos[5][2] = {{4, 0}, {7, 0}, {1, 1}, {4, 1}, {7, 1}};
char daysOfweek[][7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};



RTC::RTC(int b)
{
	int c = b;
	c = c/3;
}

void RTC::i2c_init()
{
    TWBR = 0xFF;
}

void RTC::i2c_start()
{
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while ((TWCR & (1<<TWINT)) == 0);
}

void RTC::i2c_stop()
{
    TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void RTC::i2c_write(unsigned char data)
{
    TWDR = data;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while ((TWCR & (1<<TWINT)) == 0);
}
unsigned char RTC::i2c_read()
{
    TWCR = (1 << TWINT) | (1 << TWEN)| (1 << TWEA);
    while ((TWCR & (1 << TWINT)) == 0);
    return TWDR;

}

unsigned char RTC::i2c_lastread()
{
	TWCR = (1 << TWINT) | (1 << TWEN);
	while ((TWCR & (1 << TWINT)) == 0);
	return TWDR;
	
}

unsigned char RTC::binTobcd(unsigned char data)
{
   
	/*char bcd;
	char n, dig, num, count;

	num = data;
	count = 0;
	bcd = 0;

	for (n = 0; n < 4; n++) {
		dig = num % 10;
		num = num / 10;
		bcd = (dig << count) | bcd;
		count += 4;
	}
	return bcd;*/
	return( (data/10*16) + (data%10) );
}

unsigned char RTC::bcdTobin(unsigned char data)
{
   /* char bin;
    bin = ((((data & (1<<7)) |(data & (1<<6)) |(data & (1<<5)) |(data & (1<<4))) * 0x0A) >> 4) + (data & (1<<3)) |(data & (1<<2)) |(data & (1<<1)) |(data & (1<<0));
	
	return bin;*/
    return( (data/16*10) + (data%16) );
}


void RTC::clock_init()
{
    i2c_start();
    i2c_write(RTC_WADDR);
	i2c_write(0x0E);
	i2c_write(0x20);
	i2c_write(0x08);
    i2c_stop();
	
}

void RTC::setTime(int sec, int min, int hour,int day, int mon,int wday, int year)
{
    i2c_start();
    i2c_write(RTC_WADDR);
    i2c_write(0x00);
    i2c_write(binTobcd(sec));
    i2c_write(binTobcd(min));
    i2c_write(binTobcd(hour));

	i2c_write(binTobcd(wday));
	i2c_write(binTobcd(day));
	i2c_write(binTobcd(mon));
	i2c_write(binTobcd(year));
	i2c_stop();
}

void RTC::ReadTime(int *sec, int *min, int *hour, int *day, int *wday, int *month, int *year)
{
    i2c_start();
    i2c_write(RTC_WADDR);
    i2c_write(0x00);
    i2c_stop();
	
    i2c_start();
    i2c_write(RTC_RADDR);
    *sec = bcdTobin(i2c_read());
    *min = bcdTobin(i2c_read());
    *hour = bcdTobin(i2c_read());

    *wday = bcdTobin(i2c_read());
    *day = bcdTobin(i2c_read());
    *month = bcdTobin(i2c_read());
    *year = bcdTobin(i2c_lastread());
    i2c_stop();

}

void RTC::init()
{
    i2c_init();
	clock_init();
}

void RTC::command(unsigned char cmd)
{
	port = (port & 0x0F)|(cmd & 0xF0);
	port &= ~(1<<rs);
	port |= (1<<en);
	//_delay_us(2);
	port &= ~(1<<en);
	//_delay_us(200);
	port = (port & 0x0F)|(cmd << 4);
	port |= (1<<en);
	//_delay_us(2);
	port &= ~(1<<en);
	_delay_us(50);
	
}

void RTC::lcd_init(void)
{
	direction = 0xFF;
	_delay_ms(2);
	
	command(0x02);
	command(0x28);
	command(0x0c);
	command(0x06);
	command(0x01);
	_delay_ms(2);
	
}
 void RTC::string(char *string_00)
 {
	 int i;
	 for ( i = 0; string_00[i]!=0;i++)
	 {
		 character(string_00[i]);
	 }
		 
 }
 void RTC::character(unsigned char data)
 {
	 port = (port & 0x0F)|(data & 0xF0);
	 port |= (1<<rs);
	 port |= (1<<en);
	 _delay_us(1);
	 port &= ~(1<<en);
	 //_delay_ms(200);
	 port = (port & 0x0F)|(data << 4);
	 
	 port |= (1<<en);
	 //_delay_us(1);
	 port &= ~(1<<en);
	 _delay_ms(2);
	 
 }
 
 void RTC::clear()
 {
	 command(0x01);
	 _delay_ms(2);
	 command(0x00);
 }
 
 void RTC::SetCursor(char row, char col)
 {
	 if (row == 0 && col<16){
		 command((col & 0x0F)|0x80);
	 }
	 else if(row == 1 && col <16) {
		 command((col & 0x0F)|0xC0);
	 }
 }
 
 void RTC::Blink()
 {
	 command(0x0F);
 }
  void RTC::NoBlink()
  {
	  command(0x0C);
  }

 // functions 
 void RTC::DisplayTime(int sec,int min,int hour, int day, int wday, int month, int year)
 {
	 char time[16];
	 char date[16];
	 sprintf(time,"%.2d:%.2d:%.2d\n",sec,min,hour);
	 sprintf(date,"%.2d/%.2d/%.2d",day,month,year);
	 string(time);
	 string("");
	 string(daysOfweek[wday]);
	 command(0xC0);
	 string(date);
 }
 
 void RTC::DisplayTimeBlink(int sec,int min,int hour, int day, int wday, int month, int year, int mode)
 {
	
	 //clear();
	 SetCursor(0,0);
	 char time[16];
	 char date[16];
	 sprintf(time,"%.2d:%.2d:%.2d",sec,min,hour);
	 sprintf(date,"%.2d/%.2d/%.2d",day,month,year);
	 string(time);
	 string(" ");
	 string(daysOfweek[wday]);
	 command(0xC0);
	 string(date);
	 int col = pos[mode][0];
	 int row = pos[mode][1];
	 SetCursor(row,col);
	 /*for (int i = 0; i<5; i++)
	 {
		 Blink();
		 _delay_ms(5);
		 NoBlink();
	 }*/
	Blink();
	_delay_ms(100);
	//NoBlink();

	 
	 //clear();
	 //_delay_us(1);
 }
 
 void RTC::alarmdisp(int min, int hour, int mode)
 {
	 //clear();
	 SetCursor(0,0);
	 string("HOUR:MIN        ");
	 SetCursor(1,0);
	 char time[16];
	 int col;
	 sprintf(time,"%.2d  :%.2d",hour,min);
	 string(time);
	 if (mode == 1){
		 col = 1; 
	 }
	 else{
		 col = 6;
	 }
	 SetCursor(1,col);

	Blink();
	//_delay_ms(100);
	//NoBlink();
}
 
 void RTC::slotdisp(int slot)
 {
	 //clear();
	 SetCursor(0,0);
	 string("SELECT SLOT        ");
	 SetCursor(1,0);
	 char slot_[16];
	 sprintf(slot_, "%d",slot);
	 string(slot_);
 }