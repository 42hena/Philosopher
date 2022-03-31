#include "philos.h"

static int	is_in_all_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (0);
		++i;
	}
	return (1);
}

int	check_argumets(int argc, char **argv)
{
	if (is_in_all_number(argv[1]) && \
			is_in_all_number(argv[2]) && \
			is_in_all_number(argv[3]) && \
			is_in_all_number(argv[4]))
		return (0);
	if (argc == 6 && is_in_all_number(argv[5]))
		return (0);
	return (1);
}

void	init_mutex(t_game *game)
{
	int	i;

	i = -1;
	pthread_mutex_init(&game->end_mutex, NULL);
	while (++i < game->number_of_philos)
		pthread_mutex_init(&game->philos[i].mutex, NULL);
}

void	init_game(t_game *game, int argc, char **argv)
{
	game->number_of_philos = ft_atoi(argv[1]);
	game->died_time = ft_atoi(argv[2]);
	game->eating_time = ft_atoi(argv[3]);
	game->sleeping_time = ft_atoi(argv[4]);
	game->must_eat_count = 0;
	if (argc == 6)
		game->must_eat_count = ft_atoi(argv[5]);
	game->end = 0;
	game->philos = (t_philos *)malloc(sizeof(t_philos) * \
			game->number_of_philos);
}

void	init_philos(t_game *game, int argc, char **argv)
{
	int	i;

	i = -1;
	gettimeofday(&game->create_time, NULL);
	while (++i < game->number_of_philos)
	{
		game->philos[i].recent_eat_time = game->create_time;
		game->philos[i].index = i + 1;
		game->philos[i].leftfork = &game->philos[i].mutex;
		game->philos[i].rightfork = &game->philos[(i + 1) % \
									game->number_of_philos].mutex;
		game->philos[i].gameinfo = game;
		game->philos[i].eat_count = 0;
	}
}
