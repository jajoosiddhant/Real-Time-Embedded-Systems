

/**
 * @file capture.h
 * @brief Header file for capture.c
 * @author Satya Mehta
 * @date 05/01/2019
 * @copyright Copyright (C) 2019
 * 
 */



#ifndef _CAPTURE_H
#define _CAPTURE_H


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


//************************************************************************//
//								MACROS
//************************************************************************//
#define THRESHOLD_CAM			(20)		/**< Threshold value*/


//************************************************************************//
//						VARIABLE DECLARATIONS
//************************************************************************//
extern uint8_t eventc;


//************************************************************************//
//						FUNCTION DECLARATIONS
//************************************************************************//

/**
 * @brief Initializes the Camera
 * @return void.
 */
void camera_init();


/**
 * @brief Callback Function for Camera Service.
 * @return void.
 */
void *camera_service(void *threadp); 				


void sign_handle(void);
bool compare_threshold_cam(int value);

#endif
