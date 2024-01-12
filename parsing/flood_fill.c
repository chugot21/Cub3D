
#include "../cub3d.h"

void	check_right(t_game *data)
{
	check_exit(data);
	if (data->tmap->copy_map[data->tmap->y_wall + 1]
		[data->tmap->x_wall] == '0'
		|| data->tmap->copy_map[data->tmap->y_wall + 1]
		[data->tmap->x_wall] == ' ')
	{
		data->tmap->y_wall++;
		data->tmap->copy_map[data->tmap->y_wall][data->tmap->x_wall] = '2';
		check_right(data);
		data->tmap->y_wall--;
	}
	check_down(data);
}

void	check_down(t_game *data)
{
	check_exit(data);
	if (data->tmap->copy_map[data->tmap->y_wall]
		[data->tmap->x_wall + 1] == '0'
		|| data->tmap->copy_map[data->tmap->y_wall]
		[data->tmap->x_wall + 1] == ' ')
	{
		data->tmap->x_wall++;
		data->tmap->copy_map[data->tmap->y_wall]
		[data->tmap->x_wall] = '2';
		check_right(data);
		data->tmap->x_wall--;
	}
	check_left(data);
}

void	check_left(t_game *data)
{
	check_exit(data);
	if (data->tmap->copy_map[data->tmap->y_wall - 1]
		[data->tmap->x_wall] == '0'
		|| data->tmap->copy_map[data->tmap->y_wall - 1]
		[data->tmap->x_wall] == ' ')
	{
		data->tmap->y_wall--;
		data->tmap->copy_map[data->tmap->y_wall]
		[data->tmap->x_wall] = '2';
		check_right(data);
		data->tmap->y_wall++;
	}
	check_up(data);
}

void	check_up(t_game *data)
{
	check_exit(data);
	if (data->tmap->copy_map[data->tmap->y_wall]
		[data->tmap->x_wall - 1] == '0'
		|| data->tmap->copy_map[data->tmap->y_wall]
		[data->tmap->x_wall - 1] == ' ')
	{
		data->tmap->x_wall--;
		data->tmap->copy_map[data->tmap->y_wall]
		[data->tmap->x_wall] = '2';
		check_right(data);
		data->tmap->x_wall++;
	}
	check_exit(data);
}