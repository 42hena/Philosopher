#ifndef PHILOS_H
# define PHILOS_H

typedef struct s_philo	t_philo;
typedef struct s_philo_info
{
	int				number_of_philos;
	int				eating_time;
	int				sleeping_time;
	int				died_time;
	int				must_eat_count;
	int				end;
	pthread_mutex_t	end_mutex;
	// struct timeval	create_time;
	t_philo			*philo_list;
}					t_philo_info;

// print


typedef struct s_philo
{
	int				id;
	int				state;
	int				eat_count;
	pthread_mutex_t	*leftfork;
	pthread_mutex_t	*rightfork;
	pthread_t		philo;
	pthread_mutex_t	mutex;
	t_philo_info	*gameinfo;
	struct timeval	recent_eat_time;
}					t_philo;

/*
**          init.c
*/

// int			check_argumets(int argc, char **argv);
// void		init_mutex(t_game *game);
// void		init_game(t_game *game, int argc, char **argv);
// void		init_philos(t_game *game, int argc, char **argv);

enum	e_philosopher_state
{	
	THINKING,
	PICKING,
	EATING,
	SLEEPING,
	DEAD
};

#endif
