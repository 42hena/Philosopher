#ifndef __utility_h__
#define __utility_h__

int is_numeric_string(const char *str);

long get_now_ms(void);
long get_time_ms(const struct timeval now_ms);
void run_sleep(const int duration);

#endif
