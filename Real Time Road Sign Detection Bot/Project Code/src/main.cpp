
/**
 * @file main.cpp
 * @brief This file consists of main functionality.
 * @author Satya Mehta, Siddhant jajoo, Ayush Dhoot.
 * @date 05/01/2019
 * @see Sam Siewerts Example Code.
 * @copyright Copyright (C) 2019
 * 
 */


#include "../inc/main.h"
#include "../inc/motor.h"
#include "../inc/capture.h"
#include "../inc/ultrasonic_sensor.h"
#include "../inc/mysemaphores.h"
#include "../inc/scheduler.h"


//Declaring Global variables
struct timeval current_time_val;
int i, rc, scope;
cpu_set_t threadcpu;
pthread_t threads[NUM_THREADS];
threadParams_t threadParams[NUM_THREADS];
pthread_attr_t rt_sched_attr[NUM_THREADS];
int rt_max_prio, rt_min_prio;
struct sched_param rt_param[NUM_THREADS];
struct sched_param main_param;
pthread_attr_t main_attr;
pid_t mainpid;



int main( int argc, const char** argv ) 
{ 
	
	
    
    wiringPiSetup();
    
    mainpid=getpid();
    
    //Creates the required Semaphores.
	sem_init();
    
	
    rt_max_prio = sched_get_priority_max(SCHED_FIFO);
    rt_min_prio = sched_get_priority_min(SCHED_FIFO);


	rc = sched_getparam(mainpid, &main_param);
    main_param.sched_priority = rt_max_prio;
    rc = sched_setscheduler(getpid(), SCHED_FIFO, &main_param);
    if(rc < 0) 
    {
	perror("Cannot Set priority of Main thread.\n");
    exit(EXIT_FAILURE);
    }
    
    
    //Printing the set scheduled policy.
    print_scheduler();
    
    pthread_attr_getscope(&main_attr, &scope);
    if(scope == PTHREAD_SCOPE_SYSTEM)
    {
		printf("PTHREAD SCOPE SYSTEM\n");
    }
    else if (scope == PTHREAD_SCOPE_PROCESS)
    {
		printf("PTHREAD SCOPE PROCESS\n");
    }
    else
    {
		printf("PTHREAD SCOPE UNKNOWN\n");
	}
	
    printf("rt_max_prio=%d\n", rt_max_prio);
    printf("rt_min_prio=%d\n", rt_min_prio);
    
    

    // Create Sequencer thread, which like a cyclic executive, is highest prio
    printf("Start Scheduler\n");
    threadParams[0].sequencePeriods=900;	
	

    //Set thread attributes over here.
    set_thread_attr();
	
    //Create Service threads over here.
    create_thread();
	
    //Note Start time of scheduler.
    gettimeofday(&start_time_val, (struct timezone *)0);
    
    //Create Scheduler over here.
    create_scheduler();

    //Joining Threads over here.
    for(i=0;i<NUM_THREADS;i++)
    {
	pthread_join(threads[i], NULL);
    }
	
    return 0; 
} 




void set_thread_attr(void)
{
	int i, rc;
	
	for(i=0; i < NUM_THREADS; i++)
    {

      rc=pthread_attr_init(&rt_sched_attr[i]);
      rc=pthread_attr_setinheritsched(&rt_sched_attr[i], PTHREAD_EXPLICIT_SCHED);
      rc=pthread_attr_setschedpolicy(&rt_sched_attr[i], SCHED_FIFO);
      //rc=pthread_attr_setaffinity_np(&rt_sched_attr[i], sizeof(cpu_set_t), &threadcpu);
	  pthread_attr_setscope(&rt_sched_attr[i], PTHREAD_SCOPE_SYSTEM);
      
	  rt_param[i].sched_priority=rt_max_prio-i;
      pthread_attr_setschedparam(&rt_sched_attr[i], &rt_param[i]);

      threadParams[i].threadIdx=i;
    }
}


void create_thread(void)
{    
    
    // Motor Service = RT_MAX-1
    rt_param[1].sched_priority=rt_max_prio-1;
    pthread_attr_setschedparam(&rt_sched_attr[1], &rt_param[1]);
    rc=pthread_create(&threads[1],               // pointer to thread descriptor
                      &rt_sched_attr[1],         // use specific attributes
                      //(void *)0,               // default attributes
                      motor_service,                 // thread function entry point
                      (void *)&(threadParams[1]) // parameters to pass in
                     );
    if(rc < 0)
    {
        perror("pthread_create for service 1");
    }
    else
    {
        printf("pthread_create successful for service 1\n");
    }
	
	// Ultrasonic Sensor Service = RT_MAX-2	
    rt_param[2].sched_priority=rt_max_prio-2;
    pthread_attr_setschedparam(&rt_sched_attr[2], &rt_param[2]);
    rc=pthread_create(&threads[2], &rt_sched_attr[2], obstacle_service, (void *)&(threadParams[2]));
    if(rc < 0)
    {
        perror("pthread_create for service 2");
    }
    else
    {
        printf("pthread_create successful for service 2\n");
    }

    // Camera Service  = RT_MAX-3	
    rt_param[3].sched_priority=rt_max_prio-3;
    pthread_attr_setschedparam(&rt_sched_attr[3], &rt_param[3]);
    rc=pthread_create(&threads[3], &rt_sched_attr[3], camera_service, (void *)&(threadParams[3]));
    if(rc < 0)
    {
        perror("pthread_create for service 3");
    }
    else
    {
        printf("pthread_create successful for service 3\n");
    }
}


void create_scheduler(void)
{
	 // Sequencer = RT_MAX	@
    rt_param[0].sched_priority=rt_max_prio;
    pthread_attr_setschedparam(&rt_sched_attr[0], &rt_param[0]);
    rc=pthread_create(&threads[0], &rt_sched_attr[0], scheduler, (void *)&(threadParams[0]));
    if(rc < 0)
    {
        perror("Cannot Create Scheduler Thread.\n");
    }
    else
    {
	   printf("Successfully Created Scheduler Thread.\n");
    }
    
}


double getTimeMsec(void)
{
  struct timespec event_ts = {0, 0};

  clock_gettime(CLOCK_MONOTONIC, &event_ts);
  return ((event_ts.tv_sec)*1000.0) + ((event_ts.tv_nsec)/1000000.0);
}


void print_scheduler(void)
{
   int schedType;

   schedType = sched_getscheduler(getpid());

   switch(schedType)
   {
       case SCHED_FIFO:
           printf("Pthread Policy is SCHED_FIFO\n");
           break;
       case SCHED_OTHER:
           printf("Pthread Policy is SCHED_OTHER\n"); exit(-1);
         break;
       case SCHED_RR:
           printf("Pthread Policy is SCHED_RR\n"); exit(-1);
           break;
       default:
           printf("Pthread Policy is UNKNOWN\n"); exit(-1);
   }
}


int delta_t(struct timespec *stop, struct timespec *start, struct timespec *delta_t)
{
  int dt_sec=stop->tv_sec - start->tv_sec;
  int dt_nsec=stop->tv_nsec - start->tv_nsec;

  if(dt_sec >= 0)
  {
    if(dt_nsec >= 0)
    {
      delta_t->tv_sec=dt_sec;
      delta_t->tv_nsec=dt_nsec;
    }
    else
    {
      delta_t->tv_sec=dt_sec-1;
      delta_t->tv_nsec=NSEC_PER_SEC+dt_nsec;
    }
  }
  else
  {
    if(dt_nsec >= 0)
    {
      delta_t->tv_sec=dt_sec;
      delta_t->tv_nsec=dt_nsec;
    }
    else
    {
      delta_t->tv_sec=dt_sec-1;
      delta_t->tv_nsec=NSEC_PER_SEC+dt_nsec;
    }
  }

  return(1);
}









