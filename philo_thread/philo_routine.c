#include <unistd.h> //time
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

#include "philos.h"
#include "philo_state.h"
#include "utility.h"

#define TRUE 1
#define FALSE 0

extern t_dining_info g_dining_info;

void *philo_routine_thread(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;

	if (philo->id % 2 == 0)
	{
		usleep(g_dining_info.eating_time * 1000);
		// run_sleep(g_dining_info.eating_time);
	}

	while (!g_dining_info.end_flag)
	{
		do_pick(philo);
		do_eat(philo);
		do_sleep(philo);
		do_think(philo);
	}	
	return (0);
}

void monitor_philos()
{
	int i;
	int philo_number;

	long long timestamp;
	const long long start_time = g_dining_info.start_time;
	philo_number = g_dining_info.number_of_philos;
	
	timestamp = get_now_ms();
	for (i = 0 ; i < philo_number ; ++i)
	{	
		if (!g_dining_info.end_flag&& (timestamp - get_time_ms(g_dining_info.philo_list[i].recent_eat_time)) >= g_dining_info.died_time)
		{
			g_dining_info.end_flag = TRUE;
			pthread_mutex_lock(&g_dining_info.print_mutex);
			printf("%lld msphilo id:%d Died\n", timestamp - start_time, i + 1);
			pthread_mutex_unlock(&g_dining_info.print_mutex);
			break ;
		}
	}
}

void begin_philosopher_routines()
{
	int i;
	int philo_number;

	philo_number = g_dining_info.number_of_philos;

	printf("Philosopher problem start\n");
	for (i = 0 ; i < philo_number ; ++i)
	{
		pthread_create(&(g_dining_info.philo_list[i].philo), \
		NULL, philo_routine_thread, (void *)&g_dining_info.philo_list[i]);
		pthread_detach(g_dining_info.philo_list[i].philo);
	}
	
	while (!g_dining_info.end_flag)
	{
		monitor_philos();
	}

	for (i = 0 ; i < philo_number ; ++i)
	{
		pthread_join(g_dining_info.philo_list[i].philo, NULL);
	}

	printf("Philosopher problem end\n");
}
