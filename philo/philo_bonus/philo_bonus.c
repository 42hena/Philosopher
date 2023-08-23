/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgang <sgang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 23:55:14 by sgang             #+#    #+#             */
/*   Updated: 2021/10/27 21:47:43 by sgang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	destory(t_status *st)
{
	int	idx;

	sem_wait(st->exit);
	idx = -1;
	while (st->gen && ++idx < *(st->info + NUM_PHILO))
		kill((st->gen + idx)->proc, SIGKILL);
	sem_close(st->forks);
	sem_close(st->safe);
	sem_close(st->exit);
	free(st->gen);
	return ;
}

static int	run(t_status *st)
{
	int	idx;

	idx = -1;
	st->gstamp = get_time();
	if (pthread_create(&(st->monitor), NULL, eating_monitor, (void *)st))
	{
		printf("Error: Thread create failure\n");
		return (sem_post(st->exit));
	}
	pthread_detach(st->monitor);
	while (++idx < *(st->info + NUM_PHILO))
	{
		usleep(123);
		(st->gen + idx)->last_eat = st->gstamp;
		(st->gen + idx)->proc = fork();
		if (!(st->gen + idx)->proc)
			simulation((st->gen + idx));
		else if ((st->gen + idx)->proc < 0)
		{
			sem_wait(st->safe);
			printf("Error : Failure to create process");
			return (sem_post(st->exit));
		}
	}
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
