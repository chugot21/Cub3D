/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:40:25 by chugot            #+#    #+#             */
/*   Updated: 2023/12/08 16:06:18 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	closew(t_game *game)
{
	//destroy_all(game);
	write(1, "Don't give up... It's for the weak !\n", 37);
	exit(0);
}
void	move_right(t_game *game) //revoir car n'avance pas en tournant
{
	game->player_pixel.x += cos(P2 + game->pa) * 5;
	game->player_pixel.y += sin(P2 + game->pa) * 5;
}

void	move_left(t_game *game) //revoir car n'avance pas en tournant
{
	game->player_pixel.x += cos(-P2 + game->pa) * 5; 
	game->player_pixel.y += sin(-P2 + game->pa) * 5;
}

void	move_up(t_game *game)
{
	//int position;
//
	//position = (int)game->player_pixel.x / 10 + game->player_pixel.y / 10 * game->mapx - 1;
	//printf("position up : %d\n", position);
	//if (game->map[position] == 0)
	//{
		game->player_pixel.x += game->pdelta.x;
		game->player_pixel.y += game->pdelta.y;
	//}
}

void	move_down(t_game *game)
{
	//int position;
//
	//position = (int)game->player_pixel.x / 10 + game->player_pixel.y / 10 * game->mapx;
	//printf("position down : %d\n", position);
	//if (game->map[position] == 0)
	//{
		game->player_pixel.x -= game->pdelta.x;
		game->player_pixel.y -= game->pdelta.y;
	//}
}

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

int	move_player(int keycode, t_game *game)
{
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
	return (0);
}

