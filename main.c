#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "philos.h"
#include "utility.h"
#include "init_philo.h"


int	main(int argc, char **argv)
{
	int i;
	int value;
	t_philo_info* info;

	// check arguments count if argc is not 5 or 6
	if (argc != 5 && argc != 6)
	{
		printf("The argc is not valid.\n");
		return (1);
	}

	// check arguments is numeric string
	for (i = 1 ; i < argc ; ++i)
	{
		if (is_numeric_string(argv[i]) == 0)
		{
			printf("The value at index %d is not a number. That string value is '%s'.\n", i, argv[i]);
			return (1);
		}
	}

	// check arguments is positive
	for (i = 1 ; i < argc ; ++i)
	{
		value = atoi(argv[i]);
		if (value <= 0)
		{
			printf("The value %d is not positive.\n", value);
			return (1);
		}
	}

	// create info
	info = (t_philo_info *)malloc(sizeof(t_philo_info));
	// init info
	init_limit_info(info, argc, argv);
	// check info
	print_limit_info(info);

	init_philos(info, argc, argv);
	print_philo_data(info);

	free(info);
	return (0);
}
