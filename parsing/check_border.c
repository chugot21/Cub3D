
#include "../cub3d.h"

int	is_players(char c, t_game *game)
{
	if (c == 'N')
	{
		game->dir = 'N';
		return (1);
	}
	else if (c == 'S')
	{
		game->dir = 'S';
		return (1);
	}
	else if (c == 'E')
	{
		game->dir = 'E';
		return (1);
	}
	else if (c == 'W')
	{
		game->dir = 'W';
		return (1);
	}
	return (0);
}

void	malloc_copy_map(t_game *data)
{
	size_t	y;

	y = 0;
	//data->tmap->copy_map = malloc(sizeof(char *) * data->tmap->y_map + 4);
	data->tmap->copy_map = gc_malloc(&data->gc,
			sizeof(char *) * data->tmap->y_map + 4);
	data->tmap->copy_map[y] = gc_malloc(&data->gc, sizeof(char) * data->tmap->x_map + 3);
	while (y < data->tmap->y_map + 1)
	{
		//data->tmap->copy_map[y] = gc_malloc(&data->gc,
		//		sizeof(char) * data->tmap->x_map + 2);
		y++;
	};
}

void	copy_map(t_game *data)
{
	size_t	y;
	size_t	x;

	x = 0;
	y = 0;
	while (x < data->tmap->x_map + 2)
	{
		data->tmap->copy_map[y][x] = '4';
		x++;
	}
	while (y < data->tmap->y_map + 1)
	{
		data->tmap->copy_map[y + 1] = ft_strdup_special
			(data, data->tmap->map[y]);
		y++;
	}
	y++;
	x = 0;
	data->tmap->copy_map[y] = malloc(sizeof(char) * data->tmap->x_map + 3);
	while (x < data->tmap->x_map + 2)
	{
		data->tmap->copy_map[y][x] = '4';
		x++;
	}
	//data->tmap->copy_map[y + 1] = NULL; 
}

void	check_exit(t_game *data)
{
	int y;
	int x;

	y = data->tmap->y_wall;
	x = data->tmap->x_wall;
	if (data->tmap->copy_map[y + 1][x] == '4')
		data->tmap->map_error++;
	if (data->tmap->copy_map[y - 1][x] == '4')
		data->tmap->map_error++;
	if (data->tmap->copy_map[y][x + 1] == '4')
		data->tmap->map_error++;
	if (data->tmap->copy_map[y][x - 1] == '4')
		data->tmap->map_error++;
}

/*
	if (data->tmap->copy_map[data->tmap->x_wall + 1][data->tmap->y_wall] == '4')
		data->tmap->map_error++;
	if (data->tmap->copy_map[data->tmap->x_wall - 1]
		[data->tmap->y_wall] == '4')
		data->tmap->map_error++;
	if (data->tmap->copy_map[data->tmap->x_wall]
		[data->tmap->y_wall + 1] == '4')
		data->tmap->map_error++;
	if (data->tmap->copy_map[data->tmap->x_wall]
		[data->tmap->y_wall - 1] == '4')
		data->tmap->map_error++;
*/

int	check_border_map(t_game *game)
{
	malloc_copy_map(game);
	copy_map(game);
	game->tmap->x_wall = game->player.y;
	game->tmap->y_wall = game->player.x;
	if (check_player(game) == 0)
	{
		printf("Error : No player on the map (N, S , E, W)\n");
		return (1);
	}
	if (check_player(game) > 1)
	{
		printf("Error : Too many players on the map (N, S , E, W)\n");
		return (1);
	}
	if (game->tmap->map_error != 0)
	{
		printf("Error : The map is not closed\n");
		return (1);
	}
	return (0);
}