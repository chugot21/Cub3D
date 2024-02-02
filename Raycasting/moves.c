/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 19:19:23 by chugot            #+#    #+#             */
/*   Updated: 2024/02/02 13:50:35 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_left(t_game *game)
{
	if (game->pa > (3 * PI / 2) || (game->pa > (PI / 2) && game->pa < PI))
	{
		if (game->map[game->ipy * game->mapx + game->ipx_sub_xo] == 0)
			game->player_pixel.x += cos(-(PI / 2) + game->pa) * 5;
		if (game->map[game->ipy_add_yo * game->mapx + game->ipx] == 0)
			game->player_pixel.y += sin(-(PI / 2) + game->pa) * 5;
	}
	else
	{
		if (game->map[game->ipy * game->mapx + game->ipx_add_xo] == 0)
			game->player_pixel.x += cos(-(PI / 2) + game->pa) * 5;
		if (game->map[game->ipy_sub_yo * game->mapx + game->ipx] == 0)
			game->player_pixel.y += sin(-(PI / 2) + game->pa) * 5;
	}
}
void	move_right(t_game *game)
{
	if (game->pa < (PI / 2) || (game->pa > PI && game->pa < (3 * PI / 2)))
	{
		if (game->map[game->ipy * game->mapx + game->ipx_sub_xo] == 0)
			game->player_pixel.x += cos((PI / 2) + game->pa) * 5;
		if (game->map[game->ipy_add_yo * game->mapx + game->ipx] == 0)
			game->player_pixel.y += sin((PI / 2) + game->pa) * 5;
	}
	else
	{
		if (game->map[game->ipy * game->mapx + game->ipx_add_xo] == 0)
			game->player_pixel.x += cos((PI / 2) + game->pa) * 5;
		if (game->map[game->ipy_sub_yo * game->mapx + game->ipx] == 0)
			game->player_pixel.y += sin((PI / 2) + game->pa) * 5;
	}
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
