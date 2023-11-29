/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 23:24:40 by chugot            #+#    #+#             */
/*   Updated: 2023/11/29 19:51:29 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*void	draw_ver_line(t_game *game)
{
	int y;

	y = game->drawstart;
	while (y <= game->drawend)
	{
		my_mlx_pixel_put(game, game->x, y, game->color);
		y++;
	}
}

void	draw_column_wall(t_game *game)
{
	game->line_height = (int) (game->win_y / game->perpWallDist);
	game->drawstart = -game->line_height / 2 + game->win_y / 2;
	if (game->drawstart < 0)
		game->drawstart = 0;
	game->drawend = game->line_height / 2 + game->win_y / 2;
	if (game->drawend >= game->win_y)
		game->drawend = game->win_y - 1;
	game->color = 0x00FF0000;
	if (game->side == 1)
		game->color = game->color / 2;
	draw_ver_line(game);
}

void	find_wall(t_game *game)
{
	while (game->hit == 0)
	{
		printf("sidedistx : %f, deltadistx : %f\n", game->sidedist.x, game->deltadist.x);
		printf("sidedisty : %f, deltadisty : %f\n", game->sidedist.y, game->deltadist.y);
		if (game->sidedist.x < game->sidedist.y)
		{
			game->sidedist.x += game->deltadist.x;
			game->map_here.x += game->step.x;
			game->side = 0;
			printf("test\n");
		}
		else
		{
			game->sidedist.y += game->deltadist.y;
			game->map_here.y += game->step.y;
			game->side = 1;
		}
		if (game->map[(int)game->map_here.x][(int)game->map_here.y] == '1')
		{
			game->hit = 1;
		}
	}
	if (game->side == 0)
		game->perpWallDist = (game->sidedist.x - game->deltadist.x);
	else
		game->perpWallDist = (game->sidedist.y - game->deltadist.y);
}*/

int	ft_raycasting(t_game *game)
{
	//game->x = 0;
	//while(game->x < game->win_x)
	//{
	//	printf("game->x = %d, game->win_x = %d\n", game->x, game->win_x);
	//	init_raycasting(game);
	//	find_wall(game);
	//	draw_column_wall(game);
	//	game->x++;
	//}
	draw_minimap(game);
	mlx_put_image_to_window(game->window.mlx, game->window.win, game->img, 0, 0);
	move_player(game);
	return(0);
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_window	window;
	
	game.win_x = 960;
	game.win_y = 540;
	parsing(&game);
	//treat_map(argv, &map);
	game.window.mlx = mlx_init();
	game.window.win = mlx_new_window (game.window.mlx,
			game.win_x,
			game.win_y, "Club 3D");
	init_game(&game);
	
	//display_map(&game);
	mlx_hook(game.window.win, 2, 1L << 0, moves_activated, &game);
	mlx_loop_hook(game.window.mlx, ft_raycasting, &game);
	mlx_hook(game.window.win, 3, 1L << 1, moves_disactivated, &game);
	mlx_hook(game.window.win, 17, 1L << 9, closew, &game);
	mlx_loop(game.window.mlx);
}
