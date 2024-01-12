/*
#include "../cub3d.h"

void	rotate_player(t_game *data, double angle)
{
	double	old_dirx;
	double	old_planex;
	data->tmap->x_wall = data->player.y;
	data->tmap->y_wall = data->player.x;


	old_dirx = data->ray_i->dirx;
	old_planex = data->ray_i->planex;
	data->ray_i->dirx = (old_dirx * cos
			(angle)) - (data->ray_i->diry * sin(angle));
	data->ray_i->diry = (old_dirx * sin
			(angle)) + (data->ray_i->diry * cos(angle));
	data->ray_i->planex = (old_planex * cos
			(angle)) - (data->ray_i->planey * sin(angle));
	data->ray_i->planey = (old_planex * sin
			(angle)) + (data->ray_i->planey * cos(angle));
}*/
