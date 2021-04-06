/* Play "He's A Pirate" / "Pirates of the Caribbean" Theme Song
 * By Xitang Zhao 2016.06.27
 * Youtube in Action: https://youtu.be/sjPAj1lXgtk
 * or TikTok in Action: https://www.tiktok.com/@tipstorylearn/video/6943019804261502213
 * 
 * INSTRUCTION: Hook up Pin 10 to the positive side of a buzzer or a microphone, hook up 
 * any resistor to the negative side of a buzzer (to limit current & volume & to protect the pin), 
 * and then connect the other end of the resistor to ground pin. Upload the sketch and enjoy! 
 * 
 * Don't have an Arduino right now? No worry. You can test it vitually on my TinkerCAD circuit:
 * https://www.tinkercad.com/things/f9QN4skaguI-play-pirates-of-the-caribbean-theme-song-on-buzzer
 * 
 * To learn the science of buzzer, Arduino tone library, and a step by step walkthrough of how I made this
 * Visit my learning note on TipStory: https://www.tipstory.org/learning/h2lUMccm5MeuSds
 * 
 * Last updated: 2021.03.25
 * ---------------------
 * Credits:
 * 
 * Music notes of the song obtained from Easy Music (Great website)
 * Link: http://easymusic.altervista.org/recorder-hes-a-pirate-pirates-of-caribbean-sheet-music-guitar-chords/
 * 
 * Musicnotes's "How to Read Sheet Music" Guide
 * Link: http://www.musicnotes.com/blog/2014/04/11/how-to-read-sheet-music/
 * 
 * Code inspired by Chapter 5 of Jeremy Blum's book "Exploring Arduino"
 * Link: http://www.exploringarduino.com/content/ch5/
 * 
 * Music notes' frequencies obtained from arduino website and Tone Library
 * Link: https://www.arduino.cc/en/Tutorial/toneMelody
 * Link: https://github.com/bhagman/Tone
 * 
 */

// Define pin 10 for buzzer, you can use any other digital pins (Pin 0-13)
const int speakerPin = 13;
const int inbuttonPin = A0;
const int clbuttonpin =A1;
const int change =A2;
const int valu=400;
int initial = 0;
// Change to 0.5 for a slower version of the song, 1.25 for a faster version
const float songSpeed = 1.0;

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

void Pirates()
{
  const int totalNotes = sizeof(notes) / sizeof(int);
  // Loop through each note
  for (int i = 0; i < totalNotes; i++)
  {int paubut=analogRead(clbuttonpin);
   if (paubut<valu){
    break;
  }
    
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
void GameOfThrones() {
  int paubut=analogRead(clbuttonpin);
     if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_G4);
    delay(500);
    noTone(speakerPin);
    if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_C4);
    delay(500);
    noTone(speakerPin);
      if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_DS4);
    delay(250);
    noTone(speakerPin);
    if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_F4);
    delay(250);
    noTone(speakerPin);
      if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_G4);
    delay(500);
    noTone(speakerPin);
    if (paubut<valu){
    return;
  }

    tone(speakerPin, NOTE_C4);
    delay(500);
    noTone(speakerPin);
    if (paubut<valu){
    return;
  }

    tone(speakerPin, NOTE_E4);
    delay(250);
    noTone(speakerPin);
    if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_F4);
    delay(250);
    noTone(speakerPin);
      if (paubut<valu){
    return;
  }

    tone(speakerPin, NOTE_G4);
    delay(1500);
    noTone(speakerPin);
    if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_C4);
    delay(1500);
    if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_E4);
    delay(250);
    if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_F4);
    delay(250);
    if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_G4);
    delay(1000);
    noTone(speakerPin);
    if (paubut<valu){
    return;
  }

    tone(speakerPin, NOTE_C4);
    delay(1000);
    if (paubut<valu){
    return;
  }

    tone(speakerPin, NOTE_DS4);
    delay(250);
    noTone(speakerPin);
    if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_F4);
    delay(250);
    noTone(speakerPin);
     if (paubut<valu){
    return;
  }   
 
    
    tone(speakerPin, NOTE_D4);
    delay(500);
    noTone(speakerPin);
     if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_G3);
    delay(500);
    noTone(speakerPin);
    if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_AS3);
    delay(250);
    noTone(speakerPin);
    if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_C4);
    delay(250);
    noTone(speakerPin);
  
      if (paubut<valu){
    return;
  }


      tone(speakerPin, NOTE_D4);
      delay(1500);
      noTone(speakerPin);
         if (paubut<valu){
    return;
  } 
      tone(speakerPin, NOTE_F4);
      delay(1500);
      noTone(speakerPin);
    if (paubut<valu){
    return;
  }
      tone(speakerPin, NOTE_AS3);
      delay(1000);
      noTone(speakerPin);
    if (paubut<valu){
    return;
  }
      tone(speakerPin, NOTE_DS4);
      delay(250);
      noTone(speakerPin);
    if (paubut<valu){
    return;
  }
      tone(speakerPin, NOTE_D4);
      delay(250);
      noTone(speakerPin);
    if (paubut<valu){
    return;
  }
      tone(speakerPin, NOTE_F4);
      delay(1000);
      noTone(speakerPin);
    if (paubut<valu){
    return;
  }
      tone(speakerPin, NOTE_AS3);
      delay(1000);
      noTone(speakerPin);
    if (paubut<valu){
    return;
  }
      tone(speakerPin, NOTE_DS4);
      delay(250);
      noTone(speakerPin);
    if (paubut<valu){
    return;
  }
      tone(speakerPin, NOTE_D4);
      delay(250);
      noTone(speakerPin);
    if (paubut<valu){
    return;
  }
      tone(speakerPin, NOTE_C4);
      delay(500);
      noTone(speakerPin);
    if (paubut<valu){
    return;
  }
      tone(speakerPin, NOTE_GS3);
      delay(250);
      noTone(speakerPin);
    if (paubut<valu){
    return;
  }
      tone(speakerPin, NOTE_AS3);
      delay(250);
      noTone(speakerPin);
    if (paubut<valu){
    return;
  }
      tone(speakerPin, NOTE_C4);
      delay(500);
      noTone(speakerPin);
    if (paubut<valu){
    return;
  }
      tone(speakerPin, NOTE_F3);
      delay(500);
      noTone(speakerPin);
    if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_G4);
    delay(1000);
    noTone(speakerPin);
    if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_C4);
    delay(1000);
    noTone(speakerPin);
    if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_DS4);
    delay(250);
    noTone(speakerPin);
    if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_F4);
    delay(250);
    noTone(speakerPin);
    if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_G4);
    delay(1000);
    noTone(speakerPin);
    if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_C4);
    delay(1000);
    noTone(speakerPin);
    if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_DS4);
    delay(250);
    noTone(speakerPin);
    if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_F4);
    delay(250);
    noTone(speakerPin);
    if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_D4);
    delay(500);
    noTone(speakerPin);
        if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_G3);
    delay(500);
    noTone(speakerPin);
    if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_AS3);
    delay(250);
    noTone(speakerPin);
    if (paubut<valu){
    return;
  }
    tone(speakerPin, NOTE_C4);
    delay(250);
    noTone(speakerPin);
    if (paubut<valu){
    return;
  }

    tone(speakerPin, NOTE_D4);
    delay(500);
    noTone(speakerPin);
    if (paubut<valu){
    return;
  }
}


void setup() {
    pinMode(speakerPin, OUTPUT);
    
}

void loop()
{   int pobut = analogRead(inbuttonPin); 
    if (pobut < valu ){ 
      if (initial==0){
        Pirates();}
      else {GameOfThrones();
      }
    }
    int chng=analogRead(change);
    if  (chng <valu){
      if (initial==0){
        initial=1;}
      else {
        initial =0;
      }
     }
  // Nothing in loop. Music only plays once.
  // You can click reset on Arduino to replay the song.
}
