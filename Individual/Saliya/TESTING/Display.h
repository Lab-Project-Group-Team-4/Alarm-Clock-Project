#include <Wire.h>
#include<LiquidCrystal.h>
LiquidCrystal LCD(1, 2, 4, 5, 6, 7);

void begin() {
  LCD.begin(16, 2);
  Wire.begin();
}

#define ADDRESS 0x68
String daysOfweek[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

byte BCDtoDEC(byte value) {
  return (value / 16 * 10 + value % 16);
}

byte DECtoBCD(byte value) { // conversion between BCD and Decimal
  return (value / 10 * 16 + value % 10);
}


void setTime(byte seconds, byte minutes, byte hours, byte dayofweek, byte day, byte month, byte year ) {
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
void readTime(byte* seconds, byte* minutes, byte* hours, byte* dayofweek, byte* day, byte* month, byte* year ) {
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

//Display the time on LCD display
void DisplayTime(int seconds, int minutes, int hours, int dayofweek, int day, int month, int year) {

  LCD.print(seconds); LCD.print(":"); LCD.print(minutes); LCD.print(":"); LCD.print(hours);
  LCD.print(" "); LCD.print(daysOfweek[dayofweek]); LCD.print(" ");
  LCD.setCursor(0, 1);
  LCD.print(day); LCD.print("/"); LCD.print(month); LCD.print("/"); LCD.print(year);

  delay(500);
  LCD.clear();

}


void slot_disp(int slot) {
  LCD.clear();
  LCD.print("SELECT THE SLOT");
  LCD.setCursor(0, 1);
  LCD.print(slot);
  
}


void alarm_disp(int minutes, int hours) {
  LCD.clear();
  LCD.print("MINS :HOURS");
  LCD.setCursor(0, 1);
  LCD.print(minutes); LCD.setCursor(5, 1); LCD.print(":"); LCD.print(hours);


}

void DisplayTimeBlink(int seconds, int minutes, int hours, int dayofweek, int day, int month, int year) {


  LCD.print(seconds); LCD.print(":"); LCD.print(minutes); LCD.print(":"); LCD.print(hours);

  LCD.print(" "); LCD.print(daysOfweek[dayofweek]); LCD.print(" ");
  LCD.setCursor(0, 1);
  LCD.print(day); LCD.print("/"); LCD.print(month); LCD.print("/"); LCD.print(year);

  delay(100);
  LCD.clear();
  delay(100);
}

void clear() {
  LCD.clear();
}
