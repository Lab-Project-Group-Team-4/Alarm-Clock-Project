#include <avr/pgmspace.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <stdlib.h>
#include <avr/io.h>
#include "tone.h"


int qone() {
	// internal RC oscillator calibration for 8MHz.
	OSCCAL = 176;

	// enable the piezo as output
	DDRD |= (1<<PD1);
	
	// enable internal pullup on PA7 (the button)
	PORTD |= (1<<PD7)|(1<<PD6)|(1<<PD2)|(1<<PD3);
	
	EICRA |= (1 << ISC01)|(1 << ISC11);    // set INT0 to trigger on ANY logic change
	EIMSK |= (1 << INT0)|(1 << INT1);
	sei();

	tracknumber=1;
	

	// loop forever!
	while(1) {
		if (var==1){play_();}
		
		if ((PIND&(1<<PD6))==0){
			next();
			
			_delay_ms(200);
		}
		
		if ((PIND&(1<<PD7))==0){
			pre();
			_delay_ms(200);
		}
		
		
		

	}
	
	return 0;
}
void play_tone(uint16_t delay, uint8_t duration) {
	// delay is half-period in microseconds
	// duration is in 10ms increments
	
	// example: 440Hz --> delay=1136
	
	
	// duration = 2*delay * cycles (all in same units)
	// cycles = 10000 * duration / delay / 2
	// cycles = 100 * duration / (delay/50)
	uint16_t tmp = 100 * duration;
	uint16_t delaysm = delay / 50;
	uint16_t cycles = tmp / delaysm;
	
	while(cycles > 0) {
		if (delay==NOTE_DS8){
			PORTD |= (1<<PD1);
			_delay_us(31);
			PORTD &= ~(1<<PD1);
		_delay_us(31);}


		if (delay==NOTE_D8){
			PORTD |= (1<<PD1);
			_delay_us(33);
			PORTD &= ~(1<<PD1);
		_delay_us(33);}


		if (delay==NOTE_CS8){
			PORTD |= (1<<PD1);
			_delay_us(35);
			PORTD &= ~(1<<PD1);
		_delay_us(35);}


		if (delay==NOTE_C8){
			PORTD |= (1<<PD1);
			_delay_us(37);
			PORTD &= ~(1<<PD1);
		_delay_us(37);}


		if (delay==NOTE_B7){
			PORTD |= (1<<PD1);
			_delay_us(39);
			PORTD &= ~(1<<PD1);
		_delay_us(39);}


		if (delay==NOTE_AS7){
			PORTD |= (1<<PD1);
			_delay_us(41);
			PORTD &= ~(1<<PD1);
		_delay_us(41);}


		if (delay==NOTE_A7){
			PORTD |= (1<<PD1);
			_delay_us(44);
			PORTD &= ~(1<<PD1);
		_delay_us(44);}


		if (delay==NOTE_GS7){
			PORTD |= (1<<PD1);
			_delay_us(46);
			PORTD &= ~(1<<PD1);
		_delay_us(46);}


		if (delay==NOTE_G7){
			PORTD |= (1<<PD1);
			_delay_us(49);
			PORTD &= ~(1<<PD1);
		_delay_us(49);}


		if (delay==NOTE_FS7){
			PORTD |= (1<<PD1);
			_delay_us(52);
			PORTD &= ~(1<<PD1);
		_delay_us(52);}


		if (delay==NOTE_F7){
			PORTD |= (1<<PD1);
			_delay_us(55);
			PORTD &= ~(1<<PD1);
		_delay_us(55);}


		if (delay==NOTE_E7){
			PORTD |= (1<<PD1);
			_delay_us(58);
			PORTD &= ~(1<<PD1);
		_delay_us(58);}


		if (delay==NOTE_DS7){
			PORTD |= (1<<PD1);
			_delay_us(62);
			PORTD &= ~(1<<PD1);
		_delay_us(62);}


		if (delay==NOTE_D7){
			PORTD |= (1<<PD1);
			_delay_us(65);
			PORTD &= ~(1<<PD1);
		_delay_us(65);}


		if (delay==NOTE_CS7){
			PORTD |= (1<<PD1);
			_delay_us(69);
			PORTD &= ~(1<<PD1);
		_delay_us(69);}


		if (delay==NOTE_C7){
			PORTD |= (1<<PD1);
			_delay_us(73);
			PORTD &= ~(1<<PD1);
		_delay_us(73);}


		if (delay==NOTE_B6){
			PORTD |= (1<<PD1);
			_delay_us(78);
			PORTD &= ~(1<<PD1);
		_delay_us(78);}


		if (delay==NOTE_AS6){
			PORTD |= (1<<PD1);
			_delay_us(82);
			PORTD &= ~(1<<PD1);
		_delay_us(82);}


		if (delay==NOTE_A6){
			PORTD |= (1<<PD1);
			_delay_us(87);
			PORTD &= ~(1<<PD1);
		_delay_us(87);}


		if (delay==NOTE_GS6){
			PORTD |= (1<<PD1);
			_delay_us(93);
			PORTD &= ~(1<<PD1);
		_delay_us(93);}


		if (delay==NOTE_G6){
			PORTD |= (1<<PD1);
			_delay_us(98);
			PORTD &= ~(1<<PD1);
		_delay_us(98);}


		if (delay==NOTE_FS6){
			PORTD |= (1<<PD1);
			_delay_us(104);
			PORTD &= ~(1<<PD1);
		_delay_us(104);}


		if (delay==NOTE_F6){
			PORTD |= (1<<PD1);
			_delay_us(110);
			PORTD &= ~(1<<PD1);
		_delay_us(110);}


		if (delay==NOTE_E6){
			PORTD |= (1<<PD1);
			_delay_us(117);
			PORTD &= ~(1<<PD1);
		_delay_us(117);}


		if (delay==NOTE_DS6){
			PORTD |= (1<<PD1);
			_delay_us(123);
			PORTD &= ~(1<<PD1);
		_delay_us(123);}


		if (delay==NOTE_D6){
			PORTD |= (1<<PD1);
			_delay_us(131);
			PORTD &= ~(1<<PD1);
		_delay_us(131);}


		if (delay==NOTE_CS6){
			PORTD |= (1<<PD1);
			_delay_us(139);
			PORTD &= ~(1<<PD1);
		_delay_us(139);}


		if (delay==NOTE_C6){
			PORTD |= (1<<PD1);
			_delay_us(147);
			PORTD &= ~(1<<PD1);
		_delay_us(147);}


		if (delay==NOTE_B5){
			PORTD |= (1<<PD1);
			_delay_us(156);
			PORTD &= ~(1<<PD1);
		_delay_us(156);}


		if (delay==NOTE_AS5){
			PORTD |= (1<<PD1);
			_delay_us(165);
			PORTD &= ~(1<<PD1);
		_delay_us(165);}


		if (delay==NOTE_A5){
			PORTD |= (1<<PD1);
			_delay_us(175);
			PORTD &= ~(1<<PD1);
		_delay_us(175);}


		if (delay==NOTE_GS5){
			PORTD |= (1<<PD1);
			_delay_us(185);
			PORTD &= ~(1<<PD1);
		_delay_us(185);}


		if (delay==NOTE_G5){
			PORTD |= (1<<PD1);
			_delay_us(196);
			PORTD &= ~(1<<PD1);
		_delay_us(196);}


		if (delay==NOTE_FS5){
			PORTD |= (1<<PD1);
			_delay_us(208);
			PORTD &= ~(1<<PD1);
		_delay_us(208);}


		if (delay==NOTE_F5){
			PORTD |= (1<<PD1);
			_delay_us(220);
			PORTD &= ~(1<<PD1);
		_delay_us(220);}


		if (delay==NOTE_E5){
			PORTD |= (1<<PD1);
			_delay_us(233);
			PORTD &= ~(1<<PD1);
		_delay_us(233);}


		if (delay==NOTE_DS5){
			PORTD |= (1<<PD1);
			_delay_us(247);
			PORTD &= ~(1<<PD1);
		_delay_us(247);}


		if (delay==NOTE_D5){
			PORTD |= (1<<PD1);
			_delay_us(262);
			PORTD &= ~(1<<PD1);
		_delay_us(262);}


		if (delay==NOTE_CS5){
			PORTD |= (1<<PD1);
			_delay_us(277);
			PORTD &= ~(1<<PD1);
		_delay_us(277);}


		if (delay==NOTE_C5){
			PORTD |= (1<<PD1);
			_delay_us(294);
			PORTD &= ~(1<<PD1);
		_delay_us(294);}


		if (delay==NOTE_B4){
			PORTD |= (1<<PD1);
			_delay_us(311);
			PORTD &= ~(1<<PD1);
		_delay_us(311);}


		if (delay==NOTE_AS4){
			PORTD |= (1<<PD1);
			_delay_us(330);
			PORTD &= ~(1<<PD1);
		_delay_us(330);}


		if (delay==NOTE_A4){
			PORTD |= (1<<PD1);
			_delay_us(349);
			PORTD &= ~(1<<PD1);
		_delay_us(349);}


		if (delay==NOTE_GS4){
			PORTD |= (1<<PD1);
			_delay_us(370);
			PORTD &= ~(1<<PD1);
		_delay_us(370);}


		if (delay==NOTE_G4){
			PORTD |= (1<<PD1);
			_delay_us(392);
			PORTD &= ~(1<<PD1);
		_delay_us(392);}


		if (delay==NOTE_FS4){
			PORTD |= (1<<PD1);
			_delay_us(415);
			PORTD &= ~(1<<PD1);
		_delay_us(415);}


		if (delay==NOTE_F4){
			PORTD |= (1<<PD1);
			_delay_us(440);
			PORTD &= ~(1<<PD1);
		_delay_us(440);}


		if (delay==NOTE_E4){
			PORTD |= (1<<PD1);
			_delay_us(466);
			PORTD &= ~(1<<PD1);
		_delay_us(466);}


		if (delay==NOTE_DS4){
			PORTD |= (1<<PD1);
			_delay_us(494);
			PORTD &= ~(1<<PD1);
		_delay_us(494);}


		if (delay==NOTE_D4){
			PORTD |= (1<<PD1);
			_delay_us(523);
			PORTD &= ~(1<<PD1);
		_delay_us(523);}


		if (delay==NOTE_CS4){
			PORTD |= (1<<PD1);
			_delay_us(554);
			PORTD &= ~(1<<PD1);
		_delay_us(554);}


		if (delay==NOTE_C4){
			PORTD |= (1<<PD1);
			_delay_us(587);
			PORTD &= ~(1<<PD1);
		_delay_us(587);}


		if (delay==NOTE_B3){
			PORTD |= (1<<PD1);
			_delay_us(622);
			PORTD &= ~(1<<PD1);
		_delay_us(622);}


		if (delay==NOTE_AS3){
			PORTD |= (1<<PD1);
			_delay_us(659);
			PORTD &= ~(1<<PD1);
		_delay_us(659);}


		if (delay==NOTE_A3){
			PORTD |= (1<<PD1);
			_delay_us(698);
			PORTD &= ~(1<<PD1);
		_delay_us(698);}


		if (delay==NOTE_GS3){
			PORTD |= (1<<PD1);
			_delay_us(740);
			PORTD &= ~(1<<PD1);
		_delay_us(740);}


		if (delay==NOTE_G3){
			PORTD |= (1<<PD1);
			_delay_us(784);
			PORTD &= ~(1<<PD1);
		_delay_us(784);}


		if (delay==NOTE_FS3){
			PORTD |= (1<<PD1);
			_delay_us(831);
			PORTD &= ~(1<<PD1);
		_delay_us(831);}


		if (delay==NOTE_F3){
			PORTD |= (1<<PD1);
			_delay_us(880);
			PORTD &= ~(1<<PD1);
		_delay_us(880);}


		if (delay==NOTE_E3){
			PORTD |= (1<<PD1);
			_delay_us(932);
			PORTD &= ~(1<<PD1);
		_delay_us(932);}


		if (delay==NOTE_DS3){
			PORTD |= (1<<PD1);
			_delay_us(988);
			PORTD &= ~(1<<PD1);
		_delay_us(988);}


		if (delay==NOTE_D3){
			PORTD |= (1<<PD1);
			_delay_us(1047);
			PORTD &= ~(1<<PD1);
		_delay_us(1047);}


		if (delay==NOTE_CS3){
			PORTD |= (1<<PD1);
			_delay_us(1109);
			PORTD &= ~(1<<PD1);
		_delay_us(1109);}


		if (delay==NOTE_C3){
			PORTD |= (1<<PD1);
			_delay_us(1175);
			PORTD &= ~(1<<PD1);
		_delay_us(1175);}


		if (delay==NOTE_B2){
			PORTD |= (1<<PD1);
			_delay_us(1245);
			PORTD &= ~(1<<PD1);
		_delay_us(1245);}


		if (delay==NOTE_AS2){
			PORTD |= (1<<PD1);
			_delay_us(1319);
			PORTD &= ~(1<<PD1);
		_delay_us(1319);}


		if (delay==NOTE_A2){
			PORTD |= (1<<PD1);
			_delay_us(1397);
			PORTD &= ~(1<<PD1);
		_delay_us(1397);}


		if (delay==NOTE_GS2){
			PORTD |= (1<<PD1);
			_delay_us(1480);
			PORTD &= ~(1<<PD1);
		_delay_us(1480);}


		if (delay==NOTE_G2){
			PORTD |= (1<<PD1);
			_delay_us(1568);
			PORTD &= ~(1<<PD1);
		_delay_us(1568);}


		if (delay==NOTE_FS2){
			PORTD |= (1<<PD1);
			_delay_us(1661);
			PORTD &= ~(1<<PD1);
		_delay_us(1661);}


		if (delay==NOTE_F2){
			PORTD |= (1<<PD1);
			_delay_us(1760);
			PORTD &= ~(1<<PD1);
		_delay_us(1760);}


		if (delay==NOTE_E2){
			PORTD |= (1<<PD1);
			_delay_us(1865);
			PORTD &= ~(1<<PD1);
		_delay_us(1865);}


		if (delay==NOTE_DS2){
			PORTD |= (1<<PD1);
			_delay_us(1976);
			PORTD &= ~(1<<PD1);
		_delay_us(1976);}


		if (delay==NOTE_D2){
			PORTD |= (1<<PD1);
			_delay_us(2093);
			PORTD &= ~(1<<PD1);
		_delay_us(2093);}


		if (delay==NOTE_CS2){
			PORTD |= (1<<PD1);
			_delay_us(2217);
			PORTD &= ~(1<<PD1);
		_delay_us(2217);}


		if (delay==NOTE_C2){
			PORTD |= (1<<PD1);
			_delay_us(2349);
			PORTD &= ~(1<<PD1);
		_delay_us(2349);}


		if (delay==NOTE_B1){
			PORTD |= (1<<PD1);
			_delay_us(2489);
			PORTD &= ~(1<<PD1);
		_delay_us(2489);}


		if (delay==NOTE_AS1){
			PORTD |= (1<<PD1);
			_delay_us(2637);
			PORTD &= ~(1<<PD1);
		_delay_us(2637);}


		if (delay==NOTE_A1){
			PORTD |= (1<<PD1);
			_delay_us(2794);
			PORTD &= ~(1<<PD1);
		_delay_us(2794);}


		if (delay==NOTE_GS1){
			PORTD |= (1<<PD1);
			_delay_us(2960);
			PORTD &= ~(1<<PD1);
		_delay_us(2960);}


		if (delay==NOTE_G1){
			PORTD |= (1<<PD1);
			_delay_us(3136);
			PORTD &= ~(1<<PD1);
		_delay_us(3136);}


		if (delay==NOTE_FS1){
			PORTD |= (1<<PD1);
			_delay_us(3322);
			PORTD &= ~(1<<PD1);
		_delay_us(3322);}


		if (delay==NOTE_F1){
			PORTD |= (1<<PD1);
			_delay_us(3520);
			PORTD &= ~(1<<PD1);
		_delay_us(3520);}


		if (delay==NOTE_E1){
			PORTD |= (1<<PD1);
			_delay_us(3729);
			PORTD &= ~(1<<PD1);
		_delay_us(3729);}


		if (delay==NOTE_DS1){
			PORTD |= (1<<PD1);
			_delay_us(3951);
			PORTD &= ~(1<<PD1);
		_delay_us(3951);}


		if (delay==NOTE_D1){
			PORTD |= (1<<PD1);
			_delay_us(4186);
			PORTD &= ~(1<<PD1);
		_delay_us(4186);}


		if (delay==NOTE_CS1){
			PORTD |= (1<<PD1);
			_delay_us(4435);
			PORTD &= ~(1<<PD1);
		_delay_us(4435);}


		if (delay==NOTE_C1){
			PORTD |= (1<<PD1);
			_delay_us(4699);
			PORTD &= ~(1<<PD1);
		_delay_us(4699);}


		if (delay==NOTE_B0){
			PORTD |= (1<<PD1);
			_delay_us(4978);
			PORTD &= ~(1<<PD1);
		_delay_us(4978);}

		cycles--;
		
	}
}

void pla(){

var=1;}
void sto(){
	var=0;
}

ISR (INT0_vect)          //External interrupt_zero ISR
{
	pla();
	
	
}
ISR (INT1_vect)        //External interrupt_one ISR
{
	sto();
}

void next(){
	if(tracknumber<maxnumber){tracknumber=tracknumber+1; //increment file name,curb the filename to 3(for testing=3)
	}
	else{tracknumber=1;
	}


}

void pre(){
	if(tracknumber>1){tracknumber=tracknumber-1; //increment file name,curb the filename to 3(for testing=3)
	}
	else{tracknumber=maxnumber;
	}
}

void del(int ms){
	while(ms--){_delay_ms(1);}}

	int Pirates()
	{
		const int totalNotes = sizeof(notes) / sizeof(int);
		// Loop through each note
		for (int i = 0; i < totalNotes; i++)
		{if (var==0){
		return 0;}
		
		
		const int currentNote = notes[i];
		int wait = durations[i] / songSpeed;
		// Play tone if currentNote is not 0 frequency, otherwise pause (noTone)
		if (currentNote !=0){
		play_tone( notes[i], wait/50); }
		
		// delay is used to wait for tone to finish playing before moving to next loop
		else{del(wait/10-0.5);}
		del(wait/10-5.5);
	}
}
int GameOfThrones(){
	const int totalNotes = sizeof(notes) / sizeof(int);
	// Loop through each note
	for (int i = 0; i < totalNotes; i++)
	{if (var==0){
	return 0;}
	
	
	const int currentNote = notes[i];
	int wait = durations[i] / songSpeed;
	// Play tone if currentNote is not 0 frequency, otherwise pause (noTone)
	if (currentNote !=0){
	play_tone( notes[i], wait/50); }
	
	// delay is used to wait for tone to finish playing before moving to next loop
	else{del(wait/10-0.5);}
	del(wait/10-5.5);
}
}
void play_(){
	if(tracknumber ==1){Pirates();
	}
	else{if(tracknumber==2){GameOfThrones();
	}}
	
}

