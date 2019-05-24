

/**
 * @file ultrasonic_sensor.h
 * @brief This file consists of all the function definitions related to Ultrasonic Sensor functionality.
 * @author Siddhant Jajoo
 * @date 05/01/2019
 * @copyright Copyright (C) 2019
 * 
 */



#include "../inc/main.h"
#include "../inc/ultrasonic_sensor.h"
#include "../inc/motor.h"


sem_t sem_ultrasonic;


void *obstacle_service(void *threadp)
{
	struct timespec start = {0,0};
	struct timespec stop = {0,0};
	struct timespec wcet = {0,0};
	unsigned long obstacle_service_count = 0;
	
    printf("In Obstacle service\n");
    fflush(stdout);
    
    ultrasonic_init();
    
	while(1)//!abort_motor)
	{
		sem_wait(&sem_ultrasonic);
		clock_gettime(CLOCK_REALTIME, &start);
		
		
		//Fill Ultrasonic Functions over here.
		obstacle_handle();
		
		
		clock_gettime( CLOCK_REALTIME, &stop);
		
		
		delta_t(&stop, &start, &wcet);
		obstacle_service_count++;
		syslog(LOG_CRIT, "Ultrasonic service count = %lu , timestamp: %lu sec, %lu msec (%lu microsec), ((%lu nanosec))\n\n", obstacle_service_count, wcet.tv_sec, (wcet.tv_nsec / NSEC_PER_MSEC), (wcet.tv_nsec / NSEC_PER_MICROSEC),wcet.tv_nsec);
        
	}
}
	

void ultrasonic_init(void)
{
	//wiringPiSetup();
	
	//Configure Trigger and Echo pins as Output and Input Types respectively.
	pinMode(TRIGGER, OUTPUT);
	pinMode(ECHO,INPUT);
	
}

unsigned long calc_distance(uint8_t units)
{
	struct timeval start;
	struct timeval stop;

	unsigned long sec;
	unsigned long usec;
	unsigned long distance = 1;
		
	//Pulling the Trigger Pin High.
	digitalWrite(TRIGGER, HIGH);
	
	//Inserting 10us Delay
	delayMicroseconds(10);
	
	//Pulling the Trigger Pin Low.
	digitalWrite(TRIGGER, LOW);

	//Wait here till the Echo pin is low.
	while(!digitalRead(ECHO));

	//Note the start time
	gettimeofday(&start, NULL);
	
	//Wait here till the Echo pin is high.
	while(digitalRead(ECHO));	

	//Note the end time	
	gettimeofday(&stop, NULL);	

	sec = stop.tv_sec - start.tv_sec;
	usec = stop.tv_usec - start.tv_usec;

	//printf("Time in Seconds: %lu Microseconds: %lu.\n", sec, usec);
		
	if(units)
	{
	distance = CALC_DISTANCE_CM(usec);
	//printf("Distance: %lu cm.\n", distance);

	}
	else
	{
	distance = CALC_DISTANCE_INCH(usec);
	//printf("Distance: %lu inch.\n", distance);

	}
	
		
	return distance;
	
}


bool compare_threshold(unsigned long value)
{

	if(value < THRESHOLD)
	{
		return 1;
	}
	else 
	{
		return 0;
	} 
}



void obstacle_handle(void)
{
	
	if(compare_threshold(calc_distance(1)))
	{
		//printf("Stop Motor.\n");
		
		//Raise Flag to Stop Motor.
		eventu = OBSTACLE_DETECTED;
	}
	else
	{
		//printf("Do Nothing in Obstacle Handle.\n");
		eventu = OBSTACLE_NOT_DETECTED;
	}
}
