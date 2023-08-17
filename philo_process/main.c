#include <stdio.h>

#include "check_utility.h"
// #include "init_philo.h"
#include "philo_routine.h"

int	main(int argc, char **argv)
{
	int error_code;

	// check parameter is valid
	error_code = is_invalid_prameter(argc, argv);
	if (error_code != 0)
		return (1);
    
    // main logic
    start_philosopher();

    printf("모든 프로세스가 종료되었습니다.\n");
	return (0);
}
