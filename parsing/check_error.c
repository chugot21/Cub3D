
#include "../cub3d.h"

int	check_name(char *argv) //ok verif
{
	int	i;

	i = 0;
	while (argv[i])
	{
		i++;
	}
	if (argv[i - 4] == '.' && argv[i - 3] == 'c'
		&& argv[i - 2] == 'u' && argv[i - 1] == 'b')
	{
		return (0);
	}
	printf("Error : Only .cub files are accepted by the program\n");
	return (1);
}

int	check_player(t_game *game) //idem init_game ou presque
{
	size_t	y;
	size_t	x;
	int	player;

	player = 0;
	y = 0;
	while (y < game->tmap->y_map - 1)
	{
		x = 0;
		while (game->tmap->map[y][x] && x < game->tmap->x_map)
		{
			if (game->tmap->map[y][x] && is_players
				(game->tmap->map[y][x], game) == 1)
			{
				game->tmap->map[y][x] = '7';
				game->tmap->start_player.x = x;
				game->tmap->start_player.y = y;
				player++;
			}
			x++;
		}
		y++;
	}
	return (player);
}

int	check_texture(t_game *data)
{
	int	error;

	error = 0;
	if (!data->tmap->no1 || (open(data->tmap->no1, O_RDONLY) == -1))
		error++;
	if (!data->tmap->so1 || (open(data->tmap->so1, O_RDONLY) == -1))
		error++;
	if (!data->tmap->we1 || (open(data->tmap->we1, O_RDONLY) == -1))
		error++;
	if (!data->tmap->ea1 || (open(data->tmap->ea1, O_RDONLY) == -1))
		error++;
	if (!data->tmap->f1)
		error++;
	if (!data->tmap->c1)
		error++;
	if (error != 0)
	{
		printf("Error : In the file map.cub not all ");
		printf("textures are defined correctly (example \"NO ");
		printf("./path_to_the_north_texture\", same ");
		printf("with SO, WE, EA and \"F 220,100,\" same with C) \n");
		return (1);
	}
	return (0);
}

int	check_ppm(t_game *data)
{
	int	error;

	error = 0;
	if (ft_strnrchr(data->tmap->no1, ".ppm") != 1)
		error++;
	if (ft_strnrchr(data->tmap->so1, ".ppm") != 1)
		error++;
	if (ft_strnrchr(data->tmap->ea1, ".ppm") != 1)
		error++;
	if (ft_strnrchr(data->tmap->we1, ".ppm") != 1)
		error++;
	if (error != 0)
	{
		printf("Error : Textures must be in .ppm format\n");
		return (1);
	}
	return (0);
}

int	check_error(t_game *game, char *argv)
{
	if (check_border_map(game) == 1)
		return (1);
	if (check_texture(game) == 1)
		return (1);
	if (check_ppm(game) == 1)
		return (1);
	check_right(game);
	//for (size_t i = 0; i < 16; i++)
	//	printf("copy [%zu]=%s=\n", i,data->tmap->copy_map[i]);
	if (game->tmap->map_error != 0)
	{
		printf("Error : the map is not closed\n");
		return (1);
	}
	return (0);
}