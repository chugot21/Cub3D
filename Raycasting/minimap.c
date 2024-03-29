/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:40:26 by chugot            #+#    #+#             */
/*   Updated: 2024/02/02 12:35:47 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	proportions_minimap(t_game *game)
{
	float	nb_pixelx;
	float	nb_pixely;

	nb_pixelx = (game->win_x / game->mapx) / 3;
	nb_pixely = (game->win_y / game->mapy) / 3;
	if (nb_pixelx < 5 || nb_pixely < 5)
	{
		printf("map too large for the screen, can't display minimap\n");
		return (-1);
	}
	if (nb_pixelx > nb_pixely)
		return ((int)nb_pixely);
	else
		return ((int)nb_pixelx);
}

void	draw_player_next(t_game *game, int x, int y)
{
	int		i;

	i = 0;
	while (y <= game->draw_py)
	{
		x = game->draw_px - i;
		while (x <= (game->draw_px + i))
			my_mlx_pixel_put(game, y, x++, 0x94120d);
		y++;
		i++;
	}
	i -= 2;
	while (y <= game->draw_py + game->width_player / 2)
	{
		x = game->draw_px - i;
		while (x <= (game->draw_px + i))
			my_mlx_pixel_put(game, y, x++, 0x94120d);
		y++;
		i--;
	}
}

void	draw_player(t_game *game)
{
	int		x;
	int		y;

	game->draw_px = (game->player_pixel.y) * game->proportion / 64;
	game->draw_py = (game->player_pixel.x) * game->proportion / 64;
	game->width_player = game->proportion / 5;
	if (game->width_player % 2 != 0)
		game->width_player += 1;
	x = game->draw_px;
	y = game->draw_py - game->width_player / 2;
	draw_player_next(game, x, y);
}

void	color_square(t_game *game, int x, int y)
{
	int	tempx;
	int	newx;
	int	newy;
	int	heigth;
	int	width;

	newx = x * game->proportion + 1;
	newy = y * game->proportion + 1;
	width = newx + game->proportion - 2;
	heigth = newy + game->proportion - 2;
	tempx = newx;
	while (newy <= heigth)
	{
		newx = tempx;
		while (newx <= width)
		{
			my_mlx_pixel_put(game, newx, newy, game->color);
			newx++;
		}
		newy++;
	}
}

void	draw_minimap(t_game *game)
{
	int	i;
	int	x;
	int	y;

	i = -1;
	while (i++ < game->maps - 1)
	{
		if (game->minimap[i] == 1)
		{
			y = (i / game->mapx);
			x = (i - game->mapx * y);
			game->color = 0x171717;
			color_square(game, x, y);
		}
		else if (game->minimap[i] == 0 || game->minimap[i] == 7)
		{
			y = i / game->mapx;
			x = i - game->mapx * y;
			game->color = 0xF9F9F9;
			color_square(game, x, y);
		}
	}
	draw_player(game);
}
