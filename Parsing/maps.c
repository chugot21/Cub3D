/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:20:46 by mgourlai          #+#    #+#             */
/*   Updated: 2024/02/02 12:41:56 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	strs_to_ints(t_game *game)
{
	int	i;
	int	j;
	int	k;

	j = -1;
	k = 0;
	game->minimap = malloc(sizeof(int)
			* ((game->info_map.y + 3) * (game->info_map.longest + 2)));
	if (!game->minimap)
		return (-1);
	while (++j < game->info_map.y + 3)
	{
		i = 0;
		while (i < game->info_map.longest + 2)
		{
			if (ft_isalpha(game->info_map.copy[j][i]) == 1)
				game->minimap[k] = 7;
			else
				game->minimap[k] = game->info_map.copy[j][i] - '0';
			i++;
			k++;
		}
	}
	return (0);
}

// converts map from file into a char **map
int	map_maker(t_game *game)
{
	int	i;
	int	j;

	i = game->info_map.map_start;
	j = 0;
	game->info_map.map = malloc((sizeof(char *)
				* ((game->info_map.map_end - game->info_map.map_start) + 2)));
	if (!game->info_map.map)
		return (-1);
	while ("Redbone - Childish Gambino")
	{
		if (i == game->info_map.map_end + 1)
			break ;
		game->info_map.map[j] = ft_strdup(game->info_map.file[i]);
		j++;
		i++;
	}
	game->info_map.map[j] = NULL;
	game->info_map.y = j - 1;
	game->info_map.x = ft_strlen(game->info_map.map[0]);

	//<<<<<<<<<<<<<<<<<<<test<<<<<<<<<<<<<
	printf("info_map.map\n");
	int k = 0;
	while (game->info_map.map[k])
	{
		printf("%s", game->info_map.map[k]);
		k++;
	}

	return (0);
}

// hub that handles maps
int	maps(t_game *game)
{
	printf("--creating map\n");
	longest_line(game);
	if (map_maker(game) == -1)
		return (error("make map\n"));
	printf("--map created\n");
	if (handle_spaces(game) == -1)
		return (-1);
	printf("--handled spaces\n");
	if (copy_maker(game) == -1)
		return (error("could not make map copy\n"));
	printf("--created map copy\n");
	printf("--char map converted to int array\n");
	if (strs_to_ints(game) == -1)
		return (error("couldnt convert char map to int array\n"));
	if (check_map(game) == -1)
		return (error("map incorrect\n"));
	printf("--map is correct\n");
	return (0);
}
