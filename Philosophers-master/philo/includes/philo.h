/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohykim <dohykim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:21:11 by dohykim           #+#    #+#             */
/*   Updated: 2021/12/10 04:14:44 by dohykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "structures.h"

// utils.c
int			ft_error(char *s);
int			philo_atoi(const char *str);
int			ft_usleep(t_philo *philo, ssize_t time, ssize_t timestamp);

// set_struct.c
int			init_info(int argc, char *argv[], t_info *info);
void		clean_all(t_philo *philo, t_mutex *mutex, t_info *info);

// philos_routine.c
void		*thread_philo(void *start_routine);
ssize_t		ret_timestamp(t_info *info);
int			print_status(t_philo *philo, char *str, int status, int philo_num);

#endif
