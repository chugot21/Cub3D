/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 19:19:23 by chugot            #+#    #+#             */
/*   Updated: 2023/12/27 19:19:24 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_right(t_game *game)
{
	game->player_pixel.x += cos(P2 + game->pa) * 5;
	game->player_pixel.y += sin(P2 + game->pa) * 5;
}

void	move_left(t_game *game)
{
	game->player_pixel.x += cos(-P2 + game->pa) * 5;
	game->player_pixel.y += sin(-P2 + game->pa) * 5;
}

void	move_up(t_game *game)
{
	if (game->map[game->ipy * game->mapx + game->ipx_add_xo] == 0)
		game->player_pixel.x += game->pdelta.x;
	if (game->map[game->ipy_add_yo * game->mapx + game->ipx] == 0)
		game->player_pixel.y += game->pdelta.y;
}

void	move_down(t_game *game)
{
	if (game->map[game->ipy * game->mapx + game->ipx_sub_xo] == 0)
		game->player_pixel.x -= game->pdelta.x;
	if (game->map[game->ipy_sub_yo * game->mapx + game->ipx] == 0)
		game->player_pixel.y -= game->pdelta.y;
}
