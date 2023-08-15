/*
	input :	const char ch
	output:	true or false

	description
*/

int is_number(const char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);
	return (0);
}

/*
	input :	const char *str
	output:	true or false

	description
*/

int is_numeric_string(const char *str)
{
	while (*str)
	{
		if (is_number(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}