/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgourlai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:21:09 by mgourlai          #+#    #+#             */
/*   Updated: 2024/01/23 19:21:15 by mgourlai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// finds longest line in map
void	longest_line(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = game->info_map.map_start;
	game->info_map.longest = 0;
	while (j <= game->info_map.map_end)
	{
		while (game->info_map.file[j][i] && game->info_map.file[j][i] != '\n')
			i++;
		if (i > game->info_map.longest)
			game->info_map.longest = i;
		i = 0;
		j++;
	}
}

// finds player location and stocks orientation
int	find_player(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (game->info_map.map[y] != NULL)
	{
		while (game->info_map.map[y][x] != '\n')
		{
			if (game->info_map.map[y][x] == 'N'
				|| game->info_map.map[y][x] == 'S'
				|| game->info_map.map[y][x] == 'E'
				|| game->info_map.map[y][x] == 'W')
			{
				game->player.x = x;
				game->player.y = y;
				game->dir = game->info_map.map[y][x];
				return (0);
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (-1);
}

// checks the map has at least one player and no more than one
int	only_one_player(t_game *game)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	j = 0;
	player = 0;
	while (j < game->info_map.y)
	{
		while (game->info_map.map[j][i] != '\n')
		{
			if (game->info_map.map[j][i] == 'N' ||
				game->info_map.map[j][i] == 'S' ||
				game->info_map.map[j][i] == 'W' ||
				game->info_map.map[j][i] == 'E')
				player++;
			i++;
		}
		i = 0;
		j++;
	}
	if (player != 1)
		return (-1);
	return (0);
}

// checks that map has only the possible numbers and character
int	only_numbers(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < game->info_map.y)
	{
		while (game->info_map.map[j][i] != '\n')
		{
			if (game->info_map.map[j][i] != '1' &&
				game->info_map.map[j][i] != '0' &&
				game->info_map.map[j][i] != '2' &&
				game->info_map.map[j][i] != 'N' &&
				game->info_map.map[j][i] != 'S' &&
				game->info_map.map[j][i] != 'W' &&
				game->info_map.map[j][i] != 'E' )
				return (-1);
			i++;
		}
		i = 0;
		j++;
	}
	return (0);
}

// hub that checks that the map is valid
int	check_map(t_game *game)
{
	if (only_numbers(game) == -1 || only_one_player(game) == -1)
		return (-1);
	find_player(game);
	if (zeros_corner(game, game->info_map.copy) == -1)
		return (-1);
	if (final_check(game, game->info_map.copy) == -1)
		return (-1);
	flood(game, game->player.x, game->player.y);
	return (0);
}
