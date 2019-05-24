
/**
 * @file mysemaphores.cpp
 * @brief This file consists of all the function definitions related to initializing and destroying semaphores.
 * @author Siddhant Jajoo.
 * @date 05/02/2019
 * @copyright Copyright (C) 2019
 * 
 */


#include "../inc/main.h"
#include "../inc/mysemaphores.h"



void sem_init(void)
{
	//Creating Semaphore for Service 1
	if(sem_init (&sem_motor, 0, 0))
	{ 
	 perror("Failed to initialize Service 1 semaphore\n");
	 exit(EXIT_FAILURE);
	}

	//Creating Semaphore for Service 2
	if(sem_init (&sem_ultrasonic, 0, 0))
	{ 
	 perror("Failed to initialize Service 2 semaphore\n");
	 exit(EXIT_FAILURE);
	}

	//Creating Semaphore for Service 3
	if(sem_init (&sem_camera, 0, 0))
	{ 
	 perror("Failed to initialize Service 3 semaphore\n");
	 exit(EXIT_FAILURE);
	}
	
}



void sem_destroy(void)
{
	
}
