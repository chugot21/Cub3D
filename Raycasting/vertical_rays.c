/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:32:58 by chugot            #+#    #+#             */
/*   Updated: 2023/12/28 18:33:03 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	vertical_rays_next(game);
}

void	vertical_rays_next(t_game *game)
{
	if (game->ra == 0 || game->ra == PI)
	{
		game->ray.x = game->player_pixel.x;
		game->ray.y = game->player_pixel.y;
		game->dof = game->win_y;
	}
	while (game->dof < game->win_y)
		vertical_rays_calcul(game);
}

void	vertical_rays_calcul(t_game *game)
{
	game->m.x = (int)(game->ray.x) >> 6;
	game->m.y = (int)(game->ray.y) >> 6;
	game->mp = game->m.y * game->mapx + game->m.x;
	if (game->mp > 0 && game->mp < game->maps && game->map[game->mp] == 1)
	{
		game->vertical.x = game->ray.x;
		game->vertical.y = game->ray.y;
		game->dis_verti = dist(game->player_pixel.x, game->player_pixel.y,
				game->vertical.x, game->vertical.y);
		game->dof = game->win_y;
	}
	else
	{
		game->ray.x += game->xoyo.x;
		game->ray.y += game->xoyo.y;
		game->dof++;
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
