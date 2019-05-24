
/**
 * @file ultrasonic_sensor.h
 * @brief Header file for ultrasonic_sensor.c
 * @author Siddhant Jajoo
 * @date 05/01/2019
 * @copyright Copyright (C) 2019
 * 
 */




#ifndef INC_ULTRASONIC_SENSOR_H_
#define INC_ULTRASONIC_SENSOR_H_


#include <stdio.h>
#include <stdint.h>
#include <wiringPi.h>
#include <sys/time.h>



#define CALC_DISTANCE_CM(usec)		(usec/58)		/**< Formula to calculate Distance in Centimetres*/
#define CALC_DISTANCE_INCH(usec)	(usec/148)		/**< Formula to calculate Distance in Inch*/

#define TRIGGER 			(27)		/**< GPIO pin for Trigger*/
#define	ECHO				(28)		/**< GPIO pin for Echo*/
#define THRESHOLD			(75)		/**< Threshold value in cm fr Ultrasonic Sensor*/


//Variable Declarations
extern uint8_t eventu;


//Function Declarations

/**
 * @brief This function Initializes the Ultrasonic Sensor.
 * @return void.
 */ 
void ultrasonic_init(void);

/**
 * @brief This function calculated the distance from the object.
 * @param units The units in which the distance is required. Pass 1 for cm and 0 for inch.
 * @return unsigned long The distance of the obstacle from the sensor.
 */
unsigned long calc_distance(uint8_t units);


/**
 * @brief This function compares the obtained distance value with the threshold.
 * @return bool Return 1 ifvalue is below threshld and 0 if value is above threshold.
 */
bool compare_threshold(unsigned long value);


/**
 * @brief This function handles the flags to be set on detection obstacle.
 * @return void.
 */
void obstacle_handle(void);

/**
 * @brief Callback function for Ultrasonic Sensor Service.
 * @return void.
 */
void *obstacle_service(void *threadp);

#endif
