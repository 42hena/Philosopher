#include "philos.h"

void print_message_with_ms(t_philos *philoinfo, int type, long long ms)
{
	const char *state_str[5] = \
		{"is thinking", "has taken a fork", \
		"is eating", "is sleeping", "is dead"};

	printf("ms: %lld index:%d %s\n", ms - get_time_ms(philoinfo->gameinfo->create_time), philoinfo->index,state_str[type]);
	
}

void print_message(t_philos *philoinfo, int type)
{
	struct timeval		now;
	const char *state_str[5] = \
		{"is thinking", "has taken a fork", \
		"is eating", "is sleeping", "is dead"};

	gettimeofday(&now, NULL);
	printf("ms: %lld index:%d %s\n", get_time_ms(now) - get_time_ms(philoinfo->gameinfo->create_time), philoinfo->index,state_str[type]);
}