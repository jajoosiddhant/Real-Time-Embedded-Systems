

/**
 * @file motor.h
 * @brief Header file for motor.c
 * @author Satya Mehta
 * @date 05/01/2019
 * @copyright Copyright (C) 2019
 * 
 */



#ifndef _MOTOR_H_
#define _MOTOR_H_


#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>
#include <stdio.h>
#include <stdint.h>


//************************************************************************//
//								MACROS
//************************************************************************//
#define AIN1	(7) //RPI 7th
#define AIN2	(0) //RPI 11th
#define BIN1	(1)
#define BIN2	(2)
#define CIN1	(3)
#define CIN2	(4)
#define DIN1	(5)
#define DIN2	(6)

#define PWMA	(30)
#define PWMB	(31)
#define PWMC	(21)
#define PWMD	(22)

#define initialValue 	(0)
#define	pwmRange		(100)


#define ON		(25)
#define OFF		(0)	


//************************************************************************//
//						VARIABLE DECLARATIONS
//************************************************************************//




//************************************************************************//
//						FUNCTION DECLARATIONS
//************************************************************************//

/**
 * @brief Callback function for Motor Task.
 * @return void.
 */
void *motor_service(void *threadp);


/**
 * @brief This function handles the state of motors depending on the values of the event flag.
 * @return void.
 */ 
void handle_motor(void);

/**
 * @brief This function Initializes all the GPIOs required for the Motor Functionality.
 * @return void.
 */
void motor_init();

/**
 * @brief This function moves the bot forward.
 * @return void.
 */
void motor_run_fwd();

/**
 * @brief This function moves the bot in reverse direction.
 * @return void.
 */
void motor_stop_rv();


/**
 * @brief This function stops the bot.
 * @return void.
 */
void motor_stop();


#endif
