#ifndef _PHILOS_H_
#define _PHILOS_H_

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

// print
int	ft_atoi(const char *nptr);
typedef struct s_philos t_philos;
typedef struct s_game
{
    int number_of_philos;
    int eating_time;
    int sleeping_time;
    int died_time;
    int end;
    pthread_mutex_t work_mutex;
    struct timeval  create_time;
    t_philos *philos;
} t_game;

typedef struct s_philos
{
    int index;
    int state;
    int remain_count;
    pthread_mutex_t *leftfork;
    pthread_mutex_t *rightfork;
    pthread_t philo;
    pthread_mutex_t mutex;
    pthread_mutex_t check;
    t_game *gameinfo;
    struct timeval  recent_eat_time;
} t_philos;

void print_message(t_philos *philoinfo, int type);
void print_message_with_ms(t_philos *philoinfo, int type, long long ms);
long long	get_time_ms(struct timeval now);
void do_pick(t_philos *philoinfo);
void do_eat(t_philos *philoinfo);
void do_sleep(t_philos *philoinfo);
void do_think(t_philos *philoinfo);
void sleep_function(int waiting_time);
void *monitor(void *data);
enum philosopher_state
{
    THINKING,
    PICKING,
    EATING,
    SLEEPING,
    DEAD
};
#endif