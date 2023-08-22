/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohykim <dohykim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:30:05 by dohykim           #+#    #+#             */
/*   Updated: 2021/12/10 00:40:36 by dohykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_info	t_info;
typedef struct s_mutex	t_mutex;
typedef struct s_philo	t_philo;

typedef enum e_parity	t_parity;
typedef enum e_bool		t_bool;
typedef enum e_status	t_status;
typedef enum e_fork		t_fork;

enum e_parity
{
	ODD,
	EVEN
};

enum e_bool
{
	ERROR = -1,
	FALSE,
	TRUE
};

enum e_status
{
	SUCCESS = 0,
	DEAD,
	EAT,
	THINK,
	SLEEP,
	FORK,
	END
};

enum e_fork
{
	RIGHT,
	LEFT
};

struct s_mutex
{
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	*mutex_forks;
};

struct s_philo
{
	int			fork_index[2];
	ssize_t		last_meal_time;
	int			philo_num;
	int			have_meal;
	pthread_t	philo_tid;
	t_mutex		*mutex;
	t_info		*info;
};

struct s_info
{
	struct timeval	first_meal_time;
	int				num_philos;
	ssize_t			time_die;
	ssize_t			time_eat;
	ssize_t			time_sleep;
	int				must_eat;
	int				finished_meal;
	t_bool			philo_alive;
	t_philo			*philo;
	t_mutex			*mutex;
};
#endif
