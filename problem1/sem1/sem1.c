
/* 
 * Filename: Semaphore Testing
 * Author: Siddhant Jajoo
 * Date: 02/28/2019.
 */


#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

int main()
{
	printf("Hello, Creating Semaphore 1.\n");
	sem_t *sem;
	
	//Creating Semaphore
	sem = sem_open("/sem", O_CREAT,0777,0);
	if(sem == NULL)
	{
		perror("ERROR : Semaphore Not created.\n");
		exit(EXIT_FAILURE);
	}
	
	printf("Semaphore Blocked.\n");
	if(sem_wait(sem))
	{
		perror("ERROR : Sem_wait().\n");
		exit(EXIT_FAILURE);
	}
	
	return 0;
}
