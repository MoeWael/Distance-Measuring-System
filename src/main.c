/*
 * main.c
 *
 *  Created on: ١٤‏/١٠‏/٢٠٢١
 *      Author: Moe
 */

#include <avr/io.h>
#include "ultrasonic.h"
#include "lcd.h"
#include "icu.h"

Icu_ConfigType Config = {F_CPU_8, RISING};

volatile uint8 g_edgeNum = 0;
volatile uint16 g_highTime = 0;
uint16 g_distance = 0;

int main(void){

	SREG |= (1<<7);
	Ultrasonic_init();
	LCD_init();

	while(1){
		g_distance = Ultrasonic_readDistance();
		LCD_moveCursor(0,0);
		LCD_displayString("Distance = ");
		LCD_intgerToString(g_distance);
		LCD_displayString("cm ");
	}
}
