#ifndef PHILOS_H
#define PHILOS_H

typedef struct s_philo
{
	int				id;
	int				eat_count;

	// fork mutex
	pthread_mutex_t	*leftfork;
	pthread_mutex_t	*rightfork;
	pthread_mutex_t	mutex;	// fork_mutex 실체

	

	struct timeval	recent_eat_time;

	pthread_t		philo;

	// 보류
	// int				state;
}					t_philo;

typedef struct s_philo_info
{
	// A variable to store the input values received in the main function.
	int				number_of_philos;
	int				eating_time;
	int				sleeping_time;
	int				died_time;
	int				must_eat_count;

	// An arbitrary value to synchronize the starting time among all philosophers.
	long			start_time; // TODO: baseline_time으로 바꾸기.

	// philosopher
	t_philo			*philo_list;

	// A variable that determines the termination flow of a thread.
	int				end_flag;

	// eat_time mutexes
	pthread_mutex_t	*eat_time_mutex;

	// 
	pthread_mutex_t	print_mutex;	
}					t_dining_info;

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
