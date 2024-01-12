
#include "../cub3d.h"

void	copy_other_line_map(t_game *data, int fd, char *buff)
{
	size_t	x;
	size_t	y;
	size_t	y_2;

	y_2 = 0;
	y = 1;
	while (y < data->tmap->y_map + y_2)
	{
		x = 0;
		buff = get_next_line(data, fd);
		if (!buff)
			break ;
		while (buff[x] && x < data->tmap->x_map)
		{
			//check_character(data, buff[x], x, y); // a set up pour lorientation du player 
			data->player.x = y;
			data->player.y = x;
			data->tmap->map[y][x] = buff[x];
			x++;
		}
		data->tmap->map[y][x] = '\0';
		if (ft_strstr(buff, "1") != 0)
			y++;
		else
			y_2++;
		free(buff);
		data->tmap->y_map_trace = y;
	}
}

void	copy_first_line_map(t_game *data, char *buff, int fd)
{
	size_t	x;
	size_t	y;

	y = 0;
	x = 0;
	if (data->tmap->trace_first_line != 0)
	{
		data->tmap->map[data->tmap->y_map_trace] = ft_strdup(data, buff);
		return;
	}
	data->tmap->trace_first_line++;
	while (buff[x] && x < data->tmap->x_map)
	{
		data->tmap->map[y][x] = buff[x];
		x++;
	}
	data->tmap->map[y][x] = '\0';
	data->tmap->trace++;
	copy_other_line_map(data, fd, buff);
}