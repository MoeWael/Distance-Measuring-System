 /******************************************************************************
 *
 * Module: Ultrasonic
 *
 * File Name: ultrasonic.c
 *
 * Description: Source file for the AVR Ultrasonic driver
 *
 * Author: Mohammad Wael
 *
 *******************************************************************************/


#include "ultrasonic.h"
#include "gpio.h"
#include "icu.h"
#include <util/delay.h>


void Ultrasonic_init(void){
	/* Initialize the ICU
	 * Set Callback function to the required function
	 * Setup Trigger pin direction to output
	 */
	Icu_init(&Config);
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(TRIGGER_PORT,TRIGGER_PIN,PIN_OUTPUT);
}

void Ultrasonic_Trigger(void){

	/* Send a 10us pulse to the Ultrasonic trigger
	 * to start sending the echo pulses
	 */
	GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void){

	/* Use trigger function to start sending echo pulses
	 * Return the distance measured
	 */
	Ultrasonic_Trigger();
	return (g_highTime /58);
}

void Ultrasonic_edgeProcessing(void){
	/* Callback function for the ICU
	 *  Increment the number of detected edges each time
	 *  this callback function is called */
	g_edgeNum++;

	if(g_edgeNum == 1){
		/* Rising edge is detected
		 * Set Detection type to falling
		 * Clear timer value to start measuring high time
		 */
		Icu_setEdgeDetectionType(FALLING);
		Icu_clearTimerValue();

	}
	if(g_edgeNum == 2){
		/* Falling edge is detected
		 * Capture the timer value and save it
		 * Reset the edges counter
		 * Set Detection type to Rising
		 */
		g_highTime = Icu_getInputCaptureValue();
		g_edgeNum = 0;
		Icu_setEdgeDetectionType(RISING);
	}

}
