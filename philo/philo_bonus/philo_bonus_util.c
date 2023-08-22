/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgang <sgang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 23:55:19 by sgang             #+#    #+#             */
/*   Updated: 2021/10/27 21:36:31 by sgang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	sleep_devide(int to_action)
{
	const long long	current_time = get_time();

	while (get_time() - current_time < to_action)
		usleep(to_action);
	return ;
}

long long	get_time(void)
{
	struct timeval	ret;

	gettimeofday(&ret, NULL);
	return (ret.tv_sec * 1000 + ret.tv_usec / 1000);
}

void	print(t_nin *gen, t_status *st, const char *msg)
{
	long long	cur_time;

	sem_wait(st->checker);
	sem_wait(st->safe);
	cur_time = get_time();
	printf("%lld %d%s", cur_time - st->gstamp, gen->num, msg);
	sem_post(st->safe);
	sem_post(st->checker);
	return ;
}
