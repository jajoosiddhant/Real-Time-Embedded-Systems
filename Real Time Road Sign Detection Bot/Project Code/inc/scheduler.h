
/**
 * @file scheduler.h
 * @brief Header file for scheduler.c
 * @author Siddhant Jajoo, Ayush Dhoot, Satya Mehta.
 * @date 05/02/2019
 * @copyright Copyright (C) 2019
 * 
 */



#ifndef _INC_SCHEDULER_H_
#define _INC_SCHEDULER_H_


#include <stdio.h>
#include <stdint.h>



//************************************************************************//
//								MACROS
//************************************************************************//
#define SCHEDULER_DELAY		()			//Sleeptime for Scheduler.

//************************************************************************//
//						VARIABLE DECLARATIONS
//************************************************************************//


//************************************************************************//
//						FUNCTION DECLARATIONS
//************************************************************************//

/**
 * @brief This function schedules the required task at a particular point of time.
 * @return void.
 */
void *scheduler(void *threadp);


#endif
