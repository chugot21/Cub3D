/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:40:26 by chugot            #+#    #+#             */
/*   Updated: 2024/01/25 16:11:37 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_wall(t_game *game)
{
	double	atan;
	double	ntan;

	atan = 0;
	ntan = 0;
	game->r = 0;
	game->ra = game->pa - DEGREE_RADIAN * 30;
	limits_rays(game);
	while (game->r < game->win_x)
	{
		horizontal_rays(game, atan);
		vertical_rays(game, ntan);
		low_rays(game);
		fix_fish_eye(game);
		draw_column(game);
		game->ra += DEGREE_RADIAN / 50; //plus mapx > mapy, plus 50 sera grand
		limits_rays(game);
		game->r++;
	}
}

void	limits_rays(t_game *game)
{
	if (game->ra < 0)
		game->ra += 2 * PI;
	if (game->ra > 2 * PI)
		game->ra -= 2 * PI;
}

void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->win_y / 2)
	{
		x = 0;
		while (x < game->win_x)
		{
			my_mlx_pixel_put(game, x, y, game->ccolor);
			x++;
		}
		y++;
	}
	while (y < game->win_y)
	{
		x = 0;
		while (x < game->win_x)
		{
			my_mlx_pixel_put(game, x, y, game->fcolor);
			x++;
		}
		y++;
	}
}

int	ft_raycasting(t_game *game)
{
	game->img = mlx_new_image(game->window.mlx, game->win_x, game->win_y);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	draw_background(game);
	draw_wall(game);
	if (game->map_flag == 1)
		draw_minimap(game);
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->img, 0, 0);
	mlx_destroy_image(game->window.mlx, game->img);
	return (0);
}
