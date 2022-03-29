#include "philos.h"

void print_message_with_ms(t_philos *philoinfo, int type, long long ms)
{
	const char *state_str[5] = \
		{"is thinking", "has taken a fork", \
		"is eating", "is sleeping", "is dead"};
	pthread_mutex_lock(&philoinfo->gameinfo->work_mutex);
	if (!philoinfo->gameinfo->end)
		printf("ms: %lld index:%d %s\n", ms, philoinfo->index,state_str[type]);
	pthread_mutex_unlock(&philoinfo->gameinfo->work_mutex);
}

void print_message(t_philos *philoinfo, int type)
{
	struct timeval		now;
	const char *state_str[5] = \
		{"is thinking", "has taken a fork", \
		"is eating", "is sleeping", "is dead"};

	pthread_mutex_lock(&philoinfo->gameinfo->work_mutex);
	gettimeofday(&now, NULL);
	if (!philoinfo->gameinfo->end)
		printf("ms: %lld index:%d %s\n", get_time_ms(now) - get_time_ms(philoinfo->gameinfo->create_time), philoinfo->index,state_str[type]);
	pthread_mutex_unlock(&philoinfo->gameinfo->work_mutex);
}