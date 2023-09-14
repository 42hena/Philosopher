#ifndef PHILOS_H
#define PHILOS_H

enum	e_philo_state
{	
	THINKING,
	PICKING_LEFT_FORK,
	PICKING_RIGHT_FORK,
	EATING,
	SLEEPING,
	DEAD
};

typedef struct s_philo
{
	// philo info
	// enum e_philo_state state; // 미정
	int				eat_count;
	struct timeval	recent_eat_time;

	// process info
	int				philo_id;
	long			start_time;

	// semaphore info
	sem_t			*sem_fork;
}					t_philo;

typedef struct s_philo_info
{
	// argv info
	int				number_of_philos;
	int				eating_time;
	int				sleeping_time;
	int				died_time;
	int				must_eat_count;

	// flag
	int				end_flag;
	
	// semaphore info
	sem_t			*sem_monitor;
	sem_t			*sem_print;

	// thread 무슨 스레드인지 아직 미정.
	pthread_t		thread;
}					t_philo_info;



enum	e_error_state
{
	ERR_PARAM_COUNT = 1,
	ERR_PARAM_STRING,
	ERR_PARAM_NATATIVE
};

#endif
