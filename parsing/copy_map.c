
#include "../cub3d.h"

void	copy_other_line_map(t_game *game, int fd, char *buff) //bof sure
{
	int	x;
	int	y;
	int	y_2;

	y_2 = 0;
	y = 1;
	while (y < game->tmap->y_map + y_2)
	{
		x = 0;
		buff = get_next_line_special(game, fd); //buff = get_next_line(data, fd);
		if (!buff)
			break ;
		while (buff[x] && x < game->tmap->x_map)
		{
			//check_character(data, buff[x], x, y); // a set up pour lorientation du player 
			game->player.x = y; // ->utilite ?
			game->player.y = x; // ->utilite ?
			game->tmap->map[y][x] = buff[x];
			x++;
		}
		game->tmap->map[y][x] = '\0';
		if (ft_strstr(buff, "1") != 0)
			y++;
		else
			y_2++;
		free(buff);
		game->tmap->y_map_trace = y;
	}
}

void	copy_first_line_map(t_game *game, char *buff, int fd) //mouais bof compris, a quoi sert le premier if ? initialise a 0 de base
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	if (game->tmap->trace_first_line != 0)
	{
		game->tmap->map[game->tmap->y_map_trace] = ft_strdup(game, buff);
		return;
	}
	game->tmap->trace_first_line++;
	while (buff[x] && x < game->tmap->x_map)
	{
		game->tmap->map[y][x] = buff[x];
		x++;
	}
	game->tmap->map[y][x] = '\0';
	game->tmap->trace++;
	copy_other_line_map(game, fd, buff);
}