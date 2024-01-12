
#include "../cub3d.h"

int	check_player(t_game *data)
{
	size_t	y;
	size_t	x;
	int	player;

	player = 0;
	y = 0;
	while (y < data->tmap->y_map - 1)
	{
		x = 0;
		while (data->tmap->map[y][x] && x < data->tmap->x_map)
		{
			if (data->tmap->map[y][x] && is_players
				(data->tmap->map[y][x]) == 1)
			{
				data->tmap->map[y][x] = '7';
				data->tmap->start_player.x = x;
				data->tmap->start_player.y = y;
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

int	check_name(char *argv)
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

int	check_xpm(t_game *data)
{
	int	error;

	error = 0;
	if (ft_strnrchr(data->tmap->no1, ".xpm") != 1)
		error++;
	if (ft_strnrchr(data->tmap->so1, ".xpm") != 1)
		error++;
	if (ft_strnrchr(data->tmap->ea1, ".xpm") != 1)
		error++;
	if (ft_strnrchr(data->tmap->we1, ".xpm") != 1)
		error++;
	if (error != 0)
	{
		printf("Error : Textures must be in .xpm format\n");
		return (1);
	}
	return (0);
}

int	check_error(t_game *data, char *argv)
{
	if (check_border_map(data) == 1)
		return (1);
	if (check_texture(data) == 1)
		return (1);
	if (check_name(argv) == 1)
		return (1);
	if (check_xpm(data) == 1)
		return (1);
	check_right(data);
	//for (size_t i = 0; i < 16; i++)
	//	printf("copy [%zu]=%s=\n", i,data->tmap->copy_map[i]);
	if (data->tmap->map_error != 0)
	{
		printf("Error : the map is not closed\n");
		return (1);
	}
	return (0);
}