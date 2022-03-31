#include "philos.h"

/*
**	1 sec = 1,000 ms, 1 usec = 1^-6 sec 
*/

void* t_function(void *arguments)
{
	t_philos *philoinfo;
	
	philoinfo = (t_philos *)arguments;
	if (philoinfo->index % 2 == 0)
		sleep_function(philoinfo->gameinfo->eating_time);
		
	while (!philoinfo->gameinfo->end)
	{
		do_pick(philoinfo);
		do_eat(philoinfo);
		do_sleep(philoinfo);
		do_think(philoinfo);
	}
	return (NULL);
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
	pthread_t	thread;

	i = -1;
	while (++i < game->number_of_philos)
	{
		pthread_create(&(game->philos[i].philo), NULL, t_function, (void *)&game->philos[i]);
		pthread_create(&thread, NULL, dead_monitor, (void *)&game->philos[i]);
		pthread_detach(thread);
	}
	if (game->must_eat_count)
	{
		pthread_create(&thread, NULL, eat_monitor, (void *)game);
		pthread_detach(thread);
	}
}

void	game_end(t_game *game)
{
	int i;

	i = -1;
	while (++i < game->number_of_philos)
	{
		pthread_join(game->philos[i].philo, NULL);
		pthread_mutex_destroy(&game->philos[i].mutex);
	}
	pthread_mutex_destroy(&game->end_mutex);
	free(game->philos);
}

/*
**	Input: philospher_num, die_time, eat_time, sleep_time, [must_eat_count]
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