#include <Keypad.h>
#include <LiquidCrystal.h>
const int rs=12, en=13, d4=3,d5=2, d6=1, d7=0;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
const byte ROWS = 4;
const byte COLS = 3;

byte rowPins[ROWS] = {7, 8, 9, 10};
byte colPins[COLS] = {4, 5, 6};

char keys[ROWS][COLS] ={ 
   {'1', '2', '3'},
   {'4', '5', '6'},
   {'7', '8', '9'},
   {'*', '0', '#'}
};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
 
void setup(){
  pinMode(11,OUTPUT);
  digitalWrite(11,HIGH);
  lcd.begin(16,2);
  lcd.clear();
}
 
void loop(){
  char key = keypad.getKey();
  if (key){
    lcd.setCursor(1,1);
    lcd.print(key);
  }
}
