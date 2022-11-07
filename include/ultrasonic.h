 /******************************************************************************
 *
 * Module: Ultrasonic
 *
 * File Name: ultrasonic.h
 *
 * Description: Header file for the AVR Ultrasonic driver
 *
 * Author: Mohammad Wael
 *
 *******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define TRIGGER_PORT PORTB_ID
#define TRIGGER_PIN PIN5_ID

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void Ultrasonic_init(void);
void Ultrasonic_edgeProcessing(void);
uint16 Ultrasonic_readDistance(void);


#endif /* ULTRASONIC_H_ */
