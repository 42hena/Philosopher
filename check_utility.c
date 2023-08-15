#include <stdlib.h>
#include <stdio.h>

#include "utility.h"

#define TRUE 1
#define FALSE 0

int is_argc_56_valid(int argc)
{
	return (argc == 5 || argc == 6);
}

int is_all_argv_valid(int argc, char **argv)
{
	int i;
	int value;

	// check arguments is numeric string
	for (i = 1 ; i < argc ; ++i)
	{
		if (is_numeric_string(argv[i]) == FALSE)
		{
			printf("The value at index %d is not a number. That string value is '%s'.\n", i, argv[i]);
			return (FALSE);
		}
	}

	return (TRUE);
}

int is_all_argv_positive(int argc, char **argv)
{
	int i;
	int value;

	// check arguments is positive
	for (i = 1 ; i < argc ; ++i)
	{
		value = atoi(argv[i]);
		if (value <= 0)
		{
			printf("The value %d is not positive.\n", value);
			return (FALSE);
		}
	}

	return (TRUE);
}

int is_invalid_prameter(int argc, char **argv)
{
	// check arguments count if argc is not 5 or 6
	if (is_argc_56_valid(argc) == FALSE)
	{
		printf("The argc is not valid. because argc:%d\n", argc);
		return (1);
	}

	// check arguments is numeric string
	if (is_all_argv_valid(argc, argv) == FALSE)
		return (1);

	// check arguments is positive
	if (is_all_argv_positive(argc, argv) == FALSE)
		return (1);

	return (0);
}
