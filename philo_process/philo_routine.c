#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

#include <errno.h>

extern int errno;

// test 로직
void philo_routine(int number)
{
	sem_t *sem;

	sem = sem_open("philo_fork", O_EXCL);
	if (sem < 0)
	{
		printf("sem_open Failed:%d\n", errno);
		return ;
	}
	int ret;
	ret = sem_wait(sem);
	printf("ret:%d pid:%d\n", ret, getpid());
	ret = sem_wait(sem);
	printf("ret:%d pid:%d\n", ret, getpid());
	printf("%d가 포크를 들었네요?\n", getpid());
	sem_post(sem);
	while (1)
		;
	// break;
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
	sem_t *sem_fork;
	sem_t *sem_monitor;
	sem_t *sem_print;

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
	ret = create_semaphore(&sem_fork, "philo_fork", O_CREAT, 0777, 2);
	if (ret < 0)
		return (0);
	ret = create_semaphore(&sem_monitor, "philo_monitor", O_CREAT, 0777, 1);
	if (ret < 0)
		return (0);
	ret = create_semaphore(&sem_print, "philo_print", O_CREAT, 0777, 1);
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

	// Init semaphore
	ret = init_semaphore();
	if (ret == 0)
	{
		printf("초기화에 실패하였습니다\n");
		return (1);
	}
	
	// create pid array.
	pid = (pid_t *)malloc(sizeof(pid_t) * 200); // TODO: 200이 아닌 philo 숫자만큼으로 바꿔야한다.

	// set my process id.
	now_pid = getpid();

	// create as many processes as there are philosophers
	for (i = 0 ; i < 3 ; ++i) // TODO: 3이 아닌 philo 숫자만큼으로 바꿔야한다.
	{
		// fork the process
		pid[i] = fork();

		// parent process
		if (pid[i] > 0)
		{
			printf("프로세스 %d가 pid:%d를 생성하였습니다\n", now_pid, pid[i]);
		}

		// child process
		else if (pid[i] == 0)
		{
			philo_routine(1);
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
	wait(NULL);
	return (1);
}