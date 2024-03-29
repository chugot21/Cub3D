/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:37:33 by chugot            #+#    #+#             */
/*   Updated: 2024/02/02 12:32:07 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_moves(t_game *game)
{
	game->move_left = 0;
	game->move_right = 0;
	game->move_up = 0;
	game->move_down = 0;
	game->rot_left = 0;
	game->rotate_right = 0;
	game->proportion = proportions_minimap(game);
	if (game->proportion == -1)
		game->map_flag = -1;
	else
		game->map_flag = 0;
}

void	init_direction(t_game *game)
{
	if (game->dir == 'N')
	{
		game->pa = PI * 1.5;
	}
	if (game->dir == 'S')
	{
		game->pa = PI / 2;
	}
	if (game->dir == 'W')
	{
		game->pa = 0;
	}
	if (game->dir == 'E')
	{
		game->pa = PI;
	}
	game->pdelta.x = cos(game->pa) * 5;
	game->pdelta.y = sin(game->pa) * 5;
	init_moves(game);
}

void	init_game(t_game *game)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < game->maps)
	{
		if (game->map[i] == 7)
		{
			y = i / game->mapx;
			x = (i - (game->mapx * y));
			game->player_pixel.x = (x + 0.5) * 64;
			game->player_pixel.y = (y + 0.5) * 64;
			init_direction(game);
			game->map[i] = 0;
		}
		i++;
	}
	ft_textures(game);
}
