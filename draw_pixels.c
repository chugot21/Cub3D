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
	*(unsigned int *)dst = color;
}

void	color_square(t_game *game, int x, int y, int width, int heigth, int color)
{
	int	tempx;

	tempx = x;
	while (y <= heigth)
	{
		x = tempx;
		while (x <= width)
		{
			my_mlx_pixel_put(game, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_game *game)
{
	double	px;
	double	py;
	int		i;
	int		j;

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

int	create_hexa_rgb(int r, int g, int b)
{
	int	color;

	color = ((r & 0xff) << 16) + ((g & 0xff) << 8) + ((b & 0xff));
	return (color);
}
