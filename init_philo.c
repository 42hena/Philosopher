#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>

#include "philos.h"

void init_limit_info(t_philo_info *info, int argc, char **argv)
{
	info->number_of_philos = atoi(argv[1]);
	info->died_time = atoi(argv[2]);
	info->eating_time = atoi(argv[3]);
	info->sleeping_time = atoi(argv[4]);
	info->must_eat_count = 0;
	if (argc == 6)
		info->must_eat_count = atoi(argv[5]);
	info->end = 0;
	info->philo_list = (t_philo *)malloc(sizeof(t_philo) * info->number_of_philos);
}

void	init_philos(t_philo_info *info, int argc, char **argv)
{
	struct timeval now_time;
	int	i;

	gettimeofday(&now_time, NULL);
	for (i = 0 ; i < info->number_of_philos ; ++i)
	{
		info->philo_list[i].recent_eat_time = now_time;
		info->philo_list[i].id = i + 1;
		info->philo_list[i].leftfork = &info->philo_list[i].mutex;
		info->philo_list[i].rightfork = &info->philo_list[(i + 1) % \
									info->number_of_philos].mutex;
		info->philo_list[i].gameinfo = info;
		info->philo_list[i].eat_count = 0;
	}
}

// check function
void print_limit_info(t_philo_info *info)
{
	printf("number_of_philos:%d\n"
			"died_time       :%d\n"
			"eating_time     :%d\n"
			"sleeping_time   :%d\n"
			"must_eat_count  :%d\n\n",
		info->number_of_philos,
		info->died_time,
		info->eating_time,
		info->sleeping_time,
		info->must_eat_count
		);
}

void print_philo_data(t_philo_info *info)
{
	int i;

	for (i = 0 ; i < info->number_of_philos ; ++i)
	{
		printf("philo id       :%d\n"
				"recent_eat_time:%d %d\n"
				"left  fork     :%p\n"
				"right fork     :%p\n"
				"eat_count      :%d\n\n",
			info->philo_list[i].id,
			info->philo_list[i].recent_eat_time.tv_sec,
			info->philo_list[i].recent_eat_time.tv_usec,
			info->philo_list[i].leftfork,
			info->philo_list[i].rightfork,
			info->philo_list[i].eat_count
		);
	}
}