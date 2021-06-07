// Define pin 10 for buzzer, you can use any other digital pins (Pin 0-13)


int initial = 0;
// Change to 0.5 for a slower version of the song, 1.25 for a faster version
const float songSpeed = 1.0;
const float songSpeed_G = 1.0;
// Defining frequency of each music note
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

// Music notes of the song, 0 is a rest/pulse
int notes[] = {
    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
    NOTE_A4, NOTE_G4, NOTE_A4, 0,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
    NOTE_A4, NOTE_G4, NOTE_A4, 0,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
    NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
    NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_D5, NOTE_E5, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
    NOTE_C5, NOTE_A4, NOTE_B4, 0,

    NOTE_A4, NOTE_A4,
    //Repeat of first part
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
    NOTE_A4, NOTE_G4, NOTE_A4, 0,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
    NOTE_A4, NOTE_G4, NOTE_A4, 0,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
    NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
    NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_D5, NOTE_E5, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
    NOTE_C5, NOTE_A4, NOTE_B4, 0,
    //End of Repeat

    NOTE_E5, 0, 0, NOTE_F5, 0, 0,
    NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
    NOTE_D5, 0, 0, NOTE_C5, 0, 0,
    NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

    NOTE_E5, 0, 0, NOTE_F5, 0, 0,
    NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
    NOTE_D5, 0, 0, NOTE_C5, 0, 0,
    NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4};

// Durations (in ms) of each music note of the song
// Quarter Note is 250 ms when songSpeed = 1.0
int durations[] = {
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125,

    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125,

    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 125, 250, 125,

    125, 125, 250, 125, 125,
    250, 125, 250, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 375,

    250, 125,
    //Rpeat of First Part
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125,

    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125,

    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 125, 250, 125,

    125, 125, 250, 125, 125,
    250, 125, 250, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 375,
    //End of Repeat

    250, 125, 375, 250, 125, 375,
    125, 125, 125, 125, 125, 125, 125, 125, 375,
    250, 125, 375, 250, 125, 375,
    125, 125, 125, 125, 125, 500,

    250, 125, 375, 250, 125, 375,
    125, 125, 125, 125, 125, 125, 125, 125, 375,
    250, 125, 375, 250, 125, 375,
    125, 125, 125, 125, 125, 500};
int notes_G[]={NOTE_G4,NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_G4,NOTE_C4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_C4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_D4,NOTE_G3,NOTE_AS3,NOTE_C4,NOTE_D4,NOTE_F4,NOTE_AS3,NOTE_DS4,NOTE_D4,NOTE_F4,NOTE_AS3,NOTE_DS4,NOTE_D4,NOTE_C4,NOTE_GS3,NOTE_AS3,NOTE_C4,NOTE_F3,NOTE_G4,NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_G4,NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_D4,NOTE_G3,NOTE_AS3,NOTE_C4,NOTE_D4,NOTE_G4,NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_G4,NOTE_C4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_C4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_D4,NOTE_G3,NOTE_AS3,NOTE_C4,NOTE_D4,NOTE_F4,NOTE_AS3,NOTE_DS4,NOTE_D4,NOTE_F4,NOTE_AS3,NOTE_DS4,NOTE_D4,NOTE_C4,NOTE_GS3,NOTE_AS3,NOTE_C4,NOTE_F3,NOTE_G4,NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_G4,NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_D4,NOTE_G3,NOTE_AS3,NOTE_C4,NOTE_D4};
int duration_G[]={500, 500, 250, 250, 500, 500, 250, 250, 1500, 1500, 250, 250, 1000, 1000, 250, 250, 500, 500, 250, 250, 1500, 1500, 1000, 250, 250, 1000, 1000, 250, 250, 500, 250, 250, 500, 500, 1000, 1000, 250, 250, 1000, 1000, 250, 250, 500, 500, 250, 250, 500, 500, 500, 250, 250, 500, 500, 250, 250, 1500, 1500, 250, 250, 1000, 1000, 250, 250, 500, 500, 250, 250, 1500, 1500, 1000, 250, 250, 1000, 1000, 250, 250, 500, 250, 250, 500, 500, 1000, 1000, 250, 250, 1000, 1000, 250, 250, 500, 500, 250, 250, 500};
int notone[]={9,10,11,13};

const int speakerPin = 13;
int var=0;

int next_bu=7;
int pre_bu=8;

int pla_=2;
int stop_=3;

int maxnumber= 2; //basic denomination
int tracknumber;

int Pirates()
{
  const int totalNotes = sizeof(notes) / sizeof(int);
  // Loop through each note
  for (int i = 0; i < totalNotes; i++)
  {if (var==0){
    return 0;}
    Serial.println(i);
    
    const int currentNote = notes[i];
    float wait = durations[i] / songSpeed;
    // Play tone if currentNote is not 0 frequency, otherwise pause (noTone)
    if (currentNote != 0)
    {
      tone(speakerPin, notes[i], wait); // tone(pin, frequency, duration)
    }
    else
    {
      noTone(speakerPin);
    }
    // delay is used to wait for tone to finish playing before moving to next loop
    delay(wait);
  }
}

int GameOfThrones() {
  {
  const int totalNotes = sizeof(notes_G) / sizeof(int);
  // Loop through each note
  for (int i = 0; i < totalNotes; i++)
     {if (var==0){
    return 0;}
     Serial.println(i);
      const int currentNote = notes_G[i];
    float wait = duration_G[i] / songSpeed_G;
    // Play tone if currentNote is not 0 frequency, otherwise pause (noTone)
    if (currentNote != 0)
    {
      tone(speakerPin, notes_G[i], wait); // tone(pin, frequency, duration)
    }
    else
    {
      noTone(speakerPin);
    }
    
    // delay is used to wait for tone to finish playing before moving to next loop
    delay(wait);
    if (i!=notone[i]){
      noTone(speakerPin);}}
}

}



void play_(){
 
 
  if(tracknumber==1){
    Pirates();}
  else{if(tracknumber==2){
    GameOfThrones();}}
}
void pla(){
  Serial.println("play"); 
  var=1;}
void sto(){Serial.println("sto");
  var=0;
}

  
void next(){
  Serial.println("next");
  if(tracknumber<maxnumber){tracknumber=tracknumber+1; //increment file name,curb the filename to 3(for testing=3)  
     Serial.println(tracknumber); //name of the new file to be played}
  }
  else{tracknumber=1;
     Serial.println(tracknumber); //name of the new file to be played}
     }
     
     
}

void pre(){
  Serial.println("back");
  if(tracknumber>1){tracknumber=tracknumber-1; //increment file name,curb the filename to 3(for testing=3)  

     Serial.println(tracknumber); //name of the new file to be played}
  }
   else{tracknumber=maxnumber;
     Serial.println(tracknumber); //name of the new file to be played}
     }  
}

void setup(){
  
  pinMode(next_bu,INPUT_PULLUP);
  pinMode(pre_bu,INPUT_PULLUP);
  
  Serial.begin(9600);
  pinMode(stop_,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(stop_),sto,FALLING);

  pinMode(pla_,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pla_),pla,FALLING);

  tracknumber=1;

  
}
void loop(){    
 if (var==1){play_();}
 int voltage_ne=digitalRead(next_bu);
 int voltage_pre=digitalRead(pre_bu);
  if (voltage_ne==LOW){
    next();
    delay(1000);
  }
   if (voltage_pre==LOW){
    pre();
    delay(1000);
  }
    }
  
