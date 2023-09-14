#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <pthread.h>
#include <sys/time.h>

#include <errno.h>

#include "philos.h"
#include "philo_state.h"
#include "init_philo.h"
#include "utility.h"


t_philo_info	g_info;
t_philo			g_philo;

extern int		errno;

void monitor_thread_routine(void *param)
{
	struct timeval now_time;

	g_info.sem_monitor = sem_open("philo_monitor", O_EXCL);
	if (g_info.sem_monitor < 0)
	{
		printf("sem_open Failed:%d\n", errno);
		return ;
	}

	while (!g_info.end_flag)
	{
		sem_wait(g_info.sem_monitor);
		gettimeofday(&now_time, NULL);
		
		// printf("%ld %d %ld %ld\n", get_time_ms(now_time), g_info.died_time, get_time_ms(g_philo.recent_eat_time), g_info.died_time+ get_time_ms(g_philo.recent_eat_time));
		if (get_time_ms(now_time) > g_info.died_time + get_time_ms(g_philo.recent_eat_time))
		{
			// printf("qwer\n");
			print_message(&g_philo, DEAD);
			g_info.end_flag = 1;
			sem_post(g_info.sem_monitor);
			
			
			break;
		}
		g_philo.recent_eat_time = now_time;
		sem_post(g_info.sem_monitor);
	}
}

int philo_routine(int number)
{
	sem_t *sem;
	int ret;
	t_philo philo;
	
	philo = g_philo;

	g_philo.sem_fork = sem_open("philo_fork", O_EXCL);
	if (g_philo.sem_fork < 0)
	{
		printf("sem_open Failed:%d\n", errno);
		return (0);
	}
	
	pthread_create(&g_info.thread, NULL, (void *)&monitor_thread_routine, NULL);
	while (!g_info.end_flag)
	{
		ret = do_pick_forks(&philo);
		do_eat(&philo);
		do_sleep(&philo);
		do_think(&philo);
	}
	
	return (1);
}

/*
	input : sem_t **sem, const char *name, int oflag, mode_t mode, unsigned int value
	output: (TRUE or FALSE)

	The sem_open function creates a semaphore and returns a value to the sem variable.
*/

int create_semaphore(sem_t **sem, const char *name, int oflag, mode_t mode, unsigned int value)
{
	*sem = sem_open(name, oflag, mode, value);
	if (*sem < 0)
	{
		printf("%s를 생성하지 못했습니다. errno:%d\n", name, errno);
		return (0);
	}
	return (1);
}

/*
	input : (None)
	output: (TRUE or FALSE)

	if the named semaphore exists, remove named semaphore using sem_unlink() function.
	And, create named semaphore.
*/

int init_semaphore()
{
	int ret;

	// delete semaphore
	// remove "philo_fork"
	ret = sem_unlink("philo_fork");
	if (ret < 0)
	{
		printf("sem_unlink fail. errno:%d\n", errno);
		if (errno != ENOENT)
			return (0);
	}

	// remove "philo_monitor"
	ret = sem_unlink("philo_monitor");
	if (ret < 0)
	{
		printf("sem_unlink fail. errno:%d\n", errno);
		if (errno != ENOENT)
			return (0);
	}

	// remove "philo_print"
	ret = sem_unlink("philo_print");
	if (ret < 0)
	{
		printf("sem_unlink fail. errno:%d\n", errno);
		if (errno != ENOENT)
			return (0);
	}

	// create semaphore
	ret = create_semaphore(&g_philo.sem_fork, "philo_fork", O_CREAT, 0777, g_info.number_of_philos);
	if (ret < 0)
		return (0);
	ret = create_semaphore(&g_info.sem_monitor, "philo_monitor", O_CREAT, 0777, 1);
	if (ret < 0)
		return (0);
	ret = create_semaphore(&g_info.sem_print, "philo_print", O_CREAT, 0777, 1);
	if (ret < 0)
		return (0);
	return (1);
}
/*
	input : (None)
	output: (TRUE or FALSE)

	main logic. The parent process creates the philosopher process, 
	and the child process executes the philosopher logic.
*/

int start_philosopher()
{
	pid_t *pid;
	pid_t now_pid;
	int ret;
	int i;
	struct timeval now_time;

	// Init semaphore
	ret = init_semaphore();
	if (ret == 0)
	{
		printf("초기화에 실패하였습니다\n");
		return (1);
	}
	
	// create pid array.
	pid = (pid_t *)malloc(sizeof(pid_t) * g_info.number_of_philos); // TODO: 200이 아닌 philo 숫자만큼으로 바꿔야한다.

	// set my process id.
	now_pid = getpid();

	
	gettimeofday(&now_time, NULL);
	g_philo.start_time = get_time_ms(now_time);
	g_philo.recent_eat_time = now_time;

	// create as many processes as there are philosophers
	for (i = 0 ; i < g_info.number_of_philos ; ++i) // TODO: 3이 아닌 philo 숫자만큼으로 바꿔야한다.
	{
		// fork the process
		pid[i] = fork();

		// parent process
		if (pid[i] > 0)
		{
			// printf("프로세스 %d가 pid:%d를 생성하였습니다\n", now_pid, pid[i]);
		}

		// child process
		else if (pid[i] == 0)
		{
			init_philos(i + 1);
			// print_philo_data();
			philo_routine(i + 1);
			return (1);
		}

		// occur error
		else // TODO: 생성된 프로세스들을 죽이는 함수가 필요할 것 같다.
		{
			printf("fork() function failed. Error code%d\n", errno);
			return (0);
		}
	}

	// TODO: wait 찾고 바꿔줘야 함.
	for (i = 0 ; i < g_info.number_of_philos ; ++i)
		wait(NULL);
	free(pid);
	return (1);
}