#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#include "philos.h"
#include "utility.h"

extern t_philo_info g_info;

void print_message(t_philo *philo, int type)
{
	struct timeval		now;
	const char			*state_str[] = \
		{"is thinking", "has taken a left fork", \
		"has taken a right fork",
		"is eating", "is sleeping", "is dead"};
	const long long start_time = g_info.start_time;

	// lock sem_print
	ret = sem_wait(philo->sem_print);
	if (ret < 0)
	{
		printf("sem_wait Failed:%d\n", errno);
		return ;
	}

	gettimeofday(&now, NULL);
	if (!g_philo_info.end_flag)
		printf("%-10lldms\tphilos [%3d] %s\n", \
			get_time_ms(now) - start_time, \
			philo->id, state_str[type]);
	
	// unlock sem_print
	ret = sem_post(philo->sem_print);
	if (ret < 0)
	{
		printf("sem_post Failed:%d\n", errno);
		return ;
	}
}

/*
	input : [t_philo *, int]
	output: [TRUE or FALSE]

	This function picks up the fork in the middle of the table.
	Fork is the number of semaphores, and returns 1 in case of success and 0 in case of failure.
*/

int	pick_fork(t_philo *philo, int type)
{
	int ret;

	ret = sem_wait(philo->sem_fork);
	if (ret < 0)
	{
		printf("sem_wait Failed:%d\n", errno);
		return (0);
	}
	print_message(philo, type);
	return (1);
}

/*
	input : [t_philo *]
	output: [TRUE or FALSE]

	This function picks up the fork in the middle of the table.
	Fork is the number of semaphores, and returns 1 in case of success and 0 in case of failure.
*/

int	do_pick_forks(t_philo *philo)
{
	int ret;

	// pick left fork
	ret = pick_fork(philo, PICKING_LEFT_FORK);
	if (ret < 0)
		return (0);
	
	// pick right fork
	ret = pick_fork(philo, PICKING_RIGHT_FORK);
	if (ret < 0)
		return (0);
	return (1);
}
