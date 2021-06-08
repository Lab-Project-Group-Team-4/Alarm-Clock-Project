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
	
	
	DDRB = 0b00000000;
	DDRD = 0b00000100;
	PORTB = 0b00111111;
	
	
	rtc.setTime(0,0,0,1,1,4,21);
	
	
	
	int IsEditingmode = 0;
	int modeStatus = 0;
	int isalarmeditingmode = 0;
	int alarmmode = 0;
	int alarm_min[5] = {0, 0, 0, 0, 0}; // variables for set the alarm
	int alarmMin = 0;
	int alarmHour = 0;
	int alarm_hour[5] = {0, 0, 0, 0, 0};//  variables for set the alarm
	
	int alarm_date[5] = {0, 0, 0, 0, 0}; // variables for set the alarm
	int alarmDay = 0;
	int alarmMon = 0;
	int alarm_mon[5] = {0, 0, 0, 0, 0};//  variables for set the alarm
		
	int init_alarm[5] = {0, 0, 0, 0, 0};	
	int manual_stop[5] = {1, 1, 1, 1, 1};
	int alarmslot = 0;
	int select_slot = 0;
	int current_alarm;
	int isalarmblinking = 0;
	int var = 0;	
	int AlarmBack = 0;	


	
	
	while (1)
	{
		rtc.lcd_init();
		int sec, min, hour, day, wday, month, year;
		int sec1, min1, hour1, day1, wday1, month1, year1;
		rtc.NoBlink();
		//rtc.ReadTime(&sec,&min,&hour,&day,&wday,&month,&year);
		rtc.ReadTime(&sec1,&min1,&hour1,&day1,&wday1,&month1,&year1);
		int modeButton = !(PINB & 0b00000001);
		int increment = !(PINB & 0b00000010);
		int decrement = !(PINB & 0b00000100);
		int setButton = !(PINB & 0b00001000);
		int alarmButton = !(PINB & 0b00010000);
		int backButton = !(PINB & 0b00100000);
		if (sec<=3 & min == 0 & hour == 0){
			    for (int slot = 0; slot < 5; slot++) {
				    manual_stop[slot] = 1;// renew alarms everyday
			    }
		}
		if (alarmButton == 1 & isalarmblinking == 0 & isalarmeditingmode == 0 & AlarmBack == 0)// if there is not blinking alarm, alarm button is assigned to enter the alarm editing mode
		{ 
			isalarmeditingmode = 1;
			//AlarmBack = 1;
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
				
				if (setButton ==1)// set button to set the slot
				{
					select_slot = 1;//set the alarm slot and identify a alarm slot was selected
					alarmMin = alarm_min[alarmslot];
					alarmHour =  alarm_hour[alarmslot];
					alarmDay = alarm_date[alarmslot];
					alarmMon = alarm_mon[alarmslot];
					//_delay_ms(1000);
				
					
				}

			}
			
			else
			{
				
				rtc.alarmdisp(alarmMin, alarmHour, alarmDay, alarmMon, alarmmode);//display alarm editing mode
				
			
			if (modeButton ==1)// in the alarm editing mode, after selected the slot, the mode button assigned to change hour or min
			{
				alarmmode += 1;
				if (alarmmode >3)
				{
					alarmmode = 0;
				}
				
			}
			if (increment ==1)
			{
				if (alarmmode ==0)
				{
					alarmMin += 1;
					if (alarmMin >59)
					{
						alarmMin = 0;
					}
				}
				
				if (alarmmode == 1)
				{
					alarmHour += 1;
					if (alarmHour >23)
					{
						alarmHour = 0;
					}
				}
				
				if (alarmmode ==2)
				{
					alarmDay += 1;
					if (alarmDay >31)
					{
						alarmDay = 1;
					}
				}
								
				if (alarmmode == 3)
				{
					alarmMon += 1;
					if (alarmMon >12)
					{
						alarmMon = 1;
					}
				}

			}

			if (decrement ==1)
			{
				if (alarmmode ==0)
				{
					alarmMin -= 1;
					if (alarmMin <0)
					{
						alarmMin = 59;
					}
				}
				
				if (alarmmode == 1)
				{
					alarmHour -= 1;
					if (alarmHour <0)
					{
						alarmHour = 23;
					}
				}
				if (alarmmode == 2)
				{
					alarmDay -= 1;
					if (alarmDay <1)
					{
						alarmDay = 31;
					}
				}
				
				if (alarmmode == 3)
				{
					alarmMon -= 1;
					if (alarmMon <1)
					{
						alarmMon = 12;
					}
				}

			}
		
			if (setButton == 1 )// if slot is selected, set button is assigned to set the current time as the alarm
			{
				alarm_min[alarmslot] = alarmMin;
				alarm_hour[alarmslot] = alarmHour;
				alarm_date[alarmslot] = alarmDay;
				alarm_mon[alarmslot] = alarmMon;
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
				if ((min1 == alarm_min[i]) & (hour1 == alarm_hour[i])  &(day1 == alarm_date[i]) & (month1 == alarm_mon[i]) & (init_alarm[i] == 1) & (manual_stop[i] == 1)){
					current_alarm = i;
					isalarmblinking = 1;
					PORTD = 0b00000100;
					_delay_ms(100);
					PORTD = 0;
					
				}
			}
			if ((alarmButton == 1) & (isalarmblinking == 1)){//manually stopping of current blinking alarm
				manual_stop[current_alarm] = 0;
				init_alarm[current_alarm] = 0;
				isalarmblinking = 0;
				_delay_ms(500);
			}
							
			if (modeButton == 1 & IsEditingmode == 0){
				IsEditingmode = 1;//time editing 
				sec = sec1; min = min1 ;day = day1;wday = wday1;month = month1;hour = hour1;year = year1;
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
				//rtc.setTime(sec,min,hour,day,month,wday,year);
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
				//rtc.setTime(sec,min,hour,day,month,wday,year);
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
				rtc.ReadTime(&sec1,&min1,&hour1,&day1,&wday1,&month1,&year1);
				rtc.DisplayTime(sec1, min1, hour1, day1, wday1, month1,year1);
			}
			else{
				rtc.DisplayTimeBlink(sec, min, hour, day, wday, month,year,modeStatus);
			}
		
			
		}
		
		if (backButton == 1)
		{
			IsEditingmode = 0;
			isalarmeditingmode = 0;
			select_slot = 0;
		}
		
		_delay_ms(200);
	}
	
	
}