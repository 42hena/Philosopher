/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgang <sgang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 00:57:11 by sgang             #+#    #+#             */
/*   Updated: 2021/10/23 02:29:43 by sgang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>
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
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	long long		last_action;
	long long		last_eat;
	long long		meal;
	int				num;
}	t_nin;

struct s_status
{
	struct s_nin	*gen;
	int				info[5];
	pthread_t		mon;
	pthread_mutex_t	safe;
	pthread_mutex_t	*forks;
	long long		gstamp;
	long long		gmeal;
	int				exit_count;
	int				repeat;
	int				die;
};

// philo_parser.c
t_status	*parser(int ac, char **ag, t_status *info);

// philo_init.c
int			init(int ac, char **ag, t_status *st);

//philo_tread.c
void		*simulation(void *arg);
void		*monitor(void *arg);

// philo_util.c
void		print(t_nin *gen, t_status *st, const char *msg);
long long	get_time(void);
void		sleep_devide(int to_action, int *die);

#endif
