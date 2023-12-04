/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:40:25 by chugot            #+#    #+#             */
/*   Updated: 2023/12/04 13:59:23 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	closew(t_game *game)
{
	//destroy_all(game);
	write(1, "Don't give up... It's for the weak !\n", 37);
	exit(0);
}
void	move_right(t_game *game)
{
	//if (game->map[(int)(game->player.x + (game->vec_dir.y * game->movespeed * 2))][(int)game->player.y] == '0')
	//	game->player.x += game->vec_dir.y * game->movespeed;
	//if (game->map[(int)(game->player.x)][(int)(game->player.y - (game->vec_dir.x * game->movespeed * 2))] == '0')
	//	game->player.y -= game->vec_dir.x * game->movespeed;
	game->player_pixel.x++;
	//draw_minimap(game);
}

void	move_left(t_game *game)
{
	//if (game->map[(int)(game->player.x - (game->vec_dir.y * game->movespeed * 2))][(int)game->player.y] == '0')
	//	game->player.x -= game->vec_dir.y * game->movespeed;
	//if (game->map[(int)(game->player.x)][(int)(game->player.y + (game->vec_dir.x * game->movespeed * 2))] == '0')
	//	game->player.y += game->vec_dir.x * game->movespeed;
	game->player_pixel.x--;
	//draw_minimap(game);
}

void	move_up(t_game *game)
{
	//if (game->map[(int)(game->player.x + (game->vec_dir.x * game->movespeed * 2))][(int)game->player.y] == '0')
	//	game->player.x += game->vec_dir.x * game->movespeed;
	//if (game->map[(int)(game->player.x)][(int)(game->player.y + (game->vec_dir.y * game->movespeed * 2))] == '0')
	//	game->player.y += game->vec_dir.y * game->movespeed;
	game->player_pixel.y--;
	//draw_minimap(game); //a modif en fonction game->map_here.
}

void	move_down(t_game *game)
{
	//if (game->map[(int)(game->player.x - (game->vec_dir.x * game->movespeed * 2))][(int)game->player.y] == '0')
	//	game->player.x -= game->vec_dir.x * game->movespeed;
	//if (game->map[(int)(game->player.x)][(int)(game->player.y - (game->vec_dir.y * game->movespeed * 2))] == '0')
	//	game->player.y -= game->vec_dir.y * game->movespeed;
	game->player_pixel.y++;
	//draw_minimap(game);
}

void	rotate_left(t_game *game)
{
	//double old_planx;
	//double old_dirx;
//
	//old_dirx = game->vec_dir.x;
	//old_planx = game->vec_plan.x;
	//game->vec_dir.x = game->vec_dir.x * cos(game->rotspeed / 2) - game->vec_dir.y * sin(game->rotspeed / 2);
	//game->vec_dir.y = old_dirx * sin(game->rotspeed / 2) + game->vec_dir.y * cos(game->rotspeed / 2);
	//game->vec_plan.x = game->vec_plan.x * cos(game->rotspeed / 2) - game->vec_plan.y * sin(game->rotspeed / 2);
	//game->vec_plan.y = old_planx * sin(game->rotspeed / 2) + game->vec_plan.y * cos(game->rotspeed / 2);
	game->pa += 0.1;
	if (game->pa > 2 * M_PI)
		game->pa -= 2 * M_PI;
	game->pdelta.x = cos(game->pa) * 5;
	game->pdelta.y = sin(game->pa) * 5;
	//printf("test left\n");
}

void	rotate_right(t_game *game)
{
	//double old_planx;
	//double old_dirx;
//
	//old_dirx = game->vec_dir.x;
	//old_planx = game->vec_plan.x;
	//game->vec_dir.x = game->vec_dir.x * cos(-game->rotspeed / 2) - game->vec_dir.y * sin(-game->rotspeed / 2);
	//game->vec_dir.y = old_dirx * sin(-game->rotspeed / 2) + game->vec_dir.y * cos(-game->rotspeed / 2);
	//game->vec_plan.x = game->vec_plan.x * cos(-game->rotspeed / 2) - game->vec_plan.y * sin(-game->rotspeed / 2);
	//game->vec_plan.y = old_planx * sin(-game->rotspeed / 2) + game->vec_plan.y * cos(-game->rotspeed / 2);
	game->pa -= 0.1;
	if (game->pa < 0)
		game->pa += 2 * M_PI;
	game->pdelta.x = cos(game->pa) * 5;
	game->pdelta.y = sin(game->pa) * 5;
	//printf("test right\n");
}

void	move_player(t_game *game)
{
	if (game->move_right == 1)
		move_right(game);
	if (game->move_left == 1)
		move_left(game);
	if (game->move_up == 1)
		move_up(game);
	if (game->move_down == 1)
		move_down(game);
	if (game->rotate_right == 1)
		rotate_right(game);
	if (game->rotate_left == 1)
		rotate_left(game);
}

int	moves_activated(int keycode, t_game *game)
{
	if (keycode == 100)
		game->move_right = 1;
	if (keycode == 97)
		game->move_left = 1;
	if (keycode == 119)
		game->move_up = 1;
	if (keycode == 115)
		game->move_down = 1;
	if (keycode == 65363)
		game->rotate_right = 1;
	if (keycode == 65361)
		game->rotate_left = 1;
	if (keycode == 65307)
		closew(game);
	return (0);
}

int	moves_disactivated(int keycode, t_game *game)
{
	if (keycode == 100)
		game->move_right = 0;
	if (keycode == 97)
		game->move_left = 0;
	if (keycode == 119)
		game->move_up = 0;
	if (keycode == 115)
		game->move_down = 0;
	if (keycode == 65363)
		game->rotate_right = 0;
	if (keycode == 65361)
		game->rotate_left = 0;
	return (0);
}
