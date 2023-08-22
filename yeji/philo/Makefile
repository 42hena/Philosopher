NAME = philo
CFLAGS = -Wall -Werror -Wextra -pthread
CC = gcc

SRCS_PHILO = ./philo.c \
			./philo_init.c \
			./philo_parser.c \
			./philo_thread.c \
			./philo_util.c

OBJS_PHILO = $(SRCS_PHILO:.c=.o)

all: $(NAME)

$(NAME): $(OBJS_PHILO)
	@$(CC) -o $@ $^

.c.o:
	@$(CC) $(CFLAGS) -c -o $@ $^

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re