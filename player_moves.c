/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:40:25 by chugot            #+#    #+#             */
/*   Updated: 2023/12/18 21:50:33 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	closew(t_game *game)
{
	////free(game->texture_one);
	//free(game->map);
	//free(game->crgb);
	//free(game->frgb);
	////destroy_all(game);
	write(1, "Don't give up... It's for the weak !\n", 37);
	exit(0);
}
void	move_right(t_game *game)
{
	game->flag_move = 1;
	game->player_pixel.x += cos(P2 + game->pa) * 5;
	game->player_pixel.y += sin(P2 + game->pa) * 5;
}

void	move_left(t_game *game)
{
	game->flag_move = 1;
	game->player_pixel.x += cos(-P2 + game->pa) * 5; 
	game->player_pixel.y += sin(-P2 + game->pa) * 5;
}

void	move_up(t_game *game)
{
	game->flag_move = 1;
	//if (game->map[game->ipy * game->mapx + game->ipx_add_xo] == 0)
		game->player_pixel.x += game->pdelta.x;
	//if (game->map[game->ipy_add_yo * game->mapx + game->ipx] == 0)
		game->player_pixel.y += game->pdelta.y;
}

void	move_down(t_game *game)
{
	game->flag_move = 1;
	//if (game->map[game->ipy *game->mapx + game->ipx_sub_xo] == 0)
		game->player_pixel.x -= game->pdelta.x;
	//if (game->map[game->ipy_sub_yo * game->mapx + game->ipx] == 0)
		game->player_pixel.y -= game->pdelta.y;
}

void	rotate_right(t_game *game)
{
	game->flag_move = 1;
	game->pa += 0.1;
	if (game->pa > 2 * PI)
		game->pa -= 2 * PI;
	game->pdelta.x = cos(game->pa) * 5;
	game->pdelta.y = sin(game->pa) * 5;
}

void	rotate_left(t_game *game)
{
	game->flag_move = 1;
	game->pa -= 0.1;
	if (game->pa < 0)
		game->pa += 2 * PI;
	game->pdelta.x = cos(game->pa) * 5;
	game->pdelta.y = sin(game->pa) * 5;
}

void	init_collisions_updown(t_game *game)
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
	init_collisions_updown(game);
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

/*void	move_player(t_game *game)
{
	if (game->move_right == 1)
		move_right(game);
	if (game->move_left == 1)
		move_left(game);
	if (game->move_up == 1)
	{
		printf("test up\n");
		move_up(game);
	}
	if (game->move_down == 1)
		move_down(game);
	if (game->rotate_right == 1)
	{
		printf("test rright\n");
		rotate_right(game);
	}
	if (game->rot_left == 1)
		rotate_left(game);
	moves_disactivated(game);
}*/

/*int	moves_activated(int keycode, t_game *game)
{
	game->flag_move = 1;
	if (keycode == 100)
		game->move_right == 1;
	if (keycode == 97)
		game->move_left == 1;
	if (keycode == 119)
		game->move_up == 1;
	if (keycode == 115)
		game->move_down == 1;
	if (keycode == 65363)
		game->rotate_right == 1;
	if (keycode == 65361)
		game->rot_left == 1;
	if (keycode == 65307)
		closew(game);
	printf("flag move activate %d, flag rotate left %d\n", game->flag_move, game->rot_left);
	return (0);
}

void moves_disactivated(t_game *game)
{
	game->move_right == 0;
	game->move_left == 0;
	game->move_up == 0;
	game->move_down == 0;
	game->rotate_right == 0;
	game->rot_left == 0;
	
	game->flag_move = 0;
	printf("flag move disactivate %d\n", game->flag_move);
}*/

/*int	moves_disactivated(int keycode, t_game *game)
{
	game->flag_move = 0;
	printf("flag move disactivate %d\n", game->flag_move);
	if (keycode == 100)
		game->move_right == 0;
	if (keycode == 97)
		game->move_left == 0;
	if (keycode == 119)
		game->move_up == 0;
	if (keycode == 115)
		game->move_down == 0;
	if (keycode == 65363)
		game->rotate_right == 0;
	if (keycode == 65361)
		game->rotate_left == 0;
	return (0);
}*/
