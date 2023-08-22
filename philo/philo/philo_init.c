/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgang <sgang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 01:25:42 by sgang             #+#    #+#             */
/*   Updated: 2021/10/23 02:29:43 by sgang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(t_status *st)
{
	int	idx;
	int	next;

	idx = -1;
	while (++idx < *(st->info + NUM_PHILO))
	{
		if (pthread_mutex_init((st->forks + idx), NULL))
			return (RET_ERROR);
		next = idx + 1;
		if (next == *(st->info + NUM_PHILO))
			next = 0;
		(st->gen + idx)->l_fork = (st->forks + idx);
		(st->gen + idx)->r_fork = (st->forks + next);
		if (idx % 2)
		{
			(st->gen + idx)->r_fork = (st->forks + idx);
			(st->gen + idx)->l_fork = (st->forks + next);
		}
	}
	if (pthread_mutex_init(&(st->safe), NULL))
		return (RET_ERROR);
	return (0);
}

static int	init_info(t_status *st)
{
	int	idx;

	st->gen = malloc(sizeof(t_nin) * *(st->info + NUM_PHILO));
	st->forks = malloc(sizeof(pthread_mutex_t) * *(st->info + NUM_PHILO));
	st->gstamp = get_time();
	st->exit_count = *(st->info + NUM_PHILO);
	if (!st->gen || !st->forks)
		return (RET_ERROR);
	st->die = -1;
	if (!*(st->info + REPEAT))
		st->repeat = 1;
	idx = -1;
	while (++idx < *(st->info + NUM_PHILO))
	{
		memset(st->gen + idx, 0, sizeof(t_nin));
		(st->gen + idx)->status = st;
		(st->gen + idx)->num = idx;
		(st->gen + idx)->last_eat = st->gstamp;
	}
	return (0);
}

int	init(int ac, char **ag, t_status *st)
{
	st = parser(ac, ag, st);
	if (!st)
		return (printf("Error: Check argument\n"));
	if (init_info(st))
		return (printf("Error: Memory allocate failure\n"));
	if (init_mutex(st))
		return (printf("Error: Mutex init failure\n"));
	return (0);
}
