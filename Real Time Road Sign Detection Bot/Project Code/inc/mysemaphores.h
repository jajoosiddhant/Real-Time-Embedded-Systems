
/**
 * @file mysemaphores.h
 * @brief Header file for mysemaphores.c
 * @author Siddhant Jajoo.
 * @date 05/02/2019
 * @copyright Copyright (C) 2019
 * 
 */



#ifndef _MYSEMAPHORES_H_
#define _MYSEMAPHORES_H_

#include <stdio.h>
#include <stdint.h>



//************************************************************************//
//								MACROS
//************************************************************************//


//************************************************************************//
//						VARIABLE DECLARATIONS
//************************************************************************//
extern sem_t sem_motor, sem_ultrasonic, sem_camera;


//************************************************************************//
//						FUNCTION DECLARATIONS
//************************************************************************//

/**
 * @brief This function creates Semaphores required for the Services and the Scheduler.
 * @return void.
 */
void sem_init(void);


/**
 * @brief This function destroys the created Semaphores.
 * @return void.
 */
void sem_destroy(void);

#endif
