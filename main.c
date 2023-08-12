#include <stdio.h>

int	main(int argc, char **argv)
{
	// check arguments count if argc is not 5 or 6
	if (argc != 5 && argc != 6)
	{
		printf("The argc is not valid.\n");
		return (1);
	}

	return (0);
}
