#include <unistd.h> //time
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

#include <errno.h> // [EDEADLK]

#include "philos.h"
#include "philo_state.h"
#include "utility.h"

#define TRUE 1
#define FALSE 0

extern t_dining_info g_dining_info;

void *philo_routine_thread(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;

	// 생성 시 전부 블락 상태를 걸리게 함.
	pthread_mutex_lock(&g_dining_info.mtx_create);

	// 락 획득을 풀어줌으로써 다른 스레드가 돌게 함.
	pthread_mutex_unlock(&g_dining_info.mtx_create);

	// 환형대기를 막기 위해 순서를 정해줌.
	if (philo->id % 2 == 0)
	{
		usleep(g_dining_info.eating_time * 1000);
	}

	while (!g_dining_info.end_flag)
	{
		do_pick(philo);
		do_eat(philo);
		do_sleep(philo);
		do_think(philo);
	}	
	return (0);
}

void monitor_philos()
{
	int i;
	int philo_number;

	long timestamp;
	const long start_time = g_dining_info.start_time;
	philo_number = g_dining_info.number_of_philos;
	const int must_eat_count = g_dining_info.must_eat_count;
	
	
	pthread_mutex_lock(&g_dining_info.print_mutex);
	timestamp = get_now_ms();
	for (i = 0 ; i < philo_number ; ++i)
	{	
		if (timestamp - get_time_ms(g_dining_info.philo_list[i].recent_eat_time) >= g_dining_info.died_time)
		{
			g_dining_info.end_flag = TRUE;
			printf("%-10ldms\tphilos [%3d] Died\n", timestamp - start_time, i + 1);
			break ;
		}
		if (must_eat_count != -1 && g_dining_info.philo_list[i].eat_count >= must_eat_count)
		{
			g_dining_info.end_flag = TRUE;
			printf("%-10ldms\tphilos [%3d] Eat End\n", timestamp - start_time, i + 1);
			break ;
		}
	}
	pthread_mutex_unlock(&g_dining_info.print_mutex);
}

void begin_philosopher_routines()
{
	int i;
	int philo_number;

	// return variable
	int pthread_join_ret;
// -----

	// 재사용을 위해 number에 저장함.
	philo_number = g_dining_info.number_of_philos;

	printf("Philosopher problem start\n");
	pthread_mutex_lock(&g_dining_info.mtx_create);
	// 홀수 번째 먼저 생성.
	for (i = 1 ; i < philo_number ; i += 2)
	{
		pthread_create(&(g_dining_info.philo_list[i].philo), NULL, philo_routine_thread, (void *)&g_dining_info.philo_list[i]);
		pthread_detach(g_dining_info.philo_list[i].philo);
	}

	// 짝수 번째 먼저 생성.
	for (i = 0 ; i < philo_number ; i += 2)
	{
		pthread_create(&(g_dining_info.philo_list[i].philo), NULL, philo_routine_thread, (void *)&g_dining_info.philo_list[i]);
		pthread_detach(g_dining_info.philo_list[i].philo);
	}

	// mtx_create 락을 해제함으로써 동시에 시작하게 만듬.
	pthread_mutex_unlock(&g_dining_info.mtx_create);

	// main에서 monitor th역할을 하도록 함.
	while (!g_dining_info.end_flag)
	{
		monitor_philos();
	}

	// main을 제외한 스레드를이 끝나기를 기다리는 코드임.
	for (i = 0 ; i < philo_number ; ++i)
	{
		// 스레드의 작동을 기다림.
		pthread_join_ret = pthread_join(g_dining_info.philo_list[i].philo, NULL);
		if (pthread_join_ret == EDEADLK)
		{
			printf("The [%d]th philosopher thread is deadlocked.\n", i);
			break ;
		}
	}

	printf("Philosopher problem end\n");
}
