#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#include "philos.h"
#include "utility.h"

extern t_dining_info g_dining_info;



void	print_message(t_philo *philoinfo, int type)
{
	struct timeval		now;
	const char			*state_str[] = \
		{"is thinking", "has taken a left fork", \
		"has taken a right fork",
		"is eating", "is sleeping", "is dead"};
	const long long start_time = g_dining_info.start_time;


	pthread_mutex_lock(&g_dining_info.print_mutex);
	gettimeofday(&now, NULL);
	if (!g_dining_info.end_flag)
		printf("%-10lldms\tphilos [%3d] %s\n", \
			get_time_ms(now) - start_time, \
			philoinfo->id, state_str[type]);
	pthread_mutex_unlock(&g_dining_info.print_mutex);
}

void	do_pick(t_philo *philoinfo)
{
	pthread_mutex_lock(philoinfo->leftfork);
	print_message(philoinfo, PICKING_LEFT_FORK);
	pthread_mutex_lock(philoinfo->rightfork);
	print_message(philoinfo, PICKING_RIGHT_FORK);
}

void	eating(t_philo *philoinfo)
{
	long long	ms;
	
	gettimeofday(&philoinfo->recent_eat_time, NULL);
	// ms = get_time_ms(philoinfo->recent_eat_time);
	//  - get_time_ms(g_dining_info.create_time);
	if (!g_dining_info.end_flag)
	{
		print_message(philoinfo, EATING);
		philoinfo->eat_count++;
	}
}

void	do_eat(t_philo *philoinfo)
{
	eating(philoinfo);
	run_sleep(g_dining_info.eating_time);
	pthread_mutex_unlock(philoinfo->leftfork);
	pthread_mutex_unlock(philoinfo->rightfork);
}

void	do_sleep(t_philo *philoinfo)
{
	print_message(philoinfo, SLEEPING);
	run_sleep(g_dining_info.sleeping_time);
}

void	do_think(t_philo *philoinfo)
{
	print_message(philoinfo, THINKING);
}
