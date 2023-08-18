#ifndef __utility_h__
#define __utility_h__

int is_numeric_string(const char *str);

long get_now_ms(void);
long get_time_ms(struct timeval not_ms);
void block_philosopher_ms(int want_time);



#endif