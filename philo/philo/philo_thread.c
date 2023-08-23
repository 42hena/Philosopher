/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgang <sgang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 00:56:50 by sgang             #+#    #+#             */
/*   Updated: 2021/10/28 02:08:16 by sgang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	grab_fork(t_nin *gen, t_status *st)
{
	static const char	*grab = " taken fork\n";
	static const char	*eat = " eating\n";

	pthread_mutex_lock(gen->l_fork);
	print(gen, st, grab);
	if (gen->l_fork == gen->r_fork)
	{
		sleep_devide(*(st->info + LIFE_CYCLE) * 11, &st->die);
		pthread_mutex_unlock(gen->l_fork);
		return ;
	}
	pthread_mutex_lock(gen->r_fork);
	print(gen, st, grab);
	print(gen, st, eat);
	st->gmeal++;
	gen->meal++;
	gen->last_action = get_time();
	gen->last_eat = gen->last_action;
	sleep_devide(*(st->info + TO_EAT), &st->die);
	pthread_mutex_unlock(gen->l_fork);
	pthread_mutex_unlock(gen->r_fork);
	return ;
}

static void	hit_the_sack(t_status *st, t_nin *gen)
{
	static const char	*sleeping = " sleeping\n";
	static const char	*thinking = " thinking\n";

	if (st->die != -1)
		return ;
	if (*(st->info + REPEAT) && \
		st->gmeal / *(st->info + NUM_PHILO) == *(st->info + REPEAT))
		return ;
	print(gen, st, sleeping);
	sleep_devide(*(st->info + TO_SLEEP), &st->die);
	if (*(st->info + REPEAT) && \
		st->gmeal / *(st->info + NUM_PHILO) == *(st->info + REPEAT))
		return ;
	print(gen, st, thinking);
	return ;
}

void	*monitor(void *arg)
{
	t_status	*st;
	t_nin		*gen;
	int			idx;
	long long	time;

	st = (t_status *)arg;
	while (st->die == -1 && st->exit_count)
	{
		idx = -1;
		while (++idx < *(st->info + NUM_PHILO) && st->exit_count)
		{
			time = get_time();
			gen = (st->gen + idx);
			if (time - gen->last_eat <= *(st->info + LIFE_CYCLE))
				continue ;
			pthread_mutex_lock(&(st->safe));
			st->die = idx;
			printf("%lld %d died\n", time - st->gstamp, gen->num);
			pthread_mutex_unlock(&(st->safe));
			break ;
		}
	}
	return ((void *)0);
}

void	*simulation(void *arg)
{
	int			cycle;
	t_status	*st;
	t_nin		*gen;

	gen = (t_nin *)arg;
	st = gen->status;
	cycle = *(st->info + REPEAT);
	while (st->die == -1 && (st->repeat || cycle--))
	{
		while (st->gmeal && st->gmeal / *(st->info + NUM_PHILO) < gen->meal)
			;
		grab_fork(gen, st);
		hit_the_sack(st, gen);
	}
	st->exit_count--;
	return ((void *)0);
}
