/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philos.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hena <hena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:58:35 by hena              #+#    #+#             */
/*   Updated: 2022/03/31 17:19:47 by hena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include	<stdio.h>
# include	<pthread.h>
# include	<unistd.h>
# include	<stdlib.h>
# include	<sys/time.h>
# include	<string.h>

// print
typedef struct s_philos	t_philos;
typedef struct s_game
{
	int				number_of_philos;
	int				eating_time;
	int				sleeping_time;
	int				died_time;
	int				must_eat_count;
	int				end;
	pthread_mutex_t	end_mutex;
	struct timeval	create_time;
	t_philos		*philos;
}					t_game;

typedef struct s_philos
{
	int				index;
	int				state;
	int				eat_count;
	pthread_mutex_t	*leftfork;
	pthread_mutex_t	*rightfork;
	pthread_t		philo;
	pthread_mutex_t	mutex;
	t_game			*gameinfo;
	struct timeval	recent_eat_time;
}					t_philos;

/*
**          init.c
*/

int			check_argumets(int argc, char **argv);
void		init_mutex(t_game *game);
void		init_game(t_game *game, int argc, char **argv);
void		init_philos(t_game *game, int argc, char **argv);

/*
**          utility.c
*/

long long	get_time_ms(struct timeval now);
long long	get_now_ms(void);
int			ft_atoi(const char *nptr);

/*
**			print_message.c
*/

void		print_message(t_philos *philoinfo, int type);

/*
**			philos_state.c
*/

void		do_pick(t_philos *philoinfo);
void		do_eat(t_philos *philoinfo);
void		do_sleep(t_philos *philoinfo);
void		do_think(t_philos *philoinfo);

void		sleep_function(int waiting_time);

/*
**			monitor.c
*/

void		*eat_monitor(void *data);
void		*dead_monitor(void *data);
void		*philo_routine(void *arguments);

enum	e_philosopher_state
{	
	THINKING,
	PICKING,
	EATING,
	SLEEPING,
	DEAD
};

#endif
