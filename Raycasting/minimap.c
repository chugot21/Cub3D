/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:40:26 by chugot            #+#    #+#             */
/*   Updated: 2024/01/18 18:17:06 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int    proportions_minimap(t_game *game)
{
    float nb_pixelx;
    float nb_pixely;

    nb_pixelx = game->win_x / game->mapx;
    nb_pixely = game->win_y / game->mapy;
    if (nb_pixelx < 1 || nb_pixely < 1) //inferieur a 5 car la taille du player est de 5 par 5 ?
    {
        printf("map too large for the screen, can't display minimap\n");
        return (-1);
    }
    if (nb_pixelx > nb_pixely)
        return ((int)nb_pixely);
    else
        return ((int)nb_pixelx);
}

void	draw_player(t_game *game)
{
	double	px;
	double	py;
	int		i;
	int		j;

	px = (game->player_pixel.x) * game->proportion / 64;
	py = (game->player_pixel.y) * game->proportion / 64;
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

void	color_square(t_game *game, int x, int y)
{
	int	tempx;
    int newx;
    int newy;
	int	heigth;
    int width;

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
		if (game->map[i] == 1)
		{
			y = (i / game->mapx);
			x = (i - game->mapx * y);
			game->color = 0x171717;
			color_square(game, x, y);
		}
		else
		{
			y = i / game->mapx;
			x = i - game->mapx * y;
			game->color = 0xF9F9F9;
			color_square(game, x, y);
		}
	}
	draw_player(game);
}
