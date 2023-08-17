#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#include "philos.h"
#include "utility.h"

extern t_philo_info g_info;

/*
	input : [t_philo *]
	output: [TRUE or FALSE]

	This function picks up the fork in the middle of the table.
	Fork is the number of semaphores, and returns 1 in case of success and 0 in case of failure.
*/

int	do_pick(t_philo *philo)
{
	int ret;

	ret = sem_wait(philo->sem_fork);
	if (ret < 0)
	{
		printf("sem_wait Failed:%d\n", errno);
		return (0);
	}
	printf("pid[%3d] has a fork\n", number);
	ret = sem_wait(philo->sem_fork);
	if (ret < 0)
	{
		printf("sem_wait Failed:%d\n", errno);
		return (0);
	}
	return (1);
}
