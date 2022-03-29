#include "philos.h"
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

void sleep_function(int waiting_time)
{
	struct timeval		now;
	long long			end_time;
	long long			now_time;

	gettimeofday(&now, NULL);
	now_time = get_time_ms(now);
	end_time = now_time + (long long)waiting_time;
    while(end_time > now_time)
	{
		// printf("%ld %ld\n", end_time, now_time);
		gettimeofday(&now, NULL);
		now_time = get_time_ms(now);
		usleep(100);
	}
}