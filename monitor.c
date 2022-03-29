#include "philos.h"

void *monitor(void *data)
{
    t_philos        *philo;
    struct timeval  now;
    long long       ms;
    const char *state_str[5] = \
		{"is thinking", "has taken a fork", \
		"is eating", "is sleeping", "is dead"};

    philo = (t_philos *)data;
    while(!philo->gameinfo->end && philo->state != DEAD)
    {
        pthread_mutex_lock(&philo->gameinfo->work_mutex);
        gettimeofday(&now, NULL);
        ms = get_time_ms(now) - get_time_ms(philo->recent_eat_time);
        if (ms >= philo->gameinfo->died_time && !philo->gameinfo->end)
        {
            philo->gameinfo->end = 1;
            philo->state = DEAD;
            if (philo->gameinfo->end)
		        printf("ms: %lld index:%d %s\n", ms, philo->index,state_str[DEAD]);
            // print_message_with_ms(philo, DEAD, ms);
        }
        pthread_mutex_unlock(&philo->gameinfo->work_mutex);
    }
    return (NULL);
}