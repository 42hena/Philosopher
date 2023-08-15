#ifndef PHILOS_H
#define PHILOS_H

typedef struct s_philo
{
	int				id;
	int				state;
	int				eat_count;
	pthread_mutex_t	*leftfork;
	pthread_mutex_t	*rightfork;
	pthread_t		philo;
	pthread_mutex_t	mutex;
	struct timeval	recent_eat_time;
}					t_philo;

typedef struct s_philo_info
{
	// values from convert 
	int				number_of_philos;
	int				eating_time;
	int				sleeping_time;
	int				died_time;
	int				must_eat_count;

	long long		start_time;
	int				end_flag;
	pthread_mutex_t	print_mutex;
	t_philo			*philo_list;
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
