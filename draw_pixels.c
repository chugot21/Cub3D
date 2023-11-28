/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:40:57 by chugot            #+#    #+#             */
/*   Updated: 2023/11/24 17:40:38 by clara            ###   ########.fr       */
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
	int	i;
	int	j;

	i = game->player_pixel.y - 2;
	j = game->player_pixel.x - 2;
	my_mlx_pixel_put(game, game->player_pixel.x - 1, game->player_pixel.y - 1, 0x94120d);
	my_mlx_pixel_put(game, game->player_pixel.x - 1, game->player_pixel.y + 1, 0x94120d);
	my_mlx_pixel_put(game, game->player_pixel.x + 1, game->player_pixel.y + 1, 0x94120d);
	my_mlx_pixel_put(game, game->player_pixel.x + 1, game->player_pixel.y - 1, 0x94120d);
	while (i <= game->player_pixel.y + 2)
	{
		my_mlx_pixel_put(game, game->player_pixel.x, i, 0x94120d);
		i++;
	}
	while (j <= game->player_pixel.x + 2)
	{
		my_mlx_pixel_put(game, j, game->player_pixel.y, 0x94120d);
		j++;
	}
}

void	draw_minimap(t_game *game)
{
	int	i; // i = y
	int	j; // j = x

	i = 1;
	while (game->map[i - 1] != NULL)
	{
		j = 1;
		while (game->map[i - 1][j - 1])
		{
			if (game->map[i - 1][j - 1] == '1')
				color_square(game, (j * 10 + 1), (i * 10 + 1), (j * 10 + 9), (i * 10 + 9), 0xf6f7f2); //red
			else
				color_square(game, (j * 10 + 1), (i * 10 + 1), (j * 10 + 9), (i * 10 + 9), 0x0000FF00); //vert
			j++;
		}
		i++;
	}
	draw_player(game);
	mlx_put_image_to_window(game->window.mlx, game->window.win, game->img, 0, 0);
}
