/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:26:52 by chugot            #+#    #+#             */
/*   Updated: 2023/12/27 18:26:55 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	horizontal_rays_next(game, atan);
}

void	horizontal_rays_next(t_game *game, double atan)
{
	if (game->ra == 0 || game->ra == PI)
	{
		game->ray.x = game->player_pixel.x;
		game->ray.y = game->player_pixel.y;
		game->dof = game->win_x;
	}
	while (game->dof < game->win_x)
	{
		game->m.x = (int)(game->ray.x) >> 6;
		game->m.y = (int)(game->ray.y) >> 6;
		game->mp = game->m.y * game->mapx + game->m.x;
		if (game->mp > 0 && game->mp < game->maps && game->map[game->mp] == 1)
		{
			game->horizon.x = game->ray.x;
			game->horizon.y = game->ray.y;
			game->dis_horiz = dist(game->player_pixel.x, game->player_pixel.y,
					game->horizon.x, game->horizon.y, game->ra);
			game->dof = game->win_x;
		}
		else
		{
			game->ray.x += game->xoyo.x;
			game->ray.y += game->xoyo.y;
			game->dof++;
		}
	}
}

void	vertical_rays(t_game *game, double ntan)
{
	game->dof = 0;
	ntan = -tan(game->ra);
	game->dis_verti = 1000000;
	game->vertical.x = game->player_pixel.x;
	game->vertical.y = game->player_pixel.y;
	if (game->ra > P2 && game->ra < P3)
	{
		game->ray.x = (((int)game->player_pixel.x >> 6) << 6) - 0.0001;
		game->ray.y = (game->player_pixel.x - game->ray.x)
			* ntan + game->player_pixel.y;
		game->xoyo.x = -64;
		game->xoyo.y = -game->xoyo.x * ntan;
	}
	if (game->ra < P2 || game->ra > P3)
	{
		game->ray.x = (((int)game->player_pixel.x >> 6) << 6) + 64;
		game->ray.y = (game->player_pixel.x - game->ray.x)
			* ntan + game->player_pixel.y;
		game->xoyo.x = 64;
		game->xoyo.y = -game->xoyo.x * ntan;
	}
	vertical_rays_next(game, ntan);
}

void	vertical_rays_next(t_game *game, double ntan)
{
	if (game->ra == 0 || game->ra == PI)
	{
		game->ray.x = game->player_pixel.x;
		game->ray.y = game->player_pixel.y;
		game->dof = game->win_y;
	}
	while (game->dof < game->win_y)
	{
		game->m.x = (int)(game->ray.x) >> 6;
		game->m.y = (int)(game->ray.y) >> 6;
		game->mp = game->m.y * game->mapx + game->m.x;
		if (game->mp > 0 && game->mp < game->maps && game->map[game->mp] == 1)
		{
			game->vertical.x = game->ray.x;
			game->vertical.y = game->ray.y;
			game->dis_verti = dist(game->player_pixel.x, game->player_pixel.y,
					game->vertical.x, game->vertical.y, game->ra);
			game->dof = game->win_y;
		}
		else
		{
			game->ray.x += game->xoyo.x;
			game->ray.y += game->xoyo.y;
			game->dof++;
		}
	}
}

void	low_rays(t_game *game)
{
	game->shade = 1;
	if (game->dis_verti < game->dis_horiz)
	{
		game->ray.x = game->vertical.x;
		game->ray.y = game->vertical.y;
		game->dist = game->dis_verti;
		game->shade = 0.5;
		game->side = 1;
	}
	if (game->dis_verti > game->dis_horiz)
	{
		game->ray.x = game->horizon.x;
		game->ray.y = game->horizon.y;
		game->dist = game->dis_horiz;
		game->side = 0;
	}
}
