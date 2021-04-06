#include "DSRTC.h"

Set_LCD LCD(1, 2, 4, 5, 6, 7);


int mode_status = 0; // variable for set mode to editing mode
int alarm_min[5] = {100, 100, 100, 100, 100}; // variables for set the alarm
int alarm_hour[5] = {100, 100, 100, 100, 100};//  variables for set the alarm
int manual_stop[5] = {1,1,1,1,1};
int current_alarm;
int isalarmblinking = 0;
int alarm_mode = 0;// set the mode to alarm setting mode
int alarm_time = 0;// variable for set the alrm editing feature to min or hours
int alarm_stop = 0;//differentiate set button function according to the current mode 
int alarm_slot = 0;// slot among 5 slots
int alarm_select = 0;// editing alrm

int IsEditingMode = 0;// variable for check the mode


void setup() {
  Set_LCD LCD(1, 2, 4, 5, 6, 7);
  DS3232Begin();
  setTime(0, 1, 0, 4, 7, 4, 21);
  pinMode(8, INPUT); pinMode(9, INPUT); pinMode(10, INPUT); pinMode(11, INPUT);

}

void loop() {

  byte seconds, minutes, hours, dayofweek, day, month, year;
  readTime(&seconds, &minutes, &hours, &dayofweek, &day, &month, &year );

  /////////////////////////////////////////////////////////////
  bool mode = digitalRead(8);               //// button inputs
  bool increment = digitalRead(9);
  bool decrement = digitalRead(10);
  bool set_button = digitalRead(11);
  bool alarm_button = digitalRead(12);
  /////////////////////////////////////////////////////////////
  //add mode button, this button chose the editing variable, minutes,ours or etc.
  ///////////////////////////////////////////////////////////////
  if (minutes == 0 and hours == 0){
    for (int slot=0;slot <5;slot++){
      manual_stop[slot] = 1;// renew alarms everyday
    }
  }
  if (alarm_button == 1 and isalarmblinking == 0) { //enter alarm set process
    alarm_mode = 1;
    alarm_stop = 1;
  }
  if (alarm_mode == 1) {

    if (alarm_select == 0) {//select the alarm slot among 5 slots

      //LCD.clear_all();
      slot_disp(LCD, alarm_slot);
      if (increment == HIGH and alarm_select == 0) {

        alarm_slot += 1;
        if (alarm_slot > 4) {
          alarm_slot = 0;
        }

      }
      if (set_button == 1 and alarm_select == 0) {
        alarm_select = not alarm_select;
      }
    }

    else {
      LCD.clear_all();
      alarm_disp(LCD, alarm_min[alarm_slot], alarm_hour[alarm_slot]);

      if (mode == HIGH) {//edit the chosen time slot
        alarm_time = not alarm_time;
      }

      if (increment == HIGH) {
        if (alarm_time == 0) {
          alarm_min[alarm_slot] += 1;
          if (alarm_min[alarm_slot] > 59) {//incrementing minutes for alarm
            alarm_min[alarm_slot] = 0;
          }
        }
        if (alarm_time == 1) {
          alarm_hour[alarm_slot] += 1;
          if (alarm_hour[alarm_slot] > 23) {//incrementing hour for alarm
            alarm_hour[alarm_slot] = 0;
          }
        }
      }

      if (decrement == HIGH) {
        if (alarm_time == 0) {
          alarm_min[alarm_slot] -= 1;
          if (alarm_min[alarm_slot] < 0) {//decrementing minutes for alarm
            alarm_min[alarm_slot] = 59;
          }
        }
        if (alarm_time == 1) {
          alarm_hour[alarm_slot] -= 1;
          if (alarm_hour[alarm_slot] < 0) {//decrementing hour for alarm
            alarm_hour[alarm_slot] = 23;
          }
        }
      }

      if (set_button == 1 and alarm_stop == 1) {  //set the selected alarm slot to the value which is chosen
        alarm_mode = 0;
        alarm_stop = 0;
        LCD.clear_all();
        alarm_select = not alarm_select;
        manual_stop[alarm_slot] = 1;
      }
      delay(300);
    }
  }
  //////////////////////////////////////////////////////////////////////

  else {

    for (int slot = 0; slot < 5; slot++) {

      if (alarm_min[slot] == minutes and alarm_hour[slot] == hours and manual_stop[slot] == 1 ) {// blinking the LED when alarm time come up
        current_alarm = slot;// blinking alarm slot
        isalarmblinking = 1;//identify a alarm is blinking

        digitalWrite(13, HIGH); delay(50); digitalWrite(13, LOW); delay(50);
      }
    }

    if (alarm_button == HIGH and isalarmblinking == 1){
      manual_stop[current_alarm] = 0;//add manual stop feature to current blinking alarm
      isalarmblinking = 0;
    }

    if (mode == HIGH) {
      IsEditingMode = 1;
      if (mode_status == 5) {
        mode_status = 0;
      }
      mode_status += 1;// selected minute or hours
    }

    //add increment button
    if (increment == HIGH) {
      if (mode_status == 1) {//minutes editing

        minutes += 1;
        if (minutes >= 60) {//set the limit for minutes
          minutes = 0;
        }
      }
      if (mode_status == 2) {//hours editing

        hours += 1;
        if (hours >= 24) {//set the limit for hours
          hours = 0;
        }
      }
      if (mode_status == 3) {//day editing

        day += 1;
        if (day > 31) {// set the day limit
          day = 1;
        }

        dayofweek += 1;
        if (dayofweek > 6) { //set the day of week limit
          dayofweek = 0;
        }

      }

      if (mode_status == 4) {//month editing

        month += 1;
        if (month > 12) {//set the limit for month
          month = 1;
        }
      }

      if (mode_status == 5) {//year editing
        year += 1;
      }

      DisplayTimeBlink(LCD, seconds, minutes, hours, dayofweek, day, month, year );
      setTime(seconds, minutes, hours, dayofweek, day, month, year);
    }

    //add decrement button

    if (decrement == HIGH) {//same as previous
      if (mode_status == 1) {

        minutes -= 1;
        if (minutes < 0) {
          minutes = 59;
        }
      }
      if (mode_status == 2) {

        hours -= 1;
        if (hours < 0) {
          hours = 23;
        }
      }
      if (mode_status == 3) {

        day -= 1;
        if (day < 1) {
          day = 31;
        }

        dayofweek -= 1;
        if (dayofweek < 0) {
          dayofweek = 6;
        }
      }

      if (mode_status == 4) {

        month -= 1;
        if (month < 1) {
          month = 12;
        }
      }

      if (mode_status == 5) {
        year -= 1;
      }
      DisplayTimeBlink(LCD, seconds, minutes, hours, dayofweek, day, month, year );
      setTime(seconds, minutes, hours, dayofweek, day, month, year);//set the new time to RTC
    }

    //set the new time in normal mode
    if (set_button == HIGH and IsEditingMode == 1) {
      setTime(00, minutes, hours, dayofweek, day, month, year);

      IsEditingMode = 0;
      readTime(&seconds, &minutes, &hours, &dayofweek, &day, &month, &year );

    }

    if (IsEditingMode == 0) {
      readTime(&seconds, &minutes, &hours, &dayofweek, &day, &month, &year );
      DisplayTime(LCD, seconds, minutes, hours, dayofweek, day, month, year);
    }

    else {
      DisplayTimeBlink(LCD, seconds, minutes, hours, dayofweek, day, month, year );
    }
  }
}
