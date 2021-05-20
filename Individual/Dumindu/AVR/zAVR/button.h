/*
 * button.h
 *
 * Created: 5/13/2021 10:56:36 AM
 *  Author: USER
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_


#define BUTTON_DIR DDRB
#define BUTTON_PORT PINB
#define SELECT_PIN PINB0
#define DOWN_PIN PINB1
#define UP_PIN PINB2
#define DESELECT_PIN PINB3
#define SELECT 1
#define DOWN 2
#define UP 3
#define DESELECT 4

int button;


void initializeKeyPress(void){
	BUTTON_DIR = 0x00;
}

int keyPressed(void){
	
	if (BUTTON_PORT & (1<<SELECT_PIN)) button = SELECT;
	else if (BUTTON_PORT & (1<<DOWN_PIN)) button = DOWN;
	else if (BUTTON_PORT & (1<<UP_PIN)) button = UP;
	else if (BUTTON_PORT & (1<<DESELECT_PIN)) button = DESELECT;
	else return 0;
	return button;
}




#endif /* BUTTON_H_ */