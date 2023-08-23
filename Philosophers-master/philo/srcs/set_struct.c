/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohykim <dohykim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:01:29 by dohykim           #+#    #+#             */
/*   Updated: 2021/12/10 01:19:03 by dohykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philos(t_info *info)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * info->num_philos);
	if (philo == NULL)
		return (ft_error("Error : Failed to philo allocation"));
	i = -1;
	while (++i < info->num_philos)
	{
		philo[i].philo_num = 0;
		philo[i].mutex = info->mutex;
		philo[i].info = info;
		philo[i].have_meal = 0;
		philo[i].last_meal_time = 0;
		philo[i].fork_index[RIGHT] = i;
		philo[i].fork_index[LEFT] = i + 1;
	}
	if (info->num_philos == 1)
		philo[--i].fork_index[LEFT] = -1;
	else if (i == info->num_philos)
		philo[--i].fork_index[LEFT] = 0;
	info->philo = philo;
	return (EXIT_SUCCESS);
}

static int	init_mutex(t_info *info)
{
	int		i;
	t_mutex	*mutex;
	t_bool	init_result;

	mutex = (t_mutex *)malloc(sizeof(t_mutex));
	info->mutex = mutex;
	mutex->mutex_forks = (pthread_mutex_t *) \
							malloc(sizeof(pthread_mutex_t) * info->num_philos);
	if (mutex->mutex_forks == NULL || mutex == NULL)
		return (ft_error("Error : Failed to mutex allocation"));
	i = -1;
	while (++i < info->num_philos)
	{
		init_result = pthread_mutex_init(&mutex->mutex_forks[i], NULL);
		if (init_result != SUCCESS)
			return (ft_error("Error : Failed to forks mutex init"));
	}
	init_result = pthread_mutex_init(&mutex->mutex_print, NULL);
	if (init_result != SUCCESS)
		return (ft_error("Error : Failed to print mutex init"));
	return (EXIT_SUCCESS);
}

int	init_info(int argc, char *argv[], t_info *info)
{
	int	argv_num[5];

	if (argc != 5 && argc != 6)
		return (ft_error("Error: Wrong arguments count"));
	argc = 0;
	argv_num[4] = -1;
	while (*(++argv))
	{
		argv_num[argc] = philo_atoi(*argv);
		if (argv_num[argc++] == ERROR)
			return (ERROR);
	}
	info->num_philos = argv_num[0];
	info->time_die = argv_num[1];
	info->time_eat = argv_num[2];
	info->time_sleep = argv_num[3];
	info->must_eat = argv_num[4];
	info->philo_alive = TRUE;
	info->finished_meal = 0;
	info->first_meal_time.tv_sec = 0;
	info->first_meal_time.tv_usec = 0;
	if (init_mutex(info) == ERROR || init_philos(info) == ERROR)
		return (ERROR);
	return (EXIT_SUCCESS);
}

void	clean_all(t_philo *philo, t_mutex *mutex, t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_philos)
		pthread_join(philo[i].philo_tid, NULL);
	i = -1;
	pthread_mutex_destroy(&mutex->mutex_print);
	while (++i < info->num_philos)
		pthread_mutex_destroy(&mutex->mutex_forks[i]);
	free(mutex->mutex_forks);
	free(philo);
	free(mutex);
}
