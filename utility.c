/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hena <hena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:52:02 by hena              #+#    #+#             */
/*   Updated: 2022/03/31 17:52:03 by hena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

/*
**	calculate time to ms (struct timeval consist of sec, usec)
*/

long long	get_time_ms(struct timeval not_ms)
{
	long long	ms;

	ms = not_ms.tv_sec * 1000 + not_ms.tv_usec / 1000;
	return (ms);
}

/*
**	calculate now time to ms
*/

long long	get_now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long long	n;

	i = 0;
	sign = 1;
	n = 0;
	while ((nptr[i] <= 13 && nptr[i] >= 9) || nptr[i] == '\n')
		i++;
	if (nptr[i] == '-')
		sign *= -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (n * sign > 2147483647)
			return (-1);
		else if (n * sign < -2147483648)
			return (0);
		else
			n = n * 10 + (nptr[i] - '0');
		i++;
	}
	return (n * sign);
}

void	sleep_function(int waiting_time)
{
	long long	end_time;
	long long	now_time;

	end_time = get_now_ms() + (long long)waiting_time;
	while (end_time > get_now_ms())
	{
		now_time = get_now_ms();
		usleep((end_time - now_time) / 2);
	}
}
