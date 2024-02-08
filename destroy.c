/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 19:15:18 by chugot            #+#    #+#             */
/*   Updated: 2024/02/02 13:52:39 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	closew(t_game *game)
{
	free(game->t_north);
	free(game->t_south);
	free(game->t_west);
	free(game->t_east);
	free_map(game->info_map.map);
	//free_map(game->info_map.file); //<<<<<
	free_map(game->info_map.copy);
	free(game->map);
	free(game->minimap);
	mlx_destroy_window(game->window.mlx, game->window.win);
	mlx_destroy_display(game->window.mlx);
	free(game->window.mlx);
	write(1, "Stay with us !\n", 15);
	exit(0);
}
