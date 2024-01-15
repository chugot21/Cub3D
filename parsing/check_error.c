
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

int	check_player(t_game *game) //ok
{
	int	y;
	int	x;
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
				game->tmap->start_player.x = x; //selectionne emplacement joueur.
				game->tmap->start_player.y = y; //selectionne emplacement joueur.
				player++;
			}
			x++;
		}
		y++;
	}
	return (player);
}

int	check_texture(t_game *data) //ok
{
	int	error;

	error = 0;
	if (!data->tno || (open(data->tno, O_RDONLY) == -1)) //if (!data->tmap->no1 || (open(data->tmap->no1, O_RDONLY) == -1))
		error++;
	if (!data->tso || (open(data->tso, O_RDONLY) == -1))
		error++;
	if (!data->twe || (open(data->twe, O_RDONLY) == -1))
		error++;
	if (!data->tea || (open(data->tea, O_RDONLY) == -1))
		error++;
	if (error != 0)
	{
		printf("Error : textures are not defined correctly (can't open or missing texture)\n");
		return (1);
	}
	if (!data->frgb || !data->crgb)
		error++;
	if (error != 0)
	{
		printf("Error : floor or/and ceiling color(s) are not defined correctly\n");
		return (1);
	}
	return (0);
}

int	check_ppm(t_game *data) //ok
{
	int	error;

	error = 0;
	if (ft_strnrchr(data->tno, ".ppm") != 1)
		error++;
	if (ft_strnrchr(data->tso, ".ppm") != 1)
		error++;
	if (ft_strnrchr(data->tea, ".ppm") != 1)
		error++;
	if (ft_strnrchr(data->twe, ".ppm") != 1)
		error++;
	if (error != 0)
	{
		printf("Error : Textures must be in .ppm format\n");
		return (1);
	}
	return (0);
}

int	check_error(t_game *game) //maybe ok
{
	if (check_border_map(game) == 1)
		return (1);
	if (check_texture(game) == 1)
		return (1);
	if (check_ppm(game) == 1)
		return (1);

	printf("copy map (char **) before flood fill :\n"); // <<<<<<<<<<<<<<<<<<<<<<<<<<<test
	printmap(game->tmap->copy_map);
	check_right(game);
	printf("copy map (char **) after flood fill :\n"); // <<<<<<<<<<<<<<<<<<<<<<<<<<<test
	printmap(game->tmap->copy_map);
	//for (int i = 0; i < 16; i++)
	//	printf("copy [%zu]=%s=\n", i,data->tmap->copy_map[i]);

	if (game->tmap->map_error != 0)
	{
		printf("Error : the map is not closed\n");
		return (1);
	}
	return (0);
}

void	printmap(char **map) // <<<<<<<<<<<<<<<<<<<<<<<<<test
{
	int y;

	y = 0;
	while (map[y])
	{
		printf("%s\n", map[y]);
		y++;
	}
}