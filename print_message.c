/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hena <hena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:57:48 by hena              #+#    #+#             */
/*   Updated: 2022/03/31 16:57:48 by hena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	print_message(t_philos *philoinfo, int type)
{
	struct timeval		now;
	const char			*state_str[5] = \
		{"is thinking", "has taken a fork", \
		"is eating", "is sleeping", "is dead"};

	pthread_mutex_lock(&philoinfo->gameinfo->end_mutex);
	gettimeofday(&now, NULL);
	if (!philoinfo->gameinfo->end)
		printf("%-10lldms\tphilos [%3d] %s\n", \
			get_time_ms(now) - get_time_ms(philoinfo->gameinfo->create_time), \
			philoinfo->index, state_str[type]);
	pthread_mutex_unlock(&philoinfo->gameinfo->end_mutex);
}
