#ifndef PHILOS_H
#define PHILOS_H

typedef struct s_philo
{
	// philo info
	int				state;
	int				eat_count;
	pthread_t		thread;
	struct timeval	recent_eat_time;

	// semaphore info
	sem_t			*sem_fork;
	sem_t			*sem_print;
}					t_philo;

typedef struct s_philo_info
{
	// argv info
	int				number_of_philos;
	int				eating_time;
	int				sleeping_time;
	int				died_time;
	int				must_eat_count;

	// process info
	int				philo_id;
	long			start_time;

	// semaphore info
	sem_t			*sem_monitor;
	
	// flag
	int				end_flag;

	t_philo			philo;
}					t_philo_info;

enum	e_philosopher_state
{	
	THINKING,
	PICKING_LEFT_FORK,
	PICKING_RIGHT_FORK,
	EATING,
	SLEEPING,
	DEAD
};

enum	e_error_state
{
	ERR_PARAM_COUNT = 1,
	ERR_PARAM_STRING,
	ERR_PARAM_NATATIVE
};

#endif
