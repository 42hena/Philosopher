#include <unistd.h>
#include <sys/time.h>

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

long	get_now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	get_time_ms(struct timeval not_ms)
{
	long long	ms;

	ms = not_ms.tv_sec * 1000 + not_ms.tv_usec / 1000;
	return (ms);
}

void block_philosopher_ms(int want_time)
{
	usleep(want_time * 1000);
}
