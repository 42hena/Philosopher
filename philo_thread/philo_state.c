#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#include "philos.h"
#include "utility.h"

extern t_dining_info g_dining_info;



void	print_message(t_philo *philo, int type)
{
	struct timeval		now;
	const char			*state_str[] = \
		{"is thinking", "has taken a left fork", \
		"has taken a right fork",
		"is eating", "is sleeping", "is dead"};
	const long start_time = g_dining_info.start_time;


	pthread_mutex_lock(&g_dining_info.print_mutex);
	gettimeofday(&now, NULL);
	if (!g_dining_info.end_flag)
		printf("%-10ldms\tphilos [%3d] %s\n", \
			get_time_ms(now) - start_time, \
			philo->id, state_str[type]);
	pthread_mutex_unlock(&g_dining_info.print_mutex);
}

void	do_pick(t_philo *philo)
{
	pthread_mutex_lock(philo->leftfork);
	print_message(philo, PICKING_LEFT_FORK);
	pthread_mutex_lock(philo->rightfork);
	print_message(philo, PICKING_RIGHT_FORK);
}

void	eating(t_philo *philo)
{
	const char			*state_str[] = \
		{"is thinking", "has taken a left fork", \
		"has taken a right fork",
		"is eating", "is sleeping", "is dead"};
	long	ms;
	const long start_time = g_dining_info.start_time;
	

	pthread_mutex_lock(&g_dining_info.print_mutex);
	gettimeofday(&philo->recent_eat_time, NULL);
	if (!g_dining_info.end_flag)
	{
		// print_message(philo, EATING);
		printf("%-10ldms\tphilos [%3d] %s\n", \
			get_time_ms(philo->recent_eat_time) - start_time, \
			philo->id, state_str[EATING]);
		philo->eat_count++;
	}

	pthread_mutex_unlock(&g_dining_info.print_mutex);
}

void	do_eat(t_philo *philo)
{
	eating(philo);
	run_sleep(g_dining_info.eating_time);
	pthread_mutex_unlock(philo->leftfork);
	pthread_mutex_unlock(philo->rightfork);
}

void	do_sleep(t_philo *philo)
{
	print_message(philo, SLEEPING);
	run_sleep(g_dining_info.sleeping_time);
}

void	do_think(t_philo *philo)
{
	print_message(philo, THINKING);
}
