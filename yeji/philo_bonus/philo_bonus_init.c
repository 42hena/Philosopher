/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgang <sgang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 23:55:38 by sgang             #+#    #+#             */
/*   Updated: 2021/10/27 21:43:54 by sgang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static sem_t	*init_sema(char *title, int val)
{
	sem_t	*sem;

	sem_unlink(title);
	sem = sem_open(title, O_CREAT, 0644, val);
	if (sem == SEM_FAILED)
	{
		printf("Error: Semaphore init failure");
		exit(1);
	}
	return (sem);
}

static int	init_info(t_status *st)
{
	int	idx;

	st->gen = malloc(sizeof(t_nin) * *(st->info + NUM_PHILO));
	st->die = *(st->info + NUM_PHILO);
	if (!st->gen)
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
	}
	return (0);
}

static void	make_name(char *buf, int num)
{
	static const char	*t = "PHILO_NUM: ";
	int					idx;

	idx = -1;
	while (*(t + ++idx))
		*(buf + idx) = *(t + idx);
	while (1)
	{
		if (num > 9)
		{
			*(buf + idx++) = (num % 10) + '0';
			num /= 10;
			continue ;
		}
		*(buf + idx++) = num + '0';
		break ;
	}
	*(buf + idx) = '\0';
	return ;
}

static void	init_sem(t_status *st)
{
	int		idx;
	char	bf[256];

	st->forks = init_sema("fork", *(st->info + NUM_PHILO));
	st->safe = init_sema("safe", 1);
	st->exit = init_sema("exit", 0);
	st->checker = init_sema("checker", 1);
	idx = -1;
	while (++idx < *(st->info + NUM_PHILO))
	{
		make_name(bf, idx);
		(st->gen + idx)->eat = init_sema(bf, 0);
	}
	return ;
}

int	init(int ac, char **ag, t_status *st)
{
	st = parser(ac, ag, st);
	if (!st)
		return (printf("Error: Check argument\n"));
	if (init_info(st))
		return (printf("Error: Memory allocate failure\n"));
	init_sem(st);
	return (0);
}
