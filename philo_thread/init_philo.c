#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>

#include "utility.h"
#include "philos.h"

t_philo_info g_philo_info;

void init_limit_info(int argc, char **argv)
{
	g_philo_info.number_of_philos = atoi(argv[1]);
	g_philo_info.died_time = atoi(argv[2]);
	g_philo_info.eating_time = atoi(argv[3]);
	g_philo_info.sleeping_time = atoi(argv[4]);
	g_philo_info.must_eat_count = -1;
	if (argc == 6)
		g_philo_info.must_eat_count = atoi(argv[5]);
	g_philo_info.end_flag = 0;
	g_philo_info.philo_list = (t_philo *)malloc(sizeof(t_philo) * g_philo_info.number_of_philos);
}

void	init_philos(int argc, char **argv)
{
	struct timeval now_time;
	int	i;

	gettimeofday(&now_time, NULL);
	for (i = 0 ; i < g_philo_info.number_of_philos ; ++i)
	{
		g_philo_info.philo_list[i].recent_eat_time = now_time;
		g_philo_info.philo_list[i].id = i + 1;
		g_philo_info.philo_list[i].leftfork = &g_philo_info.philo_list[i].mutex;
		g_philo_info.philo_list[i].rightfork = &g_philo_info.philo_list[(i + 1) % \
									g_philo_info.number_of_philos].mutex;
		g_philo_info.philo_list[i].eat_count = 0;
	}
	g_philo_info.start_time = get_time_ms(now_time);
}

// check function
void print_limit_info()
{
	printf("number_of_philos:%d\n"
			"died_time       :%d\n"
			"eating_time     :%d\n"
			"sleeping_time   :%d\n"
			"must_eat_count  :%d\n\n",
		g_philo_info.number_of_philos,
		g_philo_info.died_time,
		g_philo_info.eating_time,
		g_philo_info.sleeping_time,
		g_philo_info.must_eat_count
		);
}

void print_philo_data()
{
	int i;

	for (i = 0 ; i < g_philo_info.number_of_philos ; ++i)
	{
		printf("philo id       :%d\n"
				"recent_eat_time:%d %d\n"
				"left  fork     :%p\n"
				"right fork     :%p\n"
				"eat_count      :%d\n\n",
			g_philo_info.philo_list[i].id,
			g_philo_info.philo_list[i].recent_eat_time.tv_sec,
			g_philo_info.philo_list[i].recent_eat_time.tv_usec,
			g_philo_info.philo_list[i].leftfork,
			g_philo_info.philo_list[i].rightfork,
			g_philo_info.philo_list[i].eat_count
		);
	}
}