/*
 * RTC.cpp
 *
 * Created: 4/25/2021 3:27:38 PM
 *  Author: Saliya
 */ 
#ifndef F_CPU
#define  F_CPU 1000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>

#include "RTC.h"
#include "rtc3231.h"
#include "i2c.h"


#define rs PB0
#define en PB1
#define direction DDRB
#define port PORTB
int pos[5][2] = {{4, 0}, {7, 0}, {1, 1}, {4, 1}, {7, 1}};

static uint8_t lcd_displayparams;

char daysOfweek[][7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};



RTC::RTC(int b)
{
	int c = b;
	c = c/3;
}

void RTC::command(unsigned char cmd)
{
	port = (port & 0x0F)|(cmd & 0xF0);
	port &= ~(1<<rs);
	port |= (1<<en);
	_delay_us(2);
	port &= ~(1<<en);
	//_delay_us(200);
	port = (port & 0x0F)|(cmd << 4);
	port |= (1<<en);
	//_delay_us(2);
	port &= ~(1<<en);
	//_delay_ms(2);
	
}

void RTC::init(void)
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
 

 
 void RTC::ds3231_init()
 {
	 i2c_init();
	 rtc3231_init();
	 
 }
 
void RTC::ReadTime(int *sec, int *min, int *hour, int *day, int *wday, int *month, int *year)
{
	struct rtc_time time;
	struct rtc_date date;
	rtc3231_read_datetime(&time,&date);
	*sec = time.sec;
	*min = time.min;
	*hour = time.hour;
	*day = date.day;
	*wday = date.wday;
	*month = date.month;
	*year = date.year;
		 
}

void RTC::setTime(int sec, int min, int hour)
{
	struct rtc_time newTime;
	newTime.sec = sec;
	newTime.min = min;
	newTime.hour = hour;
	rtc3231_write_time(&newTime);
}

void RTC::setTdate(int day, int month, int wday, int year)
{
	struct rtc_date newDate;
	newDate.day = day;
	newDate.month = month;
	newDate.wday = wday;
	newDate.year = year;
	rtc3231_write_date(&newDate);
}

 
