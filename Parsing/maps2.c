/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 01:07:54 by mgourlai          #+#    #+#             */
/*   Updated: 2024/01/30 18:58:32 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	add_map_copy2(t_game *game, int i, int j)
{
	while (i < game->info_map.longest + 2)
	{
		game->info_map.copy[j][i] = '2';
		i++;
	}
}

// adds map to the copy
void	add_map_copy(t_game *game)
{
	int	i;
	int	j;
	int	k;
	int	l;

	j = 0;
	k = 0;
	while (++j < game->info_map.y + 2)
	{
		i = 1;
		l = 0;
		while (i < game->info_map.longest + 2)
		{
			if (game->info_map.map[k][l] == '\n')
				add_map_copy2(game, i, j);
			else
			{
				game->info_map.copy[j][i] = game->info_map.map[k][l];
				i++;
			}
			l++;
		}
		k++;
	}
}

// makes a copy of the map
int	copy_maker(t_game *game)
{
	int	i;

	i = 0;
	game->info_map.copy = malloc(sizeof(char *)
			* (game->info_map.y + 4));
	if (!game->info_map.copy)
		return (-1);
	while (i < game->info_map.y + 3)
	{
		game->info_map.copy[i] = malloc(sizeof(char)
				* game->info_map.longest + 3);
		i++;
	}
	game->info_map.copy[i] = NULL;
	top_bot_line(game);
	left_right_line(game);
	add_map_copy(game);

	//<<<<<<<<<<<<<<<<<<<<test<<<<<<<<
	printf("info_map.copy\n");
	int j = 0;
	while (game->info_map.copy[j])
	{
		printf("%s", game->info_map.copy[j]);
		printf("\n");
		j++;
	}
	return (0);
}
