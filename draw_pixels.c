/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:40:57 by chugot            #+#    #+#             */
/*   Updated: 2023/12/08 17:02:18 by clara            ###   ########.fr       */
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

/*void	draw_direction_line(t_game *game)
{
	int xmax;
	int ymax;
	int deltax;
	int deltay;

	deltax = game->pdelta.x; //valeur absolue
	deltay = game->pdelta.y;
	if (deltax < 0)
		deltax = deltax * -1;
	if (deltay < 0)
		deltay = deltay * -1;
	xmax = (int)game->player_pixel.x + game->pdelta.x; //point exact sur la carte.
	ymax = (int)game->player_pixel.y + game->pdelta.y;
	my_mlx_pixel_put(game, xmax, ymax, 0x94120d);
	while (xmax != (int)game->player_pixel.x || ymax != (int)game->player_pixel.y)
	{
		printf("xmax : %d, playerpixel.x : %f, deltax : %d, ymax : %d, playerpixel.y : % f, deltay : %d\n", xmax, game->player_pixel.x, deltax, ymax, game->player_pixel.y, deltay);
		if (deltax <= deltay && ymax > (int)game->player_pixel.y)
		{
			deltay--;
			if (game->pdelta.y < 0)
				ymax++;
			else 
				ymax--;
		}
		if (deltax > deltay && xmax > (int)game->player_pixel.x)
		{
			deltax--;
			if (game->pdelta.x < 0)
				xmax++;
			else	
				xmax--;
		}
		my_mlx_pixel_put(game, xmax, ymax, 0x94120d);
	}
}*/

void	draw_player(t_game *game)
{
	int	i;
	int	j;

	//i = game->player.y - 2;
	//j = game->player.x - 2;
	//my_mlx_pixel_put(game, game->player.x - 1, game->player.y - 1, 0x94120d);
	//my_mlx_pixel_put(game, game->player.x - 1, game->player.y + 1, 0x94120d);
	//my_mlx_pixel_put(game, game->player.x + 1, game->player.y + 1, 0x94120d);
	//my_mlx_pixel_put(game, game->player.x + 1, game->player.y - 1, 0x94120d);
	//while (i <= game->player.y + 2)
	//{
	//	my_mlx_pixel_put(game, game->player.x, i, 0x94120d);
	//	i++;
	//}
	//while (j <= game->player.x + 2)
	//{
	//	my_mlx_pixel_put(game, j, game->player.y, 0x94120d);
	//	j++;
	//}

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
			color_square(game, (x * 10 + 1), (y * 10 + 1), (x * 10 + 9), (y * 10 + 9), 0xf6f7f2); //white
		}
		else
		{
			y = i / game->mapx;
			x = i - game->mapx * y;
			color_square(game, (x * 10 + 1), (y * 10 + 1), (x * 10 + 9), (y * 10 + 9), 0x0000FF00); //black
		}
		i++;
	}
	draw_player(game);
}

void	draw_column(t_game *game)
{
	int start_pixel;
	int end_pixel;

	game->line_height = (game->maps * game->win_y) / game->dist; //espace plein dans la colonne /mur a dessiner.
	if (game->line_height > game->win_y)
		game->line_height = game->win_y;
	game->line_offset = (game->win_y / 2) - game->line_height / 2; //espace vide dans la colonne.
	start_pixel = game->line_offset;
	end_pixel = game->win_y - game->line_offset;
	while (start_pixel < end_pixel)
	{
		my_mlx_pixel_put(game, game->r, start_pixel, game->color);
		start_pixel++;
	}
}
