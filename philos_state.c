#include "philos.h"

void do_pick(t_philos *philoinfo)
{
	pthread_mutex_lock(philoinfo->leftfork);
	philoinfo->state = PICKING;
	print_message(philoinfo, philoinfo->state);
	pthread_mutex_lock(philoinfo->rightfork);
	print_message(philoinfo, philoinfo->state);
}

void do_eat(t_philos *philoinfo)
{
	long long	ms;
	const char *state_str[5] = \
		{"is thinking", "has taken a fork", \
		"is eating", "is sleeping", "is dead"};

	philoinfo->state = EATING;
	gettimeofday(&philoinfo->recent_eat_time, NULL);
	ms = get_time_ms(philoinfo->recent_eat_time) - get_time_ms(philoinfo->gameinfo->create_time);
	pthread_mutex_lock(&philoinfo->gameinfo->work_mutex);
	if (!philoinfo->gameinfo->end)
	{
		printf("ms: %lld index:%d %s\n", ms, philoinfo->index,state_str[philoinfo->state]);
	}
	pthread_mutex_unlock(&philoinfo->gameinfo->work_mutex);

	// usleep(philoinfo->gameinfo->eating_time * 1000);
	sleep_function(philoinfo->gameinfo->eating_time);

	pthread_mutex_unlock(philoinfo->leftfork);
	pthread_mutex_unlock(philoinfo->rightfork);
}

void do_sleep(t_philos *philoinfo)
{
	philoinfo->state = SLEEPING;
	print_message(philoinfo, philoinfo->state);
	
	usleep(philoinfo->gameinfo->sleeping_time * 1000);
	//sleep_function(philoinfo->gameinfo->sleeping_time);
}

void do_think(t_philos *philoinfo)
{
	philoinfo->state = THINKING;
	print_message(philoinfo, philoinfo->state);
}