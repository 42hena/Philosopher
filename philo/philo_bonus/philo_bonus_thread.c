/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_thread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgang <sgang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 21:37:31 by sgang             #+#    #+#             */
/*   Updated: 2021/10/27 21:52:19 by sgang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*eating_monitor(void *arg)
{
	t_status	*st;
	int			idx;
	int			cycle;

	st = (t_status *)arg;
	cycle = *(st->info + REPEAT);
	while (st->repeat || cycle--)
	{
		idx = -1;
		while (++idx < *(st->info + NUM_PHILO))
			sem_wait((st->gen + idx)->eat);
	}
	sem_wait(st->safe);
	sem_post(st->exit);
	return ((void *)0);
}

void	*monitor(void *arg)
{
	t_status	*st;
	t_nin		*gen;
	long long	time;

	gen = (t_nin *)arg;
	st = gen->status;
	while (1)
	{
		usleep(100);
		time = get_time();
		if (time - gen->last_eat <= *(st->info + LIFE_CYCLE))
			continue ;
		sem_wait(st->checker);
		printf("%lld %d died\n", get_time() - st->gstamp, gen->num);
		sem_post(st->exit);
		exit(1);
	}
	return ((void *)0);
}
