

/**
 * @file scheduler.cpp
 * @brief This file consists of all the function definitions related to Scheduler functionality.
 * @author Satya Mehta, Siddhant Jajoo, Ayush Dhoot.
 * @date 05/02/2019
 * @copyright Copyright (C) 2019
 * 
 */

#include "../inc/main.h"
#include "../inc/scheduler.h"
#include "../inc/mysemaphores.h"



struct timeval start_time_val;


void *scheduler(void *threadp)
{
    struct timeval current_time_val;
    struct timespec delay_time = {0,8333333}; // delay for 8.333 msec, 120 Hz
    struct timespec remaining_time;
    double current_time;
    double residual;
    int rc, delay_cnt=0;
    unsigned long long seqCnt=0;
    threadParams_t *threadParams = (threadParams_t *)threadp;

    gettimeofday(&current_time_val, (struct timezone *)0);
    syslog(LOG_CRIT, "Scheduler thread @ sec=%d, msec=%d\n", (int)(current_time_val.tv_sec-start_time_val.tv_sec), (int)current_time_val.tv_usec/USEC_PER_MSEC);
    printf("Scheduler thread @ sec=%d, msec=%d\n", (int)(current_time_val.tv_sec-start_time_val.tv_sec), (int)current_time_val.tv_usec/USEC_PER_MSEC);

    do
    {
        delay_cnt=0; residual=0.0;
            gettimeofday(&current_time_val, (struct timezone *)0);
            syslog(LOG_CRIT, "Sequencer thread prior to delay @ sec=%d, msec=%d\n", (int)(current_time_val.tv_sec-start_time_val.tv_sec), (int)current_time_val.tv_usec/USEC_PER_MSEC);
        do
        {
            rc=nanosleep(&delay_time, &remaining_time);

            if(rc == EINTR)
            { 
                residual = remaining_time.tv_sec + ((double)remaining_time.tv_nsec / (double)NANOSEC_PER_SEC);

                if(residual > 0.0) printf("residual=%lf, sec=%d, nsec=%d\n", residual, (int)remaining_time.tv_sec, (int)remaining_time.tv_nsec);
 
                delay_cnt++;
            }
            else if(rc < 0)
            {
               
                perror("Scheduler nanosleep");
                exit(-1);
            }
           
        } while((residual > 0.0) && (delay_cnt < 100));

        seqCnt++;
        gettimeofday(&current_time_val, (struct timezone *)0);
        syslog(LOG_CRIT, "Scheduler cycle %llu @ sec=%d, msec=%d\n", seqCnt, (int)(current_time_val.tv_sec-start_time_val.tv_sec), (int)current_time_val.tv_usec/USEC_PER_MSEC);


        if(delay_cnt > 1) printf("Scheduler looping delay %d\n", delay_cnt);


        // Release each service at a sub-rate of the generic sequencer rate

        // Motor Service = RT_MAX-1	@ 30 Hz
        if((seqCnt % 4) == 0)
        {
            sem_post(&sem_motor);
        }
        
        // Ultrasonic Service = RT_MAX-2	@ 4 Hz
        if((seqCnt % 30) == 0)
        {
            sem_post(&sem_ultrasonic);
        }
        
        // Camera Service = RT_MAX-3	@ 3 Hz
        if((seqCnt % 40) == 0)
        {
            sem_post(&sem_camera);
        }
        

        gettimeofday(&current_time_val, (struct timezone *)0);
        syslog(LOG_CRIT, "Sequencer release all sub-services @ sec=%d, msec=%d\n", (int)(current_time_val.tv_sec-start_time_val.tv_sec), (int)current_time_val.tv_usec/USEC_PER_MSEC);

    } while(1);//!abort_test && (seqCnt < threadParams->sequencePeriods));

    
    pthread_exit((void *)0);
}

