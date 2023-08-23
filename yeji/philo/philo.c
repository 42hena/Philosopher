/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgang <sgang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 00:57:05 by sgang             #+#    #+#             */
/*   Updated: 2021/10/23 02:29:43 by sgang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destory(t_status *st)
{
	int	idx;

	pthread_join(st->mon, NULL);
	idx = -1;
	while (st->gen && ++idx < *(st->info + NUM_PHILO))
		pthread_join((st->gen + idx)->th, NULL);
	idx = -1;
	while (st->forks && ++idx < *(st->info + NUM_PHILO))
		pthread_mutex_destroy((st->forks + idx));
	free(st->forks);
	free(st->gen);
	return ;
}

int	run(t_status *st)
{
	int	idx;

	idx = 0;
	if (pthread_create(&(st->mon), NULL, monitor, (void *)(st)))
		st->die = RET_ERROR;
	while (idx < *(st->info + NUM_PHILO))
	{
		if (pthread_create(&((st->gen + idx)->th), NULL, simulation, \
			(void *)(st->gen + idx)))
			st->die = RET_ERROR;
		idx += 2;
	}
	idx = 1;
	while (idx < *(st->info + NUM_PHILO))
	{
		usleep(123);
		if (pthread_create(&((st->gen + idx)->th), NULL, simulation, \
			(void *)(st->gen + idx)))
			st->die = RET_ERROR;
		idx += 2;
	}
	if (st->die == RET_ERROR)
		return (printf("Error: Thread create failure\n"));
	return (0);
}

int	main(int ac, char *ag[])
{
	t_status	info;

	memset(&info, 0, sizeof(t_status));
	if (!(ac >= 5 && ac <= 6))
		printf("Error: Check argument\n");
	else if (!init(ac, ag, &info))
		run(&info);
	destory(&info);
	return (0);
}
