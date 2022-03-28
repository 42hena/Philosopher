int	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long long	n;

	i = 0;
	sign = 1;
	n = 0;
	while ((nptr[i] <= 13  && nptr[i] >= 9) || nptr[i] == '\n')
		i++;
	if (nptr[i] == '-')
		sign *= -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (n * sign > 2147483647)
			return (-1);
		else if (n * sign < -2147483648)
			return (0);
		else
			n = n * 10 + (nptr[i] - '0');
		i++;
	}
	return (n * sign);
}