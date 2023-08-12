int is_number(const char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);
	return (0);
}

int is_numeric_string(const char *str)
{
	while (*str++)
		if (is_number(*str) == 0)
			return (0);

	return (1);
}