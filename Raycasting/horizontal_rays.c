/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_rays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:26:52 by chugot            #+#    #+#             */
/*   Updated: 2024/01/30 16:45:07 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	horizontal_rays(t_game *game, double atan)
{
	game->dof = 0;
	atan = -1 / tan(game->ra);
	game->dis_horiz = 1000000;
	game->horizon.x = game->player_pixel.x;
	game->horizon.y = game->player_pixel.y;
	if (game->ra > PI)
	{
		game->ray.y = (((int)game->player_pixel.y >> 6) << 6) - 0.0001;
		game->ray.x = (game->player_pixel.y - game->ray.y)
			* atan + game->player_pixel.x;
		game->xoyo.y = -64;
		game->xoyo.x = -game->xoyo.y * atan;
	}
	if (game->ra < PI)
	{
		game->ray.y = (((int)game->player_pixel.y >> 6) << 6) + 64;
		game->ray.x = (game->player_pixel.y - game->ray.y)
			* atan + game->player_pixel.x;
		game->xoyo.y = 64;
		game->xoyo.x = -game->xoyo.y * atan;
	}
	horizontal_rays_next(game);
}

void	horizontal_rays_next(t_game *game)
{
	if (game->ra == 0 || game->ra == PI)
	{
		game->ray.x = game->player_pixel.x;
		game->ray.y = game->player_pixel.y;
		game->dof = game->win_x;
	}
	while (game->dof < game->win_x)
		horizontal_rays_calcul(game);
}

void	horizontal_rays_calcul(t_game *game)
{
	game->m.x = (int)(game->ray.x) >> 6;
	game->m.y = (int)(game->ray.y) >> 6;
	game->mp = game->m.y * game->mapx + game->m.x;
	if (game->mp > 0 && game->mp < game->maps && game->map[game->mp] == 1)
	{
		game->horizon.x = game->ray.x;
		game->horizon.y = game->ray.y;
		game->dis_horiz = dist(game->player_pixel.x, game->player_pixel.y,
				game->horizon.x, game->horizon.y);
		game->dof = game->win_x;
	}
	else
	{
		game->ray.x += game->xoyo.x;
		game->ray.y += game->xoyo.y;
		game->dof++;
	}
}
