/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 23:24:40 by chugot            #+#    #+#             */
/*   Updated: 2024/01/18 16:33:03 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	engine(t_game *game)
{
	game->win_x = 960;
	game->win_y = 540;
	init_game(game);
	game->window.mlx = mlx_init();
	game->window.win = mlx_new_window (game->window.mlx,
			game->win_x,
			game->win_y, "Club 3D");
	ft_raycasting(game);
	mlx_hook(game->window.win, 2, 1L << 0, move_player, &game);
	mlx_hook(game->window.win, 17, 1L << 9, closew, &game);
	mlx_loop(game->window.mlx);
}
