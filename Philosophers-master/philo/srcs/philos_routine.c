/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohykim <dohykim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:51:48 by dohykim           #+#    #+#             */
/*   Updated: 2021/12/10 04:16:15 by dohykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

ssize_t	ret_timestamp(t_info *info)
{
	struct timeval	get_time;
	struct timeval	first_meal;
	ssize_t			timestamp;

	first_meal = info->first_meal_time;
	if (first_meal.tv_sec == 0)
		return (0);
	gettimeofday(&get_time, NULL);
	timestamp = ((get_time.tv_sec * 1000) + (get_time.tv_usec / 1000)) - \
				((first_meal.tv_sec * 1000) + (first_meal.tv_usec / 1000));
	return (timestamp);
}

int	print_status(t_philo *philo, char *str, int status, int philo_num)
{
	ssize_t	timestamp;
	t_mutex	*mutex;
	t_info	*info;

	mutex = philo->mutex;
	info = philo->info;
	pthread_mutex_lock(&mutex->mutex_print);
	timestamp = ret_timestamp(info);
	if (status != END && info->philo_alive == FALSE)
		return (DEAD);
	if (status == END && \
		info->must_eat != -1 && info->finished_meal >= info->num_philos)
		printf("%zd %s\n", timestamp, str);
	else
		printf("%zd %d %s\n", timestamp, philo_num, str);
	pthread_mutex_unlock(&mutex->mutex_print);
	if (status == EAT)
	{
		philo->last_meal_time = timestamp;
		ft_usleep(philo, info->time_eat, timestamp);
	}
	else if (status == SLEEP)
		ft_usleep(philo, info->time_sleep, timestamp);
	return (SUCCESS);
}

static int	philo_eat(t_philo *philo, t_mutex *mutex, t_info *info)
{
	int	i;

	i = LEFT;
	while (i >= RIGHT)
	{
		if (pthread_mutex_lock \
		(&mutex->mutex_forks[philo->fork_index[i--]]) != SUCCESS)
			return (ERROR);
		if (print_status \
		(philo, "has taken a fork", FORK, philo->philo_num + 1) == DEAD)
			return (DEAD);
	}
	if (print_status \
		(philo, "is eating", EAT, philo->philo_num + 1) == DEAD)
		return (DEAD);
	pthread_mutex_unlock(&mutex->mutex_forks[philo->fork_index[RIGHT]]);
	pthread_mutex_unlock(&mutex->mutex_forks[philo->fork_index[LEFT]]);
	philo->have_meal++;
	if (philo->have_meal >= info->must_eat)
		info->finished_meal++;
	return (SUCCESS);
}

void	*thread_philo(void *start_routine)
{
	t_philo	*philo;
	t_info	*info;
	t_mutex	*mutex;

	philo = (t_philo *)start_routine;
	info = philo->info;
	mutex = philo->mutex;
	if (info->first_meal_time.tv_sec == 0)
		gettimeofday(&info->first_meal_time, NULL);
	while (info->philo_alive == TRUE)
	{
		if (philo_eat(philo, mutex, info) != SUCCESS)
			break ;
		if (print_status(philo, "is sleeping", SLEEP, philo->philo_num + 1) \
			!= SUCCESS)
			break ;
		if (print_status(philo, "is thinking", THINK, philo->philo_num + 1) \
			!= SUCCESS)
			break ;
	}
	pthread_mutex_unlock(&philo->mutex->mutex_print);
	pthread_mutex_unlock(&philo->mutex->mutex_forks[philo->fork_index[RIGHT]]);
	pthread_mutex_unlock(&philo->mutex->mutex_forks[philo->fork_index[LEFT]]);
	return (NULL);
}
