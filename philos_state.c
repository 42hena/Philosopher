#include "philos.h"

void do_pick(t_philos *philoinfo)
{
	pthread_mutex_lock(&(*(philoinfo->leftfork)));
	philoinfo->state = PICKING;
	print_message(philoinfo, philoinfo->state);
	pthread_mutex_lock(&(*(philoinfo->rightfork)));
	print_message(philoinfo, philoinfo->state);
}

void do_eat(t_philos *philoinfo)
{
	struct timeval	now;
	long long	ms;
	
	pthread_mutex_lock(&philoinfo->gameinfo->work_mutex);
	pthread_mutex_lock(&philoinfo->check);
	philoinfo->state = EATING;
	gettimeofday(&now, NULL);
	ms = get_time_ms(now) - get_time_ms(philoinfo->recent_eat_time);
	if (!philoinfo->gameinfo->end)
	{
		print_message(philoinfo, philoinfo->state);
	}
	usleep(philoinfo->gameinfo->eating_time * 1000);
	pthread_mutex_unlock(&(*(philoinfo->leftfork)));
	pthread_mutex_unlock(&(*(philoinfo->rightfork)));
	// pthread_mutex_unlock(&philoinfo->gameinfo->work_mutex);
	pthread_mutex_unlock(&philoinfo->check);
	pthread_mutex_unlock(&philoinfo->gameinfo->work_mutex);
	gettimeofday(&philoinfo->recent_eat_time, NULL);
}

void do_sleep(t_philos *philoinfo)
{
	philoinfo->state = SLEEPING;
	print_message(philoinfo, philoinfo->state);
	usleep(philoinfo->gameinfo->sleeping_time * 1000);
}

void do_think(t_philos *philoinfo)
{
	philoinfo->state = THINKING;
	print_message(philoinfo, philoinfo->state);
}