/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:40:25 by chugot            #+#    #+#             */
/*   Updated: 2024/01/18 17:56:33 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_right(t_game *game)
{
	game->pa += 0.1;
	if (game->pa > 2 * PI)
		game->pa -= 2 * PI;
	game->pdelta.x = cos(game->pa) * 5;
	game->pdelta.y = sin(game->pa) * 5;
}

void	rotate_left(t_game *game)
{
	game->pa -= 0.1;
	if (game->pa < 0)
		game->pa += 2 * PI;
	game->pdelta.x = cos(game->pa) * 5;
	game->pdelta.y = sin(game->pa) * 5;
}

void	init_collisions(t_game *game)
{
	if (game->pdelta.x < 0)
		game->xco = -20;
	else
		game->xco = 20;
	if (game->pdelta.y < 0)
		game->yco = -20;
	else
		game->yco = 20;
	game->ipx = game->player_pixel.x / 64;
	game->ipy = game->player_pixel.y / 64;
	game->ipx_add_xo = (game->player_pixel.x + game->xco) / 64;
	game->ipy_add_yo = (game->player_pixel.y + game->yco) / 64;
	game->ipx_sub_xo = (game->player_pixel.x - game->xco) / 64;
	game->ipy_sub_yo = (game->player_pixel.y - game->yco) / 64;
}

int	move_player(int keycode, t_game *game)
{
	init_collisions(game);
	if (keycode == 100)
		move_right(game);
	if (keycode == 97)
		move_left(game);
	if (keycode == 119)
		move_up(game);
	if (keycode == 115)
		move_down(game);
	if (keycode == 65363)
		rotate_right(game);
	if (keycode == 65361)
		rotate_left(game);
	if (keycode == 65307)
		closew(game);
	if (keycode == 65289 && game->map_flag != -1)
	{
		if (game->map_flag == 1)
			game->map_flag = 0;
		else
			game->map_flag = 1;
	}
	ft_raycasting(game);
	return (0);
}
