

/**
 * @file main.h
 * @brief Header file for main.c
 * @author Siddhant Jajoo, Ayush Dhoot, Satya Mehta.
 * @date 05/01/2019
 * @copyright Copyright (C) 2019
 * 
 */




#ifndef _MAIN_H_
#define _MAIN_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <time.h>
#include <semaphore.h>
#include <syslog.h>
#include <sys/time.h>
#include <errno.h>



//************************************************************************//
//								MACROS
//************************************************************************//
#define NSEC_PER_SEC (1000000000)
#define NSEC_PER_MSEC (1000000)
#define NSEC_PER_MICROSEC (1000)
#define USEC_PER_MSEC (1000)
#define NANOSEC_PER_SEC (1000000000)
#define NUM_CPU_CORES (1)
#define NUM_THREADS (4)
//#define FALSE (0)
//#define TRUE (1)

#define MOTOR_ON(y)       (y | 0x01)
#define MOTOR_OFF(y)      (y & 0xFE)
#define MOTOR_OFF_MASK(y) (y & 0x01)
#define MOTOR_ON_MASK(y)  (y & 0x01)


#define YIELD_DETECTED    (1)
#define NO_SIGN_DETECTED  (0)

#define OBSTACLE_DETECTED (1)
#define OBSTACLE_NOT_DETECTED (0)

//************************************************************************//
//						VARIABLE DECLARATIONS
//************************************************************************//
typedef struct
{
    int threadIdx;
    unsigned long long sequencePeriods;
}threadParams_t;


extern struct timeval start_time_val;

//extern int abort_test;
//extern int abort_motor; 
//extern int abort_ultrasonic; 
//extern int abort_camera;



//************************************************************************//
//						FUNCTION DECLARATIONS
//************************************************************************//

/**
 * @brief This function sets the required attributes for the threads to be created.
 * @return void.
 */
void set_thread_attr(void);


/**
 * @brief This function creates the scheduler thread and the 3 service threads.
 * @return void.
 */
void create_thread(void);


/**
 * @brief This function creates a scheduler task.
 * @return void.
 */
void create_scheduler(void);


/**
 * @brief This function prints the scheduling policy in use.
 * @return void.
 */
void print_scheduler(void);


/**
 * @brief Gets time in milliseconds.
 * @return void.
 */
double getTimeMsec(void);



int delta_t(struct timespec *stop, struct timespec *start, struct timespec *delta_t);

#endif
