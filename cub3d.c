/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 23:24:40 by chugot            #+#    #+#             */
/*   Updated: 2023/12/18 21:58:11 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double dist(double ax, double ay, double bx, double by, double ang)
{
	return(sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void 	limits_rays(t_game *game)
{
	if (game->ra < 0)
		game->ra += 2 * PI;
	if (game->ra > 2 * PI)
		game->ra -= 2 * PI;
}

void	fix_fish_eye(t_game *game)
{
	game->ca = game->pa - game->ra;
	if (game->ca < 0)
		game->ca += 2 * PI;
	if (game->ca > 2 * PI)
		game->ca -= 2 * PI;
	game->dist = game->dist * cos(game->ca);
}

void low_rays(t_game *game)
{
	if (game->dis_verti < game->dis_horiz)
	{
		game->ray.x = game->vertical.x;
		game->ray.y = game->vertical.y;
		game->dist = game->dis_verti;
		//game->color = 0x217a42;
	}
	if (game->dis_verti > game->dis_horiz)
	{
		game->ray.x = game->horizon.x;
		game->ray.y = game->horizon.y;
		game->dist = game->dis_horiz;
		//game->color = 0x0cab46;
	}
}

void	vertical_rays(t_game *game, double ntan)
{
	game->dof = 0;
	ntan = -tan(game->ra);
	game->dis_verti = 1000000;
	game->vertical.x = game->player_pixel.x;
	game->vertical.y = game->player_pixel.y;
	if (game->ra > P2 && game->ra < P3) //si on regarde à gauche
	{
		game->ray.x = (((int)game->player_pixel.x >> 6) << 6)-0.0001;
		game->ray.y = (game->player_pixel.x - game->ray.x) * ntan + game->player_pixel.y;
		game->xoyo.x = -64;
		game->xoyo.y = -game->xoyo.x * ntan;
	}
	if (game->ra < P2 || game->ra > P3) //si on regarde a droite
	{
		game->ray.x = (((int)game->player_pixel.x >> 6) << 6) + 64; //
		game->ray.y = (game->player_pixel.x - game->ray.x) * ntan + game->player_pixel.y;
		game->xoyo.x = 64;
		game->xoyo.y = -game->xoyo.x * ntan;
	}
	if (game->ra == 0 || game->ra == PI)
	{
		game->ray.x = game->player_pixel.x;
		game->ray.y = game->player_pixel.y;
		game->dof = game->win_y;
	}
	while(game->dof < game->win_y)
	{
		game->m.x = (int) (game->ray.x) >> 6;
		game->m.y = (int) (game->ray.y) >> 6;
		game->mp = game->m.y * game->mapx + game->m.x;
		if (game->mp > 0 && game->mp < game->maps && game->map[game->mp] == 1) //hit wall
		{
			game->vertical.x = game->ray.x;
			game->vertical.y = game->ray.y;
			game->dis_verti = dist(game->player_pixel.x, game->player_pixel.y, game->vertical.x, game->vertical.y, game->ra);
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

void	horizontal_rays(t_game *game, double atan)
{
	game->dof = 0;
	atan = -1/tan(game->ra);
	game->dis_horiz = 1000000;
	game->horizon.x = game->player_pixel.x;
	game->horizon.y = game->player_pixel.y;
	if (game->ra > PI) //si on regarde dans le dos
	{
		game->ray.y = (((int)game->player_pixel.y >> 6) << 6) - 0.0001;
		game->ray.x = (game->player_pixel.y - game->ray.y) * atan + game->player_pixel.x;
		game->xoyo.y = -64;
		game->xoyo.x = -game->xoyo.y * atan;
	}
	if (game->ra < PI) //si on regarde en face
	{
		game->ray.y = (((int)game->player_pixel.y >> 6) << 6) + 64;
		game->ray.x = (game->player_pixel.y - game->ray.y) * atan + game->player_pixel.x;
		game->xoyo.y = 64;
		game->xoyo.x = -game->xoyo.y * atan;
	}
	if (game->ra == 0 || game->ra == PI)
	{
		game->ray.x = game->player_pixel.x;
		game->ray.y = game->player_pixel.y;
		game->dof = game->win_x;
	}
	while(game->dof < game->win_x)
	{
		game->m.x = (int) (game->ray.x) >> 6;
		game->m.y = (int) (game->ray.y) >> 6;
		game->mp = game->m.y * game->mapx + game->m.x;
		if (game->mp > 0 && game->mp < game->maps && game->map[game->mp] == 1) //hit wall
		{
			game->horizon.x = game->ray.x;
			game->horizon.y = game->ray.y;
			game->dis_horiz = dist(game->player_pixel.x, game->player_pixel.y, game->horizon.x, game->horizon.y, game->ra);
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

void	draw_wall(t_game *game)
{
	double atan;
	double ntan;

	game->r = 0;
	game->ra = game->pa - DEGREE_RADIAN * 30; //30
	limits_rays(game);
	while (game->r < game->win_x) //60
	{
		horizontal_rays(game, atan);
		vertical_rays(game, ntan);
		low_rays(game);
		fix_fish_eye(game);
		draw_column(game);
		game->ra += DEGREE_RADIAN / 16;
		limits_rays(game);
		game->r++;
	}
}

void	print_texture(t_game *game)
{
	int y;
	int x;
	int pixel;
	int r;
	int g;
	int b;

	y = 0;
	
	while (y < 32)
	{
		x = 0;
		while (x < 32)
		{
			//printf("%d\n", y * 32 + x);
			pixel = (y * 32 + x) * 3;
			//printf("pixel %d\n", pixel);
			r = game->texture_one[pixel + 0];
			g = game->texture_one[pixel + 1];
			b = game->texture_one[pixel + 2];
			//printf("r %d, g %d, b %d\n", r, g, b);
			//my_mlx_pixel_put(game, )
			color_square(game, x * 10, y * 10, x * 10 + 10, y * 10 + 10, create_hexa_rgb(r, g, b));
			x++;
		}
		y++;
	}
}

int	ft_raycasting(t_game *game)
{
	game->img = mlx_new_image(game->window.mlx, game->win_x, game->win_y);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->line_length,
							&game->endian);
	draw_background(game);
	draw_wall(game);
	//draw_minimap(game);
	//print_texture(game);
	mlx_put_image_to_window(game->window.mlx, game->window.win, game->img, 0, 0);
	mlx_destroy_image(game->window.mlx, game->img);
	//printf("test flag %d\n", game->flag_move);
	game->flag_move = 0;
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
	init_game(&game);
	game.window.mlx = mlx_init();
	game.window.win = mlx_new_window (game.window.mlx,
			game.win_x,
			game.win_y, "Club 3D");
	//display_map(&game);
	//mlx_hook(game.window.win, 2, 1L << 0, moves_activated, &game);	
	ft_raycasting(&game);
	mlx_hook(game.window.win, 2, 1L << 0, move_player, &game);
	//mlx_loop_hook(game.window.mlx, ft_raycasting, &game);
	//mlx_hook(game.window.win, 3, 1L << 1, moves_disactivated, &game);
	mlx_hook(game.window.win, 17, 1L << 9, closew, &game);
	mlx_loop(game.window.mlx);
}
