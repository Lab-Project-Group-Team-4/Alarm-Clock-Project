/*
 * AlarmTiming.cpp
 *
 * Created: 5/3/2021 1:33:23 PM
 * Author : Saliya
 */ 


#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "RTC.h"

#include <stdio.h>


RTC rtc(1);

int main()
{
	
	rtc.init();
	rtc.lcd_init();
	
	
	DDRB = 0b00000010;
	DDRD = 0b00000100;
	PORTB = 0b00011111;
	
	
	rtc.setTime(0,0,0,30,4,5,12);
	
	
	
	int IsEditingmode = 0;
	int modeStatus = 0;
	int isalarmeditingmode = 0;
	int alarmmode = 0;
	int alarm_min[5] = {0, 0, 0, 0, 0}; // variables for set the alarm
	int alarm_hour[5] = {0, 0, 0, 0, 0};//  variables for set the alarm
	int init_alarm[5] = {0, 0, 0, 0, 0};	
	int manual_stop[5] = {1, 1, 1, 1, 1};
	int alarmslot = 0;
	int select_slot = 0;
	int current_alarm;
	int isalarmblinking = 0;
	int var = 0;	
		


	
	
	while (1)
	{
		rtc.lcd_init();
		int sec, min, hour, day, wday, month, year;
		rtc.NoBlink();
		rtc.ReadTime(&sec,&min,&hour,&day,&wday,&month,&year);
		int modeButton = !(PINB & 0b00000001);
		int increment = !(PINB & 0b00000010);
		int decrement = !(PINB & 0b00000100);
		int setButton = !(PINB & 0b00001000);
		int alarmButton = !(PINB & 0b00010000);
		
		if (sec<=3 & min == 0 & hour == 0){
			    for (int slot = 0; slot < 5; slot++) {
				    manual_stop[slot] = 1;// renew alarms everyday
			    }
		}
		if (alarmButton == 1 & isalarmblinking == 0)// if there is not blinking alarm, alarm button is assigned to enter the alarm editing mode
		{ 
			isalarmeditingmode = 1;
			var = 0;
		}
		if (isalarmeditingmode == 1)
		{
			if (select_slot == 0)
			{
				if (var ==0)
				{
					rtc.clear();
					var = !var;
		    	}
				rtc.slotdisp(alarmslot);
				if(increment ==1)
				{
					alarmslot += 1;
					if (alarmslot>4)
					{
						alarmslot = 0;
					}
				}
				
				if (setButton ==1)//assigned set button to set the slot
				{
					select_slot = 1;//set the alarm slot and identify a alarm slot was selected
				}
			}
			
			else
			{
			 rtc.alarmdisp(alarm_min[alarmslot], alarm_hour[alarmslot], alarmmode);//display alarm editing mode
			
			if (modeButton ==1)// in the alarm editing mode, after selected the slot, the mode button assigned to change hour or min
			{
				alarmmode = !alarmmode;
			}
			if (increment ==1)
			{
				if (alarmmode ==0)
				{
					alarm_min[alarmslot] += 1;
					if (alarm_min[alarmslot] >59)
					{
						alarm_min[alarmslot] = 0;
					}
				}
				
				if (alarmmode == 1)
				{
					alarm_hour[alarmslot] += 1;
					if (alarm_hour[alarmslot] >23)
					{
						alarm_hour[alarmslot] = 0;
					}
				}
			}

			if (decrement ==1)
			{
				if (alarmmode ==0)
				{
					alarm_min[alarmslot] -= 1;
					if (alarm_min[alarmslot] <0)
					{
						alarm_min[alarmslot] = 59;
					}
				}
				
				if (alarmmode == 1)
				{
					alarm_hour[alarmslot] -= 1;
					if (alarm_hour[alarmslot] <0)
					{
						alarm_hour[alarmslot] = 23;
					}
				}
			}
			
			if (setButton == 1 )// if slot is selected, set button is assigned to set the current time as the alarm
			{
				isalarmeditingmode = 0;
				select_slot = 0;
				init_alarm[alarmslot] = 1;
				rtc.NoBlink();
				manual_stop[alarmslot] = 1;
			}
		}

			
		}
		else{//if not selected alarm editing mode
			for (int i =0; i<5;i++){
				if ((min == alarm_min[i]) & (hour == alarm_hour[i]) & (init_alarm[i] == 1) & (manual_stop[i] == 1)){
					current_alarm = i;
					isalarmblinking = 1;
					PORTD = (1 << PORTD2);
					_delay_ms(100);
					PORTD = 0;
					
				}
			}
			if ((alarmButton == 1) & (isalarmblinking == 1)){//manually stopping of current blinking alarm
				manual_stop[current_alarm] = 0;
				isalarmblinking = 0;
				_delay_ms(500);
			}
							
			if (modeButton == 1 & IsEditingmode == 0){
				IsEditingmode = 1;//time editing 
				//_delay_ms(50);
			}
		
			if (IsEditingmode ==1 & modeButton  == 1)
			{
				modeStatus += 1;
				if (modeStatus > 4)
				{
					modeStatus = 0;	
				}
			}
		
			if (increment == 1 & IsEditingmode ==1)
			{
				if(modeStatus == 0)
				{
					min += 1;
					if (min >=60){
						min = 0;
					}
				}
				if(modeStatus==1)
				{
					hour += 1;
					if (hour >=24){
						hour = 0;
					}

				}
				if(modeStatus==2)
				{
					day += 1;
					if (day >=32){
						day = 1;
					}
					wday += 1;
					if (wday >6){
						wday = 0;
					}

				}
				if(modeStatus==3)
				{
					month += 1;
					if (month >=13){
						month = 1;
					}

				}
				if(modeStatus==4)
				{
					year += 1;
					if (year >99){
						year = 0;
					}

				}
				rtc.setTime(sec,min,hour,day,month,wday,year);
				rtc.DisplayTimeBlink(sec, min, hour, day, wday, month,year,modeStatus);

			}
		
			if (decrement == 1 & IsEditingmode ==1)
			{
				if(modeStatus == 0)
				{
					min -= 1;
					if (min < 0){
						min = 59;
					}
				}
				if(modeStatus==1)
				{
					hour -= 1;
					if (hour <0){
						hour = 23;
					}

				}
				if(modeStatus==2)
				{
					day -= 1;
					if (day < 1){
						day = 31;
					}
					wday -= 1;
					if (wday <0){
						wday = 6;
					}

				}
				if(modeStatus==3)
				{
					month -= 1;
					if (month <0){
						month = 12;
					}

				}
				if(modeStatus==4)
				{
					year -= 1;
				
					if (year < 0){
						year = 99;
					}
							
				}
				rtc.setTime(sec,min,hour,day,month,wday,year);
				rtc.DisplayTimeBlink(sec, min, hour, day, wday, month,year,modeStatus);

			}
		
			if (setButton ==1 & IsEditingmode ==1)//if on time editing mode, set button is assigned to set the time
			{
				rtc.setTime(0,min,hour,day,month,wday,year);
				
				IsEditingmode = 0;
				//mode = 0;
				rtc.NoBlink();
			}
			if (IsEditingmode == 0)
			{
				rtc.ReadTime(&sec,&min,&hour,&day,&wday,&month,&year);
				rtc.DisplayTime(sec, min, hour, day, wday, month,year);
			}
			else{
				rtc.DisplayTimeBlink(sec, min, hour, day, wday, month,year,modeStatus);
			}
		
			
		}
		_delay_ms(500);
	}
	
	
}