#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>

#include "utility.h"
#include "philos.h"

t_dining_info g_dining_info;

void init_dining_info(int argc, char **argv)
{
	g_dining_info.number_of_philos = atoi(argv[1]);
	g_dining_info.died_time = atoi(argv[2]);
	g_dining_info.eating_time = atoi(argv[3]);
	g_dining_info.sleeping_time = atoi(argv[4]);
	g_dining_info.must_eat_count = -1;
	if (argc == 6)
		g_dining_info.must_eat_count = atoi(argv[5]);
	g_dining_info.end_flag = 0;
	g_dining_info.philo_list = (t_philo *)malloc(sizeof(t_philo) * g_dining_info.number_of_philos);

	// create print_mutex
	pthread_mutex_init(&g_dining_info.print_mutex, NULL);
}

void	init_philos(int argc, char **argv)
{
	struct timeval now_time;
	int	i;

	gettimeofday(&now_time, NULL);
	for (i = 0 ; i < g_dining_info.number_of_philos ; ++i)
	{
		g_dining_info.philo_list[i].recent_eat_time = now_time;
		g_dining_info.philo_list[i].id = i + 1;
		g_dining_info.philo_list[i].leftfork = &g_dining_info.philo_list[i].mutex;
		g_dining_info.philo_list[i].rightfork = &g_dining_info.philo_list[(i + 1) % \
									g_dining_info.number_of_philos].mutex;
		g_dining_info.philo_list[i].eat_count = 0;

		// create fork mutex
		pthread_mutex_init(&g_dining_info.philo_list[i].mutex, NULL);
	}
	g_dining_info.start_time = get_time_ms(now_time);
}

// check function
void print_limit_info()
{
	printf("number_of_philos:%d\n"
			"died_time       :%d\n"
			"eating_time     :%d\n"
			"sleeping_time   :%d\n"
			"must_eat_count  :%d\n\n",
		g_dining_info.number_of_philos,
		g_dining_info.died_time,
		g_dining_info.eating_time,
		g_dining_info.sleeping_time,
		g_dining_info.must_eat_count
		);
}

void print_philo_data()
{
	int i;

	for (i = 0 ; i < g_dining_info.number_of_philos ; ++i)
	{
		printf("philo id       :%d\n"
				"recent_eat_time:%d %d\n"
				"left  fork     :%p\n"
				"right fork     :%p\n"
				"eat_count      :%d\n\n",
			g_dining_info.philo_list[i].id,
			g_dining_info.philo_list[i].recent_eat_time.tv_sec,
			g_dining_info.philo_list[i].recent_eat_time.tv_usec,
			g_dining_info.philo_list[i].leftfork,
			g_dining_info.philo_list[i].rightfork,
			g_dining_info.philo_list[i].eat_count
		);
	}
}