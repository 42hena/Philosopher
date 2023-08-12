#include <stdio.h>
#include "utility.h"


int	main(int argc, char **argv)
{
	int i;

	// check arguments count if argc is not 5 or 6
	if (argc != 5 && argc != 6)
	{
		printf("The argc is not valid.\n");
		return (1);
	}

	for (i = 1 ; i < argc ; ++i)
	{
		if (is_numeric_string(argv[i]) == 0)
		{
			printf("The value at index %d is not a number. That string value is '%s'.\n", i, argv[i]);
			return (1);
		}
	}

	return (0);
}
