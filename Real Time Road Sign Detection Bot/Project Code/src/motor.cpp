
/**
 * @file motor.cpp
 * @brief This file consists of all the function definitions related to Motor functionality.
 * @author Satya Mehta
 * @date 05/01/2019
 * @see https://projects.drogon.net/raspberry-pi/wiringpi/
 * @copyright Copyright (C) 2019
 * 
 */

#include "../inc/main.h"
#include "../inc/motor.h"
#include "../inc/mysemaphores.h"
#include "../inc/ultrasonic_sensor.h"

sem_t sem_motor;

uint8_t eventu;
uint8_t eventc;


void *motor_service(void *threadp)
{
	struct timespec start = {0,0};
	struct timespec stop = {0,0};
	struct timespec wcet = {0,0};
	unsigned long motor_service_count = 0;
	eventc = 0;
	eventu = 0;
	
    printf("In Motor service\n");
    motor_init();
    
    
	while(1)//!abort_motor)
	{
		sem_wait(&sem_motor);
		clock_gettime(CLOCK_REALTIME, &start);
		
		
		//Fill Motor Functions over here.
		handle_motor();
		
		
		clock_gettime( CLOCK_REALTIME, &stop);
		
		
		delta_t(&stop, &start, &wcet);
		motor_service_count++;
		syslog(LOG_CRIT, "Motor service count = %lu , timestamp: %lu sec, %lu msec (%lu microsec), ((%lu nanosec))\n\n", motor_service_count, wcet.tv_sec, (wcet.tv_nsec / NSEC_PER_MSEC), (wcet.tv_nsec / NSEC_PER_MICROSEC),wcet.tv_nsec);
        
	}
}


void handle_motor(void)
{
	if (eventc | eventu)
	{
		motor_stop();
		delay(5);	
			
	}
	else
	{
		motor_run_fwd();
	}
}




void motor_init()
{
	//wiringPiSetup();
	
	pinMode(AIN1, OUTPUT);
	pinMode(AIN2, OUTPUT);
	pinMode(BIN1, OUTPUT);
	pinMode(BIN2, OUTPUT);

	pinMode(PWMA, OUTPUT);
	pinMode(PWMB, OUTPUT);

	
	softPwmCreate(PWMA, initialValue, pwmRange);
	softPwmCreate(PWMB, initialValue, pwmRange);

	softPwmWrite(PWMA, ON);
	softPwmWrite(PWMB, ON);
	printf("Motor Initialized\n\r");
}

void motor_run_fwd()
{
	//printf("Motor in Forward Motion\n\r");
	
	softPwmWrite(PWMA, ON);	
		
	digitalWrite(AIN1, HIGH);
	digitalWrite(AIN2, LOW);
	digitalWrite(BIN1, HIGH);
	digitalWrite(BIN2, LOW);
	
}


void motor_stop_rv()
{
	//printf("Motor in Reverse Motion\n\r");
	softPwmWrite(PWMA, ON);
	
	digitalWrite(AIN1, LOW);
	digitalWrite(AIN2, HIGH);
	digitalWrite(BIN1, LOW);
	digitalWrite(BIN2, HIGH);
}


void motor_stop()
{
	//printf("Motor in No Motion\n\r");
	softPwmWrite(PWMA, OFF);
	digitalWrite(AIN1, LOW);
	digitalWrite(AIN2, LOW);
	digitalWrite(BIN1, LOW);
	digitalWrite(BIN2, LOW);

}
