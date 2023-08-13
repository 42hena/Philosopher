#ifndef __INIT_PHILO_H__
#define __INIT_PHILO_H__

void init_limit_info(t_philo_info *info, int argc, char **argv);
void init_philos(t_philo_info *info, int argc, char **argv);


void print_limit_info(t_philo_info *info);
void print_philo_data(t_philo_info *info);

#endif