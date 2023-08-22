/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohykim <dohykim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:21:16 by dohykim           #+#    #+#             */
/*   Updated: 2021/12/10 04:15:58 by dohykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	delay_eating(t_info info)
{
	struct timeval	get_time;
	struct timeval	timestamp;
	ssize_t			time_taken;

	if (info.time_eat + info.time_sleep > info.time_die)
	{
		usleep(1000);
		return (DEAD);
	}
	gettimeofday(&get_time, NULL);
	while (TRUE)
	{
		gettimeofday(&timestamp, NULL);
		time_taken = ((timestamp.tv_sec - get_time.tv_sec) * 1000000) + \
						(timestamp.tv_usec - get_time.tv_usec);
		if (time_taken >= info.time_eat * 900)
			break ;
		usleep(info.time_eat);
	}
	return (SUCCESS);
}

static void	monitor_philos(t_philo *philo, t_info *info)
{
	ssize_t	timestamp;
	int		i;

	i = -1;
	while (++i < info->num_philos)
	{
		timestamp = ret_timestamp(info);
		if ((timestamp - philo[i].last_meal_time) >= info->time_die)
		{
			info->philo_alive = FALSE;
			print_status(philo, "died", END, i + 1);
			break ;
		}
		else if (info->must_eat != -1 \
				&& info->finished_meal >= info->num_philos)
		{
			info->philo_alive = FALSE;
			print_status(philo, "All philos have finished meal", END, i + 1);
			break ;
		}
		if (i == info->num_philos - 1)
			i = -1;
	}
}

static int	start_dining(t_philo *philo, int num_philos)
{
	int		i;
	t_bool	result;

	i = EVEN;
	while (i < num_philos)
	{
		philo[i].philo_num = i;
		result = pthread_create \
				(&philo[i].philo_tid, NULL, thread_philo, &philo[i]);
		if (result != SUCCESS)
			return (ft_error("Error: Fail to create thread"));
		i += 2;
	}
	delay_eating(*philo->info);
	i = ODD;
	while (i < num_philos)
	{
		philo[i].philo_num = i;
		result = pthread_create \
				(&philo[i].philo_tid, NULL, thread_philo, &philo[i]);
		if (result != SUCCESS)
			return (ft_error("Error: Fail to create thread"));
		i += 2;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_info	info;
	t_bool	result;

	result = init_info(argc, argv, &info);
	if (result == ERROR)
		return (EXIT_FAILURE);
	result = start_dining(info.philo, info.num_philos);
	if (result == ERROR)
		return (EXIT_FAILURE);
	monitor_philos(info.philo, &info);
	clean_all(info.philo, info.philo->mutex, &info);
	return (EXIT_SUCCESS);
}
