#include "philos.h"

void *monitor(void *data)
{
    t_philos        *philo;
    struct timeval  now;
    long long       ms;

    philo = (t_philos *)data;
    while(!philo->gameinfo->end)
    {
        pthread_mutex_lock(&philo->gameinfo->work_mutex);
        gettimeofday(&now, NULL);
        ms = get_time_ms(now) - get_time_ms(philo->recent_eat_time);
        if (ms >= philo->gameinfo->died_time)
        {
            philo->gameinfo->end = 1;
            print_message_with_ms(philo, DEAD, ms);
            break;
        }
        pthread_mutex_unlock(&philo->gameinfo->work_mutex);
    }
    return (NULL);
}