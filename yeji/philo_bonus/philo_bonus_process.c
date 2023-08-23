/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgang <sgang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 23:55:11 by sgang             #+#    #+#             */
/*   Updated: 2021/10/27 21:42:04 by sgang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	grab_fork(t_nin *gen, t_status *st)
{
	static const char	*grab = " taken fork\n";
	static const char	*eat = " eating\n";

	sem_wait(st->forks);
	print(gen, st, grab);
	sem_wait(st->forks);
	print(gen, st, grab);
	print(gen, st, eat);
	gen->last_eat = get_time();
	gen->last_action = gen->last_eat;
	sleep_devide(*(st->info + TO_EAT));
	sem_post(gen->eat);
	sem_post(st->forks);
	sem_post(st->forks);
	return ;
}

static void	hit_the_sack(t_status *st, t_nin *gen)
{
	static const char	*sleeping = " sleeping\n";
	static const char	*thinking = " thinking\n";

	print(gen, st, sleeping);
	sleep_devide(*(st->info + TO_SLEEP));
	print(gen, st, thinking);
	return ;
}

void	simulation(void *arg)
{
	t_status	*st;
	t_nin		*gen;
	int			cycle;

	gen = (t_nin *)arg;
	st = gen->status;
	cycle = *(st->info + REPEAT);
	if (pthread_create(&(gen->th), NULL, monitor, (void *)gen))
	{
		printf("Error: Thread create failure\n");
		sem_post(st->exit);
	}
	pthread_detach(gen->th);
	while (st->repeat || cycle--)
	{
		grab_fork(gen, st);
		hit_the_sack(st, gen);
	}
	while (1)
		;
}
