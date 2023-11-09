/******************************************************************************
 *
 * Module: Application
 *
 * File Name: main.c
 *
 * Description: main Application
 *
 * Author: Muhammad Salah
 *
 *******************************************************************************/


#include <avr/io.h> /* To use the SREG register */
#include "HAL/lcd.h"
#include "HAL/ultrasonic.h"
#include <util/delay.h>

/*
 * Function Description :
 * display the current distance read by ultrasonic on LCD
 */
void display_distance(uint16 distance)
{
	/* Display the distance value */
	LCD_moveCursor(0,11);
	LCD_intgerToString(distance);
	if(distance < 100)
	{
		LCD_displayString(" "); /* to avoid overwriting */

	}
	LCD_displayStringRowColumn(0,14,"cm");

}

int main()
{
	/* Initialize distance variable */
	uint16 distance = 0;

	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	/* Initialize both the LCD and Ultrasonic drivers */
	LCD_init();
	Ultrasonic_init();

	LCD_displayString("Distance =");

	while(1)
	{
		/*store the value of the distance*/
		distance = Ultrasonic_readDistance();
		display_distance(distance);

	}

}

