/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hena <hena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:57:38 by hena              #+#    #+#             */
/*   Updated: 2022/03/31 17:57:39 by hena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	*dead_monitor(void *data)
{
	t_philos		*philo;
	struct timeval	now;
	long long		ms;
	const char		*state_str[5] = \
		{"is thinking", "has taken a fork", \
		"is eating", "is sleeping", "is dead"};

	philo = (t_philos *)data;
	while (!philo->gameinfo->end)
	{
		pthread_mutex_lock(&philo->gameinfo->end_mutex);
		gettimeofday(&now, NULL);
		ms = get_time_ms(now) - get_time_ms(philo->recent_eat_time);
		if (ms >= philo->gameinfo->died_time && !philo->gameinfo->end)
		{
			ms = get_time_ms(now) - get_time_ms(philo->gameinfo->create_time);
			printf("%-10lldms\tphilos [%3d] %s\n", \
			ms, philo->index, state_str[DEAD]);
			philo->gameinfo->end = 1;
		}
		pthread_mutex_unlock(&philo->gameinfo->end_mutex);
	}
	return (NULL);
}

void	*eat_monitor(void *data)
{
	t_game			*game;
	int				i;
	struct timeval	now;
	long long		ms;
	int				flag;

	game = (t_game *)data;
	while (!game->end)
	{
		pthread_mutex_lock(&game->end_mutex);
		i = -1;
		flag = 1;
		while (++i < game->number_of_philos)
			if (game->philos[i].eat_count < game->must_eat_count)
				flag = 0;
		if (flag)
		{
			game->end = 1;
			gettimeofday(&now, NULL);
			ms = get_time_ms(now) - get_time_ms(game->create_time);
			printf("%-10lldms Game Over\n", ms);
		}
		pthread_mutex_unlock(&game->end_mutex);
	}
	return (NULL);
}

void	*philo_routine(void *arguments)
{
	t_philos	*philoinfo;

	philoinfo = (t_philos *)arguments;
	if (philoinfo->index % 2 == 0)
		sleep_function(philoinfo->gameinfo->eating_time);
	while (!philoinfo->gameinfo->end)
	{
		do_pick(philoinfo);
		do_eat(philoinfo);
		do_sleep(philoinfo);
		do_think(philoinfo);
	}
	return (NULL);
}
