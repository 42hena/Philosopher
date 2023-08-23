/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgang <sgang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 00:56:58 by sgang             #+#    #+#             */
/*   Updated: 2021/10/22 00:56:58 by sgang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_devide(int to_action, int *die)
{
	const long long	current_time = get_time();

	while (get_time() - current_time < to_action && *die == -1)
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

	pthread_mutex_lock(&(st->safe));
	cur_time = get_time();
	if (st->die != -1)
	{
		pthread_mutex_unlock(&(st->safe));
		return ;
	}
	printf("%lld %d%s", cur_time - st->gstamp, gen->num, msg);
	pthread_mutex_unlock(&(st->safe));
	return ;
}
