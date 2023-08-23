/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgang <sgang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 23:55:50 by sgang             #+#    #+#             */
/*   Updated: 2021/10/28 02:28:48 by sgang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>

# define RET_ERROR		-2
# define RET_SUCCESS	0
# define NUM_PHILO		0
# define LIFE_CYCLE		1
# define TO_EAT			2
# define TO_SLEEP		3
# define REPEAT			4

typedef struct s_status	t_status;
typedef struct s_nin
{
	struct s_status	*status;
	pthread_t		th;
	sem_t			*eat;
	pid_t			proc;
	long long		last_action;
	long long		last_eat;
	int				num;
	int				exit_flag;
}	t_nin;

struct s_status
{
	struct s_nin	*gen;
	int				info[5];
	pthread_t		monitor;
	sem_t			*exit;
	sem_t			*forks;
	sem_t			*safe;
	sem_t			*checker;
	long long		gstamp;
	int				repeat;
	int				die;
};

// philo_bonus_parser.c
t_status	*parser(int ac, char **ag, t_status *info);

// philo_bonus_init.c
int			init(int ac, char **ag, t_status *st);

// philo_bonus_semaphore.c
void		simulation(void *arg);

// philo_bonus_thread.c
void		*eating_monitor(void *arg);
void		*monitor(void *arg);

// philo_bonus_util.c
void		print(t_nin *gen, t_status *st, const char *msg);
long long	get_time(void);
void		sleep_devide(int to_action);

#endif
