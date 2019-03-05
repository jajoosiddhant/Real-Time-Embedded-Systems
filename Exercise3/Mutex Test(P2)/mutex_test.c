/* 
 * Filename: Mutex_test
 * Author: Siddhant Jajoo
 * Description: This code uses a RT-Linux Pthreads that does a thread safe update 
 * of a complex state with a timestamp. The code consistes of two threads : 
 * One thread updates the time and double precision elements in a structure.
 * The other thread reads the timestamped values without the possibility of data corruption.  
 * Date: 03/08/2019.
 */


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>


#define CALC_FLOAT_VALUE		(((float)rand()/(float)(RAND_MAX)) * 5.0)	//Generates a Random Number between 0 and 5

//Function Declarations
void *update_data(void *threadp);
void *read_data(void *threadp);

//Gobal Declarations
pthread_t update_thread, read_thread;
pthread_mutex_t mute;


//Struct Declaration
struct data_time
{
	struct timespec update_time;
	double acc_x;
	double acc_y;
	double acc_z;
	double roll;
	double pitch;
	double yaw;
};

int main()
{
	struct data_time data_time;				//Local Structure Object
	srand(time(0));							//Initializing Seed Value
		
	printf("\n******Testing Mutex*******\n");
	
	memset(&data_time, 0, sizeof(data_time));
	printf("\nInitializing Values....\n");
	printf("Timestamp : %ld Seconds and %ld Nano-seconds.\n", data_time.update_time.tv_sec, data_time.update_time.tv_nsec);
	printf("Acc_x = %f.\n", data_time.acc_x);
	printf("Acc_y = %f.\n", data_time.acc_y);
	printf("Acc_z = %f.\n", data_time.acc_z);
	printf("Roll = %f.\n", data_time.roll);
	printf("Pitch = %f.\n", data_time.pitch);
	printf("Yaw = %f.\n", data_time.yaw); 
	
	if(pthread_mutex_init(&mute, NULL))
	{
		perror("ERROR : pthread_mutex_init(), Mutex Initialization Failed.\n");
		exit(EXIT_FAILURE);
	}
	
	//Creating Threads
	if(pthread_create(&update_thread, NULL , update_data, (void *)&data_time))
	{
		perror("ERROR : pthread_create(), Thread 1 Creation Failed.\n");
		exit(EXIT_FAILURE);
	}
	
	if(pthread_create(&read_thread, NULL , read_data, (void *)&data_time))
	{
		perror("ERROR : pthread_create(), Thread 2 Creation Failed.\n");
		exit(EXIT_FAILURE);
	}
	
	//Waiting for threads to complete
	if(pthread_join(update_thread,NULL))
	{
		perror("ERROR : pthread_join(), Thread 1.\n");
		exit(EXIT_FAILURE);
	}
	
	if(pthread_join(read_thread,NULL))
	{
		perror("ERROR : pthread_join(), Thread 2.\n");
		exit(EXIT_FAILURE);
	}
	
	//Destroying Mutex
	if(pthread_mutex_destroy(&mute))
	{
		perror("ERROR : pthread_mutex_destroy, Cannot destroy Mutex.\n");
		exit(EXIT_FAILURE);
	}
	
	return 0;
}


/*
 * Thread 1 Starting function.
 * This function updates random data to the structure using rand() function.
 */ 
void *update_data(void *threadp)
{	
	struct data_time *data_time = (struct data_time *)threadp;
	printf("\nUpdating Data.....\n");
	pthread_mutex_lock(&mute);
	clock_gettime(CLOCK_REALTIME, &(data_time->update_time));
	data_time->acc_x = CALC_FLOAT_VALUE;
	data_time->acc_y = CALC_FLOAT_VALUE;
	data_time->acc_z = CALC_FLOAT_VALUE;
	data_time->roll = CALC_FLOAT_VALUE;
	data_time->pitch = CALC_FLOAT_VALUE;
	data_time->yaw = CALC_FLOAT_VALUE;
	
	printf("Update Values:\n");
	printf("Timestamp : %ld Seconds and %ld Nano-seconds.\n", data_time->update_time.tv_sec, data_time->update_time.tv_nsec);
	printf("Acc_x = %f.\n", data_time->acc_x);
	printf("Acc_y = %f.\n", data_time->acc_y);
	printf("Acc_z = %f.\n", data_time->acc_z);
	printf("Roll = %f.\n", data_time->roll);
	printf("Pitch = %f.\n", data_time->pitch);
	printf("Yaw = %f.\n", data_time->yaw); 
	pthread_mutex_unlock(&mute);
	
}

/*
 * Thread 2 Starting function.
 * This function reads random data from the structure.
 */ 
void *read_data(void *threadp)
{
	sleep(1);
	struct data_time *data_time = (struct data_time *)threadp;
	printf("\nReading Data.....\n");
	pthread_mutex_lock(&mute);
	printf("Update Values:\n");
	printf("Timestamp : %ld Seconds and %ld Nano-seconds.\n", data_time->update_time.tv_sec, data_time->update_time.tv_nsec);
	printf("Acc_x = %f.\n", data_time->acc_x);
	printf("Acc_y = %f.\n", data_time->acc_y);
	printf("Acc_z = %f.\n", data_time->acc_z);
	printf("Roll = %f.\n", data_time->roll);
	printf("Pitch = %f.\n", data_time->pitch);
	printf("Yaw = %f.\n", data_time->yaw); 
	pthread_mutex_unlock(&mute);
}
