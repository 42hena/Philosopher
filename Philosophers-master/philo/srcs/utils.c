/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohykim <dohykim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:25:07 by dohykim           #+#    #+#             */
/*   Updated: 2021/12/10 00:34:03 by dohykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(t_philo *philo, ssize_t time, ssize_t timestamp)
{
	ssize_t	time_taken;

	time_taken = 0;
	while (time_taken < timestamp + (time))
	{
		time_taken = ret_timestamp(philo->info);
		usleep(time);
	}
	return (SUCCESS);
}

int	ft_error(char *s)
{
	printf("%s\n", s);
	return (ERROR);
}

int	philo_atoi(const char *str)
{
	long long	num;

	num = 0;
	if (*str == '\0' || *str == '0')
		return (ft_error("Error: argv is null or zero"));
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (ft_error("Error: Only use integer [sign is not valid]"));
		num *= 10;
		num += (*(str++) - '0');
	}
	if (num > 2147483647)
		return (ft_error("Error: Out of int range"));
	return (num);
}
