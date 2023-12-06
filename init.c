/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:37:33 by chugot            #+#    #+#             */
/*   Updated: 2023/12/06 18:25:58 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*void	init_sidedist(t_game *game)
{
	if (game->raydir.x < 0)
	{
		game->step.x = -1;
		game->sidedist.x = (game->player.x - game->map_here.x) * game->deltadist.x;
	}
	else
	{
		game->step.x = 1;
		game->sidedist.x = (game->map_here.x + 1.0 - game->player.x) * game->deltadist.x;
	}
	if (game->raydir.y < 0)
	{
		game->step.y = -1;
		game->sidedist.y = (game->player.y - game->map_here.y) * game->deltadist.y;
	}
	else
	{
		game->step.y = 1;
		game->sidedist.y = (game->map_here.y + 1.0 - game->player.y) * game->deltadist.y;
	}
}

void	init_deltadist(t_game *game)
{
	if (game->raydir.y == 0)
		game->deltadist.x =  0;
	else if (game->raydir.x == 0)
		game->deltadist.x = 1;
	else
		game->deltadist.x = sqrt(1 + (game->raydir.y * game->raydir.y) / (game->raydir.x * game->raydir.x));
	if (game->raydir.x == 0)
		game->deltadist.y = 0;
	else if (game->raydir.y == 0)
		game->deltadist.y = 1;
	else
		game->deltadist.y = sqrt(1 + (game->raydir.x * game->raydir.x) / (game->raydir.y * game->raydir.y));
}

void	init_raycasting(t_game *game)
{
	game->hit = 0;
	game->perpWallDist = 0;
	game->camerax = 2 * game->x * 2 / (double)game->win_x - 1;
	game->raydir.x = game->vec_dir.x + game->vec_plan.x * game->camerax;
	game->raydir.y = game->vec_dir.y + game->vec_plan.y * game->camerax;
	game->map_here.x = (int)game->player.x;
	game->map_here.y = (int)game->player.y;
	game->movespeed = 0.1;
	game->rotspeed = 0.033 * 1.8;
	init_deltadist(game);
	init_sidedist(game);
}*/

void	init_moves(t_game *game)
{
	game->move_left = 0;
	game->move_right = 0;
	game->move_up = 0;
	game->move_down = 0;
	game->rotate_left = 0;
	game->rotate_right = 0;
	//game->side = -1; //a voir si utile.
}

void	init_direction_WE(t_game *game)
{
	if (game->dir == 'W')
	{
		game->pa = PI;
		//game->pdelta.x = cos(game->pa) * 5;
		//game->pdelta.y = sin(game->pa) * 5;
		//game->vec_plan.x = -0.66;
		//game->vec_plan.y = 0;
	}
	if (game->dir == 'E')
	{
		game->pa = 0;
		//game->vec_dir.x = 0;
		//game->vec_dir.y = 1;
		//game->vec_plan.x = 0.66;
		//game->vec_plan.y = 0;
	}
	printf("pa : %f\n", game->pa);
	//if (game->pa < 0)
	//	game->pa += 2 * M_PI;
	//if (game->pa > 2 * M_PI)
	//	game->pa -= 2 * M_PI;
	game->pdelta.x = cos(game->pa) * 5;
	game->pdelta.y = sin(game->pa) * 5;
	printf("init pdelat x : %f, pdelta y : %f, pa : %f\n", game->pdelta.x, game->pdelta.y, game->pa);
	init_moves(game);
}

void	init_direction(t_game *game)
{
	if (game->dir == 'N')
	{
		game->pa = PI / 2;
		//game->vec_dir.x = -1;
		//game->vec_dir.y = 0;
		//game->vec_plan.x = 0;
		//game->vec_plan.y = 0.66;
	}
	if (game->dir == 'S')
	{
		game->pa = PI * 1.5;
		//game->vec_dir.x = 1;
		//game->vec_dir.y = 0;
		//game->vec_plan.x = 0;
		//game->vec_plan.y = -0.66;
	}
	init_direction_WE(game);
}
/*void	init_game(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'W' || game->map[i][j] == 'E')
			{
				game->player.x = j + 0.5;
				game->player.y = i + 0.5;
				game->player_pixel.x = (j + 1.5) * 10;
				game->player_pixel.y = (i + 1.5) * 10;
				init_direction(game, game->map[i][j]);
			}
			j++;
		}
		i++;
	}
	game->img = mlx_new_image(game->window.mlx, game->win_x, game->win_y);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->line_length,
								&game->endian);
}*/

void	init_game(t_game *game)
{
	int i;
	int x;
	int y;

	i = 0;
	while (i < game->maps)
	{
		if (game->map[i] == 7)
		{
			y = (i + 1) / game->mapx;
			x = (i + 1) - (game->mapx * y);
			printf("init mapx : %d, i : %d, x : %d, y : %d\n", game->mapx, i ,x, y);
			game->player.x = x + 0.5;
			game->player.y = y + 0.5;
			game->player_pixel.x = (x + 1.5) * 10;
			game->player_pixel.y = (y + 1.5) * 10;
			init_direction(game);
		}
		i++;
	}
	game->img = mlx_new_image(game->window.mlx, game->win_x, game->win_y);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->line_length,
								&game->endian);
}

