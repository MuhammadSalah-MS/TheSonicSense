/******************************************************************************
 *
 * Module: Ultrasonic Sensor
 *
 * File Name: ultrasonic.c
 *
 * Description: Source file for the Ultranoic sensor driver
 *
 * Author: Muhammad Salah
 *
 *******************************************************************************/

#include "ultrasonic.h"
#include "../MCAL/icu.h"
#include <util/delay.h>

/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/

/*
 * Description:
 * - Send the Trigger pulse to the Ultrasonic.
 */
static void Ultrasonic_Trigger(void);

/*******************************************************************************
 *                       Static And Global Variables 	                      *
 *******************************************************************************/

static uint8 g_edgeCount = 0;
static uint16 g_timeHigh = 0;


void Ultrasonic_init(void)
{
	/* Create configuration structure for ICU driver */
	ICU_ConfigType ICU_Configurations = {F_CPU_8,RAISING};
	/* Initialize ICU with the choosed parameters */
	ICU_init(&ICU_Configurations);
	/* Setup Ultrasonic sensor Trigger pin as output */
	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,PIN_OUTPUT);
	/* Set the Call back function pointer in the ICU driver */
	ICU_setCallBack(Ultrasonic_edgeProcessing);
}

static void Ultrasonic_Trigger(void)
{
	/* Description :
	 * HSR04 Sensor Needs a high pulse with duration 10us to start
	 * sending its sound waves
	 */
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,LOGIC_LOW);

}

uint16 Ultrasonic_readDistance(void)
{
	/* Initialize distance with 0 */
	uint16 distance=0;
	/* Start Sending UltraSonic waves */
	Ultrasonic_Trigger();
	/* wait until the wave reflects */
	while(g_edgeCount!=2);
	g_edgeCount = 0;
	/* Calculate distance */
	distance = 1 + (g_timeHigh/58);

	return distance;
}

void Ultrasonic_edgeProcessing(void)
{

	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		ICU_clearTimerValue();
		/* Detect falling edge */
		ICU_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		/* Store the High time value */
		g_timeHigh = ICU_getInputCaptureValue();
		/* Detect rising edge */
		ICU_setEdgeDetectionType(RAISING);
		ICU_clearTimerValue();
	}


}

