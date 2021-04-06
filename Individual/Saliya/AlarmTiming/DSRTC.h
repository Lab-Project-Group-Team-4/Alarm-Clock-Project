#include <Wire.h>
#include<LiquidCrystal.h>
LiquidCrystal *object;
#define ADDRESS 0x68
String daysOfweek[7] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

class Set_LCD{
  private:
  int RS;
  int E;
  int pin_1;//lcd display pins
  int pin_2;
  int pin_3;
  int pin_4;
  int check=0;
  
  public:
    Set_LCD(int RS_pin, int enable, int p1, int p2, int p3, int p4){
      RS = RS_pin;
      E = enable;
      pin_1 = p1;
      pin_2 = p2;
      pin_3 = p3;
      pin_4 = p4; 
      
      LiquidCrystal LCD(RS,E,pin_1,pin_2,pin_3,pin_4);
      object = &LCD;
      LCD.begin(16,2);
    }

    void DISP(String word_1){
      
      LiquidCrystal LCD = *object;
      LCD.print(word_1);
      check += 1;
    }

    void DISP(int value){
      
      LiquidCrystal LCD = *object;
      LCD.print(value);
      check += 1;
    }

    void clear_all(){
      LiquidCrystal LCD = *object;
      LCD.clear();
      
    }
    void set_pos(int col,int row){
      LiquidCrystal LCD = *object;
      LCD.setCursor(col,row);
    
    }
    
};
// binary coded decimal and decimal conversion
byte BCDtoDEC(byte value){
  return (value/16*10 +value%16); 
}

byte DECtoBCD(byte value){
  return (value/10*16 +value%10); 
}
// begin 
void DS3232Begin(){

  Wire.begin();
  
}
// set the time to DS3232
void setTime(byte seconds,byte minutes, byte hours,byte dayofweek, byte day, byte month, byte year ){
  Wire.beginTransmission(ADDRESS);
  Wire.write(0);
  Wire.write(DECtoBCD(seconds));
  Wire.write(DECtoBCD(minutes));
  Wire.write((DECtoBCD(hours)));
  Wire.write(DECtoBCD(dayofweek));
  Wire.write(DECtoBCD(day));
  Wire.write(DECtoBCD(month));
  Wire.write(DECtoBCD(year));
  Wire.endTransmission();
  
}
// read time updates from DS3232
void readTime(byte* seconds,byte* minutes, byte* hours,byte* dayofweek, byte* day, byte* month, byte* year ){
  Wire.beginTransmission(ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(ADDRESS, 7);
  *seconds = BCDtoDEC(Wire.read() & 0x7F);
  *minutes = BCDtoDEC(Wire.read());
  *hours = BCDtoDEC(Wire.read() & 0x3F);
  *dayofweek = BCDtoDEC(Wire.read());
  *day = BCDtoDEC(Wire.read());
  *month = BCDtoDEC(Wire.read());
  *year = BCDtoDEC(Wire.read());
}
// display function to lcd dispaly
void DisplayTime(Set_LCD LCD, int seconds,int minutes,int hours,int dayofweek,int day,int month,int year){
  LCD.DISP(seconds);LCD.DISP(":");LCD.DISP(minutes);LCD.DISP(":");LCD.DISP(hours);
  
  LCD.DISP(" ");LCD.DISP(daysOfweek[dayofweek]);LCD.DISP(" ");
  LCD.set_pos(0,1);
  LCD.DISP(day);LCD.DISP("/");LCD.DISP(month);LCD.DISP("/");LCD.DISP(year);
  
  delay(500);
  LCD.clear_all();
  
}

// time dispalying with a blink
void DisplayTimeBlink(Set_LCD LCD, int seconds,int minutes,int hours,int dayofweek,int day,int month,int year){


  LCD.DISP(seconds);LCD.DISP(":");LCD.DISP(minutes);LCD.DISP(":");LCD.DISP(hours);
  
  LCD.DISP(" ");LCD.DISP(daysOfweek[dayofweek]);LCD.DISP(" ");
  LCD.set_pos(0,1);
  LCD.DISP(day);LCD.DISP("/");LCD.DISP(month);LCD.DISP("/");LCD.DISP(year);
  
  delay(100);
  LCD.clear_all();
  delay(100);
}
// dispaly alarm time and alarm time setting

void alarm_disp(Set_LCD LCD,int minutes, int hours){
  //LCD.DISP("set alarm");
  LCD.DISP(minutes);LCD.DISP(":");LCD.DISP(hours);LCD.DISP(" ");
  
  
}

void slot_disp(Set_LCD LCD,int slot){
    //LCD.DISP("Select_slot(0-4)");
    LCD.DISP(" "); LCD.DISP(slot);delay(100);LCD.clear_all();
    delay(100);
}
