/*
 * keypad.h
 *
 * Created: 5/31/2021 10:03:36 AM
 *  Author: USER
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
#define KEY_PRT		PORTB
#define KEY_DDR		DDRB
#define KEY_PIN		PINB

unsigned char keypad[4][4] = {{'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}};
unsigned char colloc, rowloc;

char keyfind()
{
	while(1)
	{
		KEY_DDR = 0xF0;          // 0b11110000 set port direction as input-output
		KEY_PRT = 0xFF;          // 0b11111111
		
		do
		{
			KEY_PRT &= 0x0F;

			rowloc = (KEY_PIN & 0x0F); /* read status of row */
		}while(rowloc != 0x0F);
		
		do
		{
			do
			{
				
				rowloc = (KEY_PIN & 0x0F); /* read status of row */
				}while(colloc == 0x0F);        /* check for any key press */
				
				rowloc = (KEY_PIN & 0x0F);
			}while(rowloc == 0x0F);

			/* now check for rows */
			KEY_PRT = 0xEF;            /* check for pressed key in 1st column */
			rowloc = (KEY_PIN & 0x0F);
			if(rowloc != 0x0F)
			{
				colloc = 0;
				break;
			}

			KEY_PRT = 0xDF;		/* check for pressed key in 2nd column */
			rowloc = (KEY_PIN & 0x0F);
			if(rowloc != 0x0F)
			{
				colloc = 1;
				break;
			}
			
			KEY_PRT = 0xBF;		/* check for pressed key in 3rd column */
			rowloc = (KEY_PIN & 0x0F);
			if(rowloc != 0x0F)
			{
				colloc = 2;
				break;
			}

		}
		if(rowloc == 0x0E)
		return(keypad[0][colloc]);
		else if(rowloc == 0x0D)
		return(keypad[1][colloc]);
		else if(rowloc == 0x0B)
		return(keypad[2][colloc]);
		else if(rowloc == 0x07)
		return(keypad[3][colloc]);
}

#endif /* KEYPAD_H_ */