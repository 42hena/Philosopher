#include "check_utility.h"
#include "init_philo.h"
#include "philo_routine.h"

int	main(int argc, char **argv)
{
	int error_code;

	// check parameter is valid
	error_code = is_invalid_prameter(argc, argv);
	if (error_code != 0)
		return (1);
	
	// Init basic info
	init_dining_info(argc, argv);

	// Init philos
	init_philos(argc, argv);

	// start main routine
	begin_philosopher_routines();

	return (0);
}
