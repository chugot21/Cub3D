/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 23:24:40 by chugot            #+#    #+#             */
/*   Updated: 2023/12/22 16:02:04 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game		game;

	if (argc != 2)
	{
		perror("Error : only file .cub in argument\n");
		return(1);
	}
	if (check_name(argv[1]) == 1)
		return(1);
	gc_init(&game.gc);
	init_parsing(&game);
	get_map(&game, argv[1]);
	if (check_error(&game) == 1) // free a faire 
	{
		//printf("here erreur map\n");
		//clean_all_error(&game, 0);
		return(1);
	}
	//for (int i = 0; i < 15; i++)
	//	printf("real [%zu]=%s=\n", i,game.tmap->map[i]);
	printf("start player x:%f y:%f\n", game.tmap->start_player.x , game.tmap->start_player.y);
	end_parss(&game);
	//OU
	parsing(&game); //version test


	game.win_x = 960;
	game.win_y = 540;
	init_game(&game);
	game.window.mlx = mlx_init();
	game.window.win = mlx_new_window (game.window.mlx,
			game.win_x,
			game.win_y, "Club 3D");
	ft_raycasting(&game);
	mlx_hook(game.window.win, 2, 1L << 0, move_player, &game);
	mlx_hook(game.window.win, 17, 1L << 9, closew, &game);
	mlx_loop(game.window.mlx);
}
