/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:36:35 by chugot            #+#    #+#             */
/*   Updated: 2024/02/02 13:51:21 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	dist(double ax, double ay, double bx, double by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	fix_fish_eye(t_game *game)
{
	float i;

	game->ca = game->pa - game->ra;
	if (game->ca < 0)
		game->ca += 2 * PI;
	if (game->ca > 2 * PI)
		game->ca -= 2 * PI;
	game->dist = game->dist * cos(game->ca);
	if (game->mapx > game->mapy)
		i = game->mapx / game->mapy;
	else
		i = game->mapy / game->mapx;
	if (i < 1)
		i = 1;
	game->line_height = (game->maps * game->win_y) / (game->dist * game->mapx / (4 * i));
}

void	draw_column(t_game *game)
{
	game->ty_step = 32 / (float)game->line_height;
	game->ty_off = 0;
	if (game->line_height > game->win_y)
	{
		game->ty_off = (game->line_height - game->win_y) / 2;
		game->line_height = game->win_y;
	}
	game->line_offset = (game->win_y / 2) - game->line_height / 2;
	 game->texture_iy = game->ty_off * game->ty_step;
	if (game->shade == 1)
	{
		game->texture_ix = (int)(game->ray.x / 2) % 32;
		if (game->ra > PI)
			game->texture_ix = 31 - game->texture_ix;
	}
	else
	{
		game->texture_ix = (int)(game->ray.y / 2) % 32;
		if (game->ra > (PI / 2) && game->ra < (3 * PI / 2))
			game->texture_ix = 31 - game->texture_ix;
	}
	draw_column_next(game);
}

void	draw_column_next(t_game *game)
{
	int	start_pixel;
	int	end_pixel;

	start_pixel = game->line_offset;
	end_pixel = game->win_y - game->line_offset;
	while (start_pixel < end_pixel)
	{
		draw_textures(game, start_pixel);
		start_pixel++;
		game->texture_iy += game->ty_step;
	}
}

void	draw_textures(t_game *game, int start_pixel)
{
	if (game->side == 0 && ((game->ra >= 0)) && (game->ra < PI))
		my_mlx_pixel_put(game, game->r, start_pixel,
			find_pixel_color(game->texture_ix,
				game->texture_iy, game->t_north));
	if (game->side == 0 && (game->ra >= PI && game->ra < 2 * PI))
		my_mlx_pixel_put(game, game->r, start_pixel,
			find_pixel_color(game->texture_ix,
				game->texture_iy, game->t_south));
	if (game->side == 1 && (game->ra >= (PI / 2) && game->ra < (3 * PI / 2)))
		my_mlx_pixel_put(game, game->r, start_pixel,
			find_pixel_color(game->texture_ix,
				game->texture_iy, game->t_east));
	if (game->side == 1 && ((game->ra >= 0 && game->ra < (PI / 2))
			|| (game->ra < (2 * PI) && game->ra >= (3 * PI / 2))))
		my_mlx_pixel_put(game, game->r, start_pixel,
			find_pixel_color(game->texture_ix,
				game->texture_iy, game->t_west));
}
