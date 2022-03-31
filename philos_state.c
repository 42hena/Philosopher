#include "philos.h"

void	do_pick(t_philos *philoinfo)
{
	pthread_mutex_lock(philoinfo->leftfork);
	print_message(philoinfo, PICKING);
	pthread_mutex_lock(philoinfo->rightfork);
	print_message(philoinfo, PICKING);
}

static void	eating(t_philos *philoinfo)
{
	long long	ms;
	const char	*state_str[5] = \
		{"is thinking", "has taken a fork", \
		"is eating", "is sleeping", "is dead"};

	gettimeofday(&philoinfo->recent_eat_time, NULL);
	ms = get_time_ms(philoinfo->recent_eat_time) - \
	get_time_ms(philoinfo->gameinfo->create_time);
	if (!philoinfo->gameinfo->end)
	{
		printf("%-10lldms\tphilos [%3d] %s\n", \
				ms, philoinfo->index, state_str[EATING]);
		philoinfo->eat_count++;
	}
}

void	do_eat(t_philos *philoinfo)
{
	pthread_mutex_lock(&philoinfo->gameinfo->end_mutex);
	eating(philoinfo);
	pthread_mutex_unlock(&philoinfo->gameinfo->end_mutex);
	sleep_function(philoinfo->gameinfo->eating_time);
	pthread_mutex_unlock(philoinfo->leftfork);
	pthread_mutex_unlock(philoinfo->rightfork);
}

void	do_sleep(t_philos *philoinfo)
{
	print_message(philoinfo, SLEEPING);
	sleep_function(philoinfo->gameinfo->sleeping_time);
}

void	do_think(t_philos *philoinfo)
{
	print_message(philoinfo, THINKING);
}
