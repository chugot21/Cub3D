/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:40:57 by chugot            #+#    #+#             */
/*   Updated: 2023/12/22 16:06:13 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_game *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	color_square(t_game *game, int x, int y, int width, int heigth, int color)
{
	int tempx;

	tempx = x;
	while (y <= heigth)
	{
		x = tempx;
		while (x <= width)
		{
			my_mlx_pixel_put(game, x, y, color); //LA x et y ou ca commence.
			x++;
		}
		y++;
	}
}

void	draw_player(t_game *game)
{
	double px;
	double py;
	int	i;
	int	j;

	px = (game->player_pixel.x + 10) * 10 / 64;
	py = (game->player_pixel.y + 10) * 10 / 64;
	i = py - 2;
	j = px - 2;
	my_mlx_pixel_put(game, px - 1, py - 1, 0x94120d);
	my_mlx_pixel_put(game, px - 1, py + 1, 0x94120d);
	my_mlx_pixel_put(game, px + 1, py + 1, 0x94120d);
	my_mlx_pixel_put(game, px + 1, py - 1, 0x94120d);
	while (i <= py + 2)
	{
		my_mlx_pixel_put(game, px, i, 0x94120d);
		i++;
	}
	while (j <= px + 2)
	{
		my_mlx_pixel_put(game, j, py, 0x94120d);
		j++;
	}
}

void	draw_minimap(t_game *game)
{
	int i;
	int	x;
	int	y;

	i = 0;
	while (i < game->maps)
	{
		if (game->map[i] == 1)
		{
			y = (i / game->mapx);
			x = (i - game->mapx * y);
			color_square(game, (x * 10 + 1), (y * 10 + 1), (x * 10 + 9), (y * 10 + 9), 0xFFFFFF); //walls
		}
		else
		{
			y = i / game->mapx;
			x = i - game->mapx * y;
			color_square(game, (x * 10 + 1), (y * 10 + 1), (x * 10 + 9), (y * 10 + 9), 0x009966); //floor
		}
		i++;
	}
	draw_player(game);
}

int	find_pixel_color(t_game *game, int x, int y, int *texture)
{
	int pixel;
	int r;
	int g;
	int b;

	pixel = ((int)y * 32 + (int)x) * 3;
	r = texture[pixel + 0];
	g = texture[pixel + 1];
	b = texture[pixel + 2];
	return(create_hexa_rgb(r, g, b));
}

void	draw_column(t_game *game)
{
	int start_pixel;
	int end_pixel;

	game->line_height = (game->maps * game->win_y) / game->dist; //espace plein dans la colonne /mur a dessiner.
	game->ty_step = 32 / (float)game->line_height;
	game->ty_off = 0;
	if (game->line_height > game->win_y)
	{
		game->ty_off = (game->line_height - game->win_y) / 2;
		game->line_height = game->win_y;
	}
	game->line_offset = (game->win_y / 2) - game->line_height / 2; //espace vide dans la colonne.
	game->texture_iy = game->ty_off * game->ty_step;
	if (game->shade == 1)
	{
		game->texture_ix = (int)(game->ray.x / 2) % 32;
		if (game->ra > 180)
			game->texture_ix = 31 - game->texture_ix;
	}
	else
	{
		game->texture_ix = (int) (game->ray.y / 2) % 32;
		if (game->ra > 90 && game->ra < 270)
			game->texture_ix = 31 - game->texture_ix;
	}
	start_pixel = game->line_offset;
	end_pixel = game->win_y - game->line_offset;
	while (start_pixel < end_pixel)
	{
		if (game->side == 0 && ((game->ra >= 0)) && (game->ra < PI))
			my_mlx_pixel_put(game, game->r, start_pixel, find_pixel_color(game, game->texture_ix, game->texture_iy, game->t_north));
		if (game->side == 0 &&  (game->ra >= PI && game->ra < 2 * PI))
			my_mlx_pixel_put(game, game->r, start_pixel, find_pixel_color(game, game->texture_ix, game->texture_iy, game->t_south));
		if (game->side == 1 && (game->ra >= P2 && game->ra < P3))
			my_mlx_pixel_put(game, game->r, start_pixel, find_pixel_color(game, game->texture_ix, game->texture_iy, game->t_east));
		if (game->side == 1 && ((game->ra >= 0 && game->ra < P2) || (game->ra < (2 * PI) && game->ra >= P3)))
			my_mlx_pixel_put(game, game->r, start_pixel, find_pixel_color(game, game->texture_ix, game->texture_iy, game->t_west));
		start_pixel++;
		game->texture_iy += game->ty_step;
	}
}

void	draw_background(t_game *game)
{
	int x;
	int y;

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

int	create_hexa_rgb(int r, int g, int b)
{
	int color;
	
	color = ((r & 0xff) << 16) + ((g & 0xff) << 8) + ((b & 0xff));
	return(color);
}

