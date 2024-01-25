/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgourlai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 00:56:30 by mgourlai          #+#    #+#             */
/*   Updated: 2024/01/25 00:56:31 by mgourlai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_blue3(char *blue, int i, int res)
{
	blue[i] = '\0';
	res = ft_atoi(blue);
	free(blue);
	return (res);
}

int	get_blue2(t_game *game, int floor, int i)
{
	while (game->info_map.file[floor][i] >= '0' &&
	game->info_map.file[floor][i] <= '9')
		i++;
	return (i);
}

//isolates blue color code in rgb
int	get_blue(t_game *game, int floor)
{
	char	*blue;
	int		res;
	int		i;
	int		j;
	int		num;

	i = 0;
	j = 0;
	num = 0;
	res = 0;
	while (game->info_map.file[floor] && num < 2)
	{
		if (game->info_map.file[floor][i] == ',')
			num++;
		i++;
	}
	j = i;
	i = get_blue2(game, floor, i);
	blue = malloc(sizeof(char) * ((i - j) + 1));
	i = 0;
	while (game->info_map.file[floor][j] >= '0' &&
		game->info_map.file[floor][j] <= '9')
		blue[i++] = game->info_map.file[floor][j++];
	res = get_blue3(blue, i, res);
	return (res);
}
