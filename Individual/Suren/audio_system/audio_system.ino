#include <SD.h>                      // need to include the SD library
//#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
#define SD_ChipSelectPin 4  //using digital pin 4 on arduino nano 328, can use other pins
#include <TMRpcm.h>           //  also need to include this library...
#include <SPI.h>

TMRpcm tmrpcm;   // create an object for use in this sketch
int play_but=2;
int stop_but=3;
File myFile;
char trackname[] = "0001.wav"; //basic denomination
int tracknumber;

int next_bu=7;
int pre_bu=8;

void pla(){
  
  tmrpcm.play(trackname); //the sound file "music" will play each time the arduino powers up, or is reset}
  
}
void sto(){Serial.println("sto"); 
 
  tmrpcm.disable();
  
   
  }

void next(){
  if(tracknumber<4){tracknumber=tracknumber+1; //increment file name,curb the filename to 3(for testing=3)  
     sprintf(trackname, "%04d.wav",tracknumber);//calculate the file name 
     Serial.println(trackname); //name of the new file to be played}
  }
  else{tracknumber=1;
  sprintf(trackname, "%04d.wav",tracknumber);//calculate the file name 
     Serial.println(trackname); //name of the new file to be played}
     }
     pla();
}

void pre(){
  if(tracknumber>1){tracknumber=tracknumber-1; //increment file name,curb the filename to 3(for testing=3)  
     sprintf(trackname, "%04d.wav",tracknumber);//calculate the file name 
     Serial.println(trackname); //name of the new file to be played}
  }
   else{tracknumber=4;
  sprintf(trackname, "%04d.wav",tracknumber);//calculate the file name 
     Serial.println(trackname); //name of the new file to be played}
     }
  pla();
}

void setup(){
   tmrpcm.speakerPin = 9; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc
  
  pinMode(pre_bu,INPUT_PULLUP);
  pinMode(next_bu,INPUT_PULLUP);
  
  Serial.begin(9600);
  pinMode(stop_but,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(stop_but),sto,FALLING);

  pinMode(play_but,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(play_but),pla,FALLING);

  sprintf(trackname, "%04d.wav",1);//startup file name

  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");  
    return;   // don't do anything more if not

  }
  else{   
    Serial.println("SD ok");   
  }
}



void loop(){  
  
 int voltage_ne=digitalRead(next_bu);
  if (voltage_ne==LOW){
    next();
    delay(1000);
  }
  int voltage_pre=digitalRead(pre_bu);
   if (voltage_pre==LOW){
    pre();
    delay(1000);
  }

  
}
