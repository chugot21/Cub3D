/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checktextures2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgourlai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 01:04:03 by mgourlai          #+#    #+#             */
/*   Updated: 2024/01/25 01:04:04 by mgourlai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	texture_extension2(t_game *game, int i, int j)
{
	if (i == 0)
		j = game->info_map.no;
	else if (i == 1)
		j = game->info_map.so;
	else if (i == 2)
		j = game->info_map.we;
	else if (i == 3)
		j = game->info_map.ea;
	return (j);
}

//checks that texture extensions are valid
int	texture_extension(t_game *game)
{
	int	ppm;
	int	i;
	int	j;

	ppm = 0;
	i = 0;
	while (i++ < 4)
	{
		j = texture_extension2(game, i, j);
		if (check_extension(game->info_map.file[j], ".ppm") == 0)
			ppm++;
		else if (check_extension(game->info_map.file[j], ".xpm") == 0)
		{
			printf("incompatible format detected\n");
			printf(".xpm files aren't supported yet\n");
			return (-1);
		}
	}
	if (ppm == 4)
		return (0);
	printf("incompatible format detected\n");
	return (-1);
}
