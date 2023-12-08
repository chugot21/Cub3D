/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:37:33 by chugot            #+#    #+#             */
/*   Updated: 2023/12/08 16:27:29 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_moves(t_game *game)
{
	game->move_left = 0;
	game->move_right = 0;
	game->move_up = 0;
	game->move_down = 0;
	game->rotate_left = 0;
	game->rotate_right = 0;
}

void	init_direction_WE(t_game *game)
{
	if (game->dir == 'W')
	{
		game->pa = PI;
		//game->pdelta.x = cos(game->pa) * 5;
		//game->pdelta.y = sin(game->pa) * 5;
		//game->vec_plan.x = -0.66;
		//game->vec_plan.y = 0;
	}
	if (game->dir == 'E')
	{
		game->pa = 0;
		//game->vec_dir.x = 0;
		//game->vec_dir.y = 1;
		//game->vec_plan.x = 0.66;
		//game->vec_plan.y = 0;
	}
	game->pdelta.x = cos(game->pa) * 5;
	game->pdelta.y = sin(game->pa) * 5;
	init_moves(game);
}

void	init_direction(t_game *game)
{
	if (game->dir == 'N')
	{
		game->pa = PI / 2;
		//game->vec_dir.x = -1;
		//game->vec_dir.y = 0;
		//game->vec_plan.x = 0;
		//game->vec_plan.y = 0.66;
	}
	if (game->dir == 'S')
	{
		game->pa = PI * 1.5;
		//game->vec_dir.x = 1;
		//game->vec_dir.y = 0;
		//game->vec_plan.x = 0;
		//game->vec_plan.y = -0.66;
	}
	init_direction_WE(game);
}

void	init_game(t_game *game)
{
	int i;
	int x;
	int y;

	i = 0;
	while (i <= game->maps)
	{
		if (game->map[i] == 7)
		{
			y = i / game->mapx;
			x = (i - (game->mapx * y));
			game->player.x = x + 0.5;
			game->player.y = y + 0.5;
			game->player_pixel.x = (x + 0.5) * 10;
			game->player_pixel.y = (y + 0.5) * 10;
			init_direction(game);
		}
		i++;
	}
}

