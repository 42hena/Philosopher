NAME = philo_bonus
CFLAGS = -pthread -Wall -Werror -Wextra 
CC = gcc

SRCS_PHILO_BONUS = ./philo_bonus.c \
			./philo_bonus_util.c \
			./philo_bonus_process.c \
			./philo_bonus_thread.c \
			./philo_bonus_parser.c \
			./philo_bonus_init.c

OBJS_PHILO_BONUS = $(SRCS_PHILO_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS_PHILO_BONUS)
	@$(CC) -o $@ $^

.c.o:
	@$(CC) $(CFLAGS) -c -o $@ $^

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re