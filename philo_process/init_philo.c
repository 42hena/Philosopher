#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#include "utility.h"
#include "philos.h"

extern t_philo_info g_info;
extern t_philo		g_philo;

/*
	input : [int, char **]
	output: (None)

	[in] uses main's parameter argc.
	[in] uses main's parameter argv.

	Initializes information for the process to run.
*/

void init_info(int argc, char **argv)
{
	g_info.number_of_philos = atoi(argv[1]);
	g_info.died_time = atoi(argv[2]);
	g_info.eating_time = atoi(argv[3]);
	g_info.sleeping_time = atoi(argv[4]);
	g_info.must_eat_count = -1;
	if (argc == 6)
		g_info.must_eat_count = atoi(argv[5]);
	g_info.end_flag = 0;
}

/*
	input : [int]
	output: (None)

	[in] A parameter used to classify philosophers.

	Save id to philo_id, and initialize the rest to default values.
*/

void init_philos(int id)
{
	struct timeval now_time;
	int	i;

	gettimeofday(&now_time, NULL);
	g_philo.start_time = get_time_ms(now_time);
	g_philo.recent_eat_time = now_time;
	g_philo.philo_id = id;
	g_philo.eat_count = 0;
}

/*
	input : (None)
	output: (None)

	A function that checks the values ​​stored in g_info.
*/

void print_info(void)
{
	printf("number_of_philos:%d\n"
			"died_time       :%d\n"
			"eating_time     :%d\n"
			"sleeping_time   :%d\n"
			"must_eat_count  :%d\n\n",
		g_info.number_of_philos,
		g_info.died_time,
		g_info.eating_time,
		g_info.sleeping_time,
		g_info.must_eat_count
	);
}

/*
	input : (None)
	output: (None)

	A function to check the value stored in g_philo.
*/

void print_philo_data(void)
{
	printf("process id     :%d\n"
			"philo id       :%d\n"
			"eat_count      :%d\n"
			"recent_eat_time:%ld %d\n\n",
		getpid(),
		g_philo.philo_id,
		g_philo.eat_count,
		g_philo.recent_eat_time.tv_sec,
		g_philo.recent_eat_time.tv_usec
	);
}
