/*
 * zAVR.c
 *
 * Created: 5/13/2021 10:55:58 AM
 * Author : USER
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define HOURS 0
#define MINUTES 1
#define SECONDS 2

#include "button.h"
#include "lcd.h"
#include "clock.h"

int alarmArray[4][3] = {0};

int clockHours = 0;
int clockMinutes = 0;
int clockSeconds = 0;

int tempHours = 0;
int tempMinutes = 0;
int tempSeconds = 0;

typedef enum {false, true} bool;

bool tick = true;
bool toDisplay = false;
bool clockReset = false;
bool alarmReset = false;
bool alarmState[4] = {false, false, false, false};

int button;
int position = 0;
int alarmNo = -1;

int Directory[3] = {0, 0, 0};
char timeString[9];
char alarmString[9];
char temp[3];
char toneString[2];
char resetConfirm[2];
char alarmMenu[2] = {'1'};
char upperAlarm[17];
char lowerAlarm[17];
char alarmChange[2];

int tone = 0;
int alarmSelection = 1;

void tickClock(int* hours, int* minutes, int* seconds);
void updateTime(int* hours, int* minutes, int* seconds, int pos, int updateValue);
void viewAlarms(void);

int main(void)
{
	
	initializeLCD();
	initializeKeyPress();
    /* Replace with your application code */

	
    while (1) 
    {
		button = keyPressed();
		
		if (tick) tickClock(&clockHours, &clockMinutes, &clockSeconds);
		 
		switch(Directory[0]){
			
			case 0:
			
				if (tick || toDisplay){
				clearDisplay();
				sprintf(timeString, "%02d:%02d:%02d", clockHours, clockMinutes, clockSeconds);
				sendString_XY(0,2,"CURRENT TIME");
				sendString_XY(1,4, timeString);
				tick = false;
				toDisplay = false;
				}
				
				if (button == 2) { 
					Directory[0] = 1;
					toDisplay = true;
				}
				
				break;
			
			case 1:
				
				switch(Directory[1]){
					
					case 0:
						if (toDisplay){
						clearDisplay();
						sendString_XY(0,4,"SETTINGS");
						sendString_XY(1,0, "1.EDIT TIME");
						toDisplay = false;
						}
						
						if (button == 1) {
							Directory[1] = 1;
							clearDisplay();
							sendString_XY(0,4,"HH:MM:SS");
							sendString_XY(1,4, timeString);
						}
						
						else if (button == 2) {
							Directory[0] = 2;
							toDisplay = true;
						}
						else if (button == 3) {
							Directory[0] = 0;
							toDisplay = true;
						}
						
						break;
						
					case 1:
					
					
						if (button == 1) {
							if (position == 2) {
								Directory[1] = 0;
								position = 0;
							}
							else position++;
						}
							
						else if (button == 2) {
							updateTime(&clockHours, &clockMinutes, &clockSeconds, position, -1);
							sprintf(timeString, "%02d:%02d:%02d", clockHours, clockMinutes, clockSeconds); // temp position
						}
						else if (button == 3) {
							updateTime(&clockHours, &clockMinutes, &clockSeconds, position, +1);
							sprintf(timeString, "%02d:%02d:%02d", clockHours, clockMinutes, clockSeconds); // temp position
						}
						else if (button == 4) {
							Directory[1] = 0;
							position = 0;
							toDisplay = true;
						} 
						
						//temp[0] = timeString[position+position/2];
						sendString_XY(1,4+(position*3),"__");
						temp[0] = timeString[position*3];
						temp[1] = timeString[position*3 + 1];
						sendString_XY(1,4+(position*3),temp);// note working this section
						break;
						
					default:
						break;
				
				}
				break;
				
			case 2:
				switch(Directory[1]){
					case 0:
						if (toDisplay){
							clearDisplay();
							sendString_XY(0,4,"SETTINGS");
							sendString_XY(1,0, "2.ALARM SETTINGS");
							toDisplay = false;
						}
						
						if (button == 1){
							Directory[1] = 1;
							clearDisplay();
							toDisplay = true;
						}
						
						else if (button == 2) {
							Directory[0] = 3;
							toDisplay = true;
						}
						else if (button == 3) {
							Directory[0] = 1;
							toDisplay = true;
						}
						break;
					
					case 1:
						switch(Directory[2]){
							case 0:
							
								if(toDisplay){
									sendString_XY(0,0,"1:VIEW 2:CLR");
									sendString_XY(1,0,"3.CHNG ENTER:");
									sendString_XY(1,13,alarmMenu);
									toDisplay = false;									
								}
							
								if (button == 1){
									if (alarmSelection == 1) Directory[2] = 1;
									else if (alarmSelection == 2) Directory[2] = 2;
									else if (alarmSelection == 3) Directory[2] = 3;
									clearDisplay();
									toDisplay = true;
								}
								
								else if (button == 2){
									alarmSelection -= 1;
									if (alarmSelection<1) alarmSelection = 1;
									sprintf(alarmMenu,"%d",alarmSelection);
									sendString_XY(1,13,alarmMenu);
								}
								
								else if (button == 3){
									alarmSelection += 1;
									if (alarmSelection>3) alarmSelection = 3;
									sprintf(alarmMenu,"%d",alarmSelection);
									sendString_XY(1,13,alarmMenu);
									
								}
								
								else if (button == 4){
									toDisplay = true;
									Directory[1]=0;
								}
								
								break;
								
							case 1:
								if (toDisplay){
									viewAlarms();
									toDisplay = false;
								}
								
								if (button==4) {
									Directory[2]=0;
								}
								break;
								
							case 2:
								if (toDisplay){
									clearDisplay();
									sendString_XY(0,0,"ENTER ALARM:");
									toDisplay = false;
								}
								
								if ((button == 1) && (alarmNo>= 0)){
										alarmState[alarmNo] = false;
										alarmNo = -1;
										clearDisplay();
										sendString_XY(0,0,"ALARM CLEARED");
										_delay_ms(100);
										Directory[2] = 0;
										toDisplay = true;
										clearDisplay();
									}
									
								else if (button == 2){
									alarmNo -=1;
									if (alarmNo<0) alarmNo = 0;
									sprintf(alarmMenu,"%d", alarmNo+1);
									sendString_XY(0,12,alarmMenu);
								}
								else if (button == 3){
									alarmNo +=1;
									if (alarmNo>3) alarmNo = 3;									
									sprintf(alarmMenu, "%d", alarmNo+1);
									sendString_XY(0,12,alarmMenu);
								}
								else if (button == 4){
									clearDisplay();
									toDisplay = true;
									Directory[2] = 0;
									alarmMenu[0] = '1';
								}
								
								break;
								
							case 3://Hard part
								if (toDisplay){
									clearDisplay();
									sendString_XY(0,0,"ENTER ALARM:");
									toDisplay = false;
									alarmNo = 0;
								}
								
								if (button == 1){
									if (alarmReset){
										if (position == 1) {
											alarmState[alarmNo] = true;
											alarmArray[alarmNo][0] = tempHours;
											alarmArray[alarmNo][1] = tempMinutes;
											alarmReset = false;
											clearDisplay();
											sendString_XY(0,0,"ALARM CHANGED");
											_delay_ms(100);
											toDisplay = true;
											clearDisplay();
											position = 0;
											tempHours = 0;
											tempMinutes = 0;
											tempSeconds = 0;	
											Directory[2] = 0;																					
										}
										
										else {
											position ++;
										}
									}
									
									else{
										alarmReset = true;
										sprintf(alarmString, "%02d:%02d", tempHours, tempMinutes);
										sendString_XY(1,4,alarmString);
									}
								}
								
								else if (button == 2){
									if (alarmReset){
										updateTime(&tempHours, &tempMinutes, &tempSeconds, position, -1);
										sprintf(alarmString, "%02d:%02d", tempHours, tempMinutes);	
																		
									}
									else{
										alarmNo -=1;
										if (alarmNo<0) alarmNo = 0;
										sprintf(alarmChange,"%d", alarmNo+1);
										sendString_XY(0,12,alarmChange);
									}
								}
								
								else if (button == 3){
									if (alarmReset){
										updateTime(&tempHours, &tempMinutes, &tempSeconds, position, +1);
										sprintf(alarmString, "%02d:%02d", tempHours, tempMinutes);	
									}
									else{
										alarmNo +=1;
										alarmNo %=4;
										sprintf(alarmChange,"%d", alarmNo+1);
										sendString_XY(0,12,alarmChange);
									}
								}
								
								else if (button == 4){
									Directory[2] = 0;
									position = 0;
									toDisplay = true;
								}						
							
								sendString_XY(1,4+(position*3),"__");
								temp[0] = alarmString[position*3];
								temp[1] = alarmString[position*3 + 1];
								sendString_XY(1,4+(position*3),temp);// note working this section
							
							
							default:
								break;
						
						}
						
						
						break;
						
					default:
						break;
						
						
					
					
				}//end of default[1] switch
				
				break;
			
			case 3:
				switch(Directory[1]){
					case 0: 
						if (toDisplay){
							clearDisplay();
							sendString_XY(0,4,"SETTINGS");
							sendString_XY(1,0, "3.TONE SETTINGS");
							toDisplay = false;
						}
						
						if (button == 1){
							Directory[1] = 1;
							clearDisplay();
							sendString_XY(0,0,"ENTER TONE:");
							sprintf(toneString, "%d", tone+1);
							sendString_XY(1,0,toneString);
						}
						
						else if (button == 2) {
							Directory[0] = 4;
							toDisplay = true;
						}
						
						else if (button == 3) {
							Directory[0] = 2;
							toDisplay = true;
						}
						
						break;
					
					case 1:
						if (button == 1){
							clearDisplay();
							sendString_XY(0,1,"TONE CHANGED");
							_delay_ms(100);
							toDisplay = true;
							Directory[1] = 0;
							
						}
						
						else if (button == 2){
							tone -= 1;
							if (tone == -1) tone = 0;
							sprintf(toneString, "%d", tone+1);
							sendString_XY(1,0,toneString);
							
						}
						
						else if (button == 3){
							tone += 1;
							tone %= 2;
							sprintf(toneString, "%d", tone+1);
							sendString_XY(1,0,toneString);
						}
						break;
					
					default:
						break;
				}
				
				break;
				
			case 4:
				switch(Directory[1]){
					case 0:
						if (toDisplay){
							clearDisplay();
							sendString_XY(0,4,"SETTINGS");
							sendString_XY(1,0, "4.FACTORY RESET");
							toDisplay = false;
						}
						
						if (button == 1){
							Directory[1] = 1;
							clearDisplay();
							sendString_XY(0,0,"CONFIRM:");
							
						}
						
						else if (button == 3) {
							Directory[0] = 3;
							toDisplay = true;
						}
						break;
					
					case 1:
						if (button == 1){
							
							if (clockReset) {
							clearDisplay();
							sendString_XY(0,0,"RESET SUCCESSFUL");
							_delay_ms(100);
							toDisplay = true;
							Directory[1] = 0;
							}
							
							else if (!clockReset) {
							clearDisplay();
							sendString_XY(0,0,"CANCELLED");
							_delay_ms(100);
							toDisplay = true;
							Directory[1] = 0;								
							}
						}
						
						else if (button == 2){
							sendString_XY(1,0,"Y");
							clockReset = true;
						}
						else if (button == 3){
							sendString_XY(1,0,"N");
							clockReset = false;
						}
							
						break;
						
						
						
					default:
						break;
				
				}
				
			default:
				break;

		}//end of directory[0] switch;
		
		_delay_ms(200);
    }
}


//Supportive functions
void updateTime(int* hours, int* minutes, int* seconds, int pos, int updateValue){
	
	if (updateValue == 1){
		if (pos == 0) {
			*hours += 1;
			*hours %= 24;
		}
		
		else if (pos == 1){
			*minutes += 1;
			*minutes %= 60;
		}
		
		else if (pos == 2){
			*seconds += 1;
			*seconds %= 60;
		}
		
	}
	
	else if (updateValue == -1){
		if (pos == 0){
			*hours -=1;
			if (*hours == -1) *hours = 23;
		}
		
		else if (pos == 1){
			*minutes -= 1;
			if (*minutes == -1) *minutes = 59;
		}
		
		else if ( pos == 2){
			*seconds -= 1;
			if (*seconds == -1) *seconds = 59;
		}
		
	}
	
	
	
	
	/*
	
	if ( pos == 4) updateValue *= 10;
	else if ( pos == 3) updateValue *=60;
	else if ( pos == 2) updateValue *=600;
	else if ( pos == 1) updateValue *=3600;
	else if ( pos == 0) updateValue *=36000;
	long  total = *hours * 3600L + *minutes * 60L + *seconds + updateValue;
	
	if (total<0)		  total = total + 3600L*24L;
	if (total> (3600L*24L)) total = total - 3600L*24L;
	*seconds = total%60;
	*minutes = ((total-*seconds)/60)%60;
	*hours   = ((total - *minutes * 60 - *seconds)/60)%24;
	*/

}



void tickClock(int* hours, int* minutes, int* seconds){
	*seconds += 1;
	*minutes += *seconds/60;
	*seconds %=60;
	*hours += *minutes/60;
	*minutes %= 60;
	*hours %=24;
}


void viewAlarms(void){
	sprintf(upperAlarm,"1)%02d:%02d  2)%02d:%02d ",alarmArray[0][0], alarmArray[0][1],alarmArray[1][0], alarmArray[1][1]);
	sprintf(lowerAlarm,"3)%02d:%02d  4)%02d:%02d ",alarmArray[2][0], alarmArray[2][1],alarmArray[3][0], alarmArray[3][1]);
	sendString_XY(0,0,upperAlarm);
	sendString_XY(1,0,lowerAlarm);
	for (int j = 0; j<4; j++){
		if (alarmState[j] == false){
			sendString_XY(j/2, 8*(j%2)+(j%2)+2," OFF ");
		}
	}
}






/*		j++;
i++;
itoa(j, val, 10);
sendCharacter(i);
sendString_XY(1,0,val);
_delay_ms(100);

clearDisplay();*/