
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
	printf("Hello, Checking for semaphore.\n");
	sem_t *sem;
	
	//Open Semaphore
	sem = sem_open("sem", O_EXCL,0777,0);
	if(sem == NULL)
	{
		perror("ERROR : Semaphore Not created.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Semaphore already created.\n");
	}
	
	printf("Semaphore Blocked.\n");
	
	if(sem_post(sem))
	{
		perror("ERROR : Sem_wait().\n");
		exit(EXIT_FAILURE);
	}
	
	printf("Semaphore Released.\n");
	
	//Unlinking Semaphore
	if(sem_unlink("sem"))
	{
		perror("Cannot Unlink Semaphore.\n");
		exit(EXIT_FAILURE);
	}
	
	//Destroying Semaphore
	if(sem_destroy(sem))
	{
		perror("ERROR : Cannot destroy Semaphore.\n");
		exit(EXIT_FAILURE);
	}
	
	return 0;
}
