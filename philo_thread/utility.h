#ifndef __utility_h__
#define __utility_h__

int is_numeric_string(const char *str);

long long	get_now_ms(void);
long long	get_time_ms(struct timeval not_ms);
void	run_sleep(int time);

#endif