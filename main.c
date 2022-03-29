#include "philos.h"

/*
**	1 sec = 1,000 ms, 1 usec = 1^-6 sec 
*/

long long	get_time_ms(struct timeval not_ms)
{
	long long	ms;

	ms = not_ms.tv_sec * 1000 + not_ms.tv_usec / 1000;
	return (ms);
}

void* t_function(void *arguments)
{
	t_philos *philoinfo;
	
	philoinfo = (t_philos *)arguments;
	if (philoinfo->index % 2 == 0)
		// sleep_function(philoinfo->gameinfo->eating_time);
		usleep(50);
	while (!philoinfo->gameinfo->end)
	{
		do_pick(philoinfo);
		do_eat(philoinfo);
		do_sleep(philoinfo);
		do_think(philoinfo);
	}
	return (NULL);
}

void init_mutex(t_game *game)
{
	int i;
	
	i = -1;
	pthread_mutex_init(&game->work_mutex, NULL);
	while (++i < game->number_of_philos)
	{
		pthread_mutex_init(&game->philos[i].mutex, NULL);
		pthread_mutex_init(&game->philos[i].check, NULL);
	}
}

void	init_game(t_game *game, int argc, char **argv)
{
	game->number_of_philos = ft_atoi(argv[1]);
	game->died_time = ft_atoi(argv[2]);
	game->eating_time = ft_atoi(argv[3]);
	game->sleeping_time = ft_atoi(argv[4]);
	game->end = 0;
	game->philos = (t_philos *)malloc(sizeof(t_philos) * game->number_of_philos);
	gettimeofday(&game->create_time, NULL);
}

void	init_philos(t_game *game, int argc, char **argv)
{
	int i;

	i = -1;
	while (++i < game->number_of_philos)
	{
		game->philos[i].recent_eat_time = game->create_time;
		game->philos[i].index = i + 1;
		game->philos[i].leftfork = &game->philos[i].mutex;
		game->philos[i].rightfork = &game->philos[(i + 1) % game->number_of_philos].mutex;
		game->philos[i].state = THINKING;
		game->philos[i].gameinfo = game;
		// if (argc == 6) // 
		// 	game->philos[i].remain_count = ft_atoi(argv[5]);
	}
}

void	init_argv_data(t_game *game, int argc, char **argv)
{	
	init_game(game, argc, argv);
	init_mutex(game);
	init_philos(game, argc, argv);
}

void	game_start(t_game *game)
{
	int			i;
	int			state;
	pthread_t	thread;

	i = -1;
	while (++i < game->number_of_philos)
	{
		pthread_create(&(game->philos[i].philo), NULL, t_function, (void *)&game->philos[i]);
		pthread_create(&thread, NULL, monitor, (void *)&game->philos[i]);
		pthread_detach(thread);
	}
}

void	game_end(t_game *game)
{
	int i;
	int state;

	i = -1;
	while (++i < game->number_of_philos)
	{
		pthread_join(game->philos[i].philo, (void *)&state);
	}
}

/*
**	philonum, die, eat, sleep, [count]
입력 처리 부분 붙여야 함
*/

int main(int argc, char **argv)
{
	t_game game;
	if (argc != 5 && argc != 6)
	{
		printf("exit\n");
		return (0);
	}
	init_argv_data(&game, argc, argv);
	game_start(&game);
	game_end(&game);
}