/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgourlai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:22:03 by mgourlai          #+#    #+#             */
/*   Updated: 2024/01/23 19:22:04 by mgourlai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// writes Error and then details error
int	error(char *str)
{
	char	*err;

	err = "Error\n";
	while (*err)
		write(2, err++, 1);
	while (*str)
		write(2, str++, 1);
	return (-1);
}

int	has_floor_ceiling2(t_game *game, int i, int floor, int ceiling)
{
	int	j;

	while (i < game->info_map.linecount)
	{
		j = skip_space(game->info_map.file[i]);
		if (!ft_strncmp(&game->info_map.file[i][j], "F ", 2))
		{
			if (valid_rgb(&game->info_map.file[i][j]) == -1)
				return (-1);
			floor++;
			game->info_map.floor = i;
		}
		if (!ft_strncmp(&game->info_map.file[i][j], "C ", 2))
		{
			if (valid_rgb(&game->info_map.file[i][j]) == -1)
				return (-1);
			ceiling++;
			game->info_map.ceiling = i;
		}
		i++;
	}
	if (floor == 1 && ceiling == 1)
		return (0);
	return (-1);
}

// checks that rgb colors are valid
int	valid_rgb(char *str)
{
	int	i;
	int	chiffre;
	int	nb;

	i = 2;
	chiffre = 1;
	nb = 1;
	while (str[i + 1] != '\0' && str[i + 1] != ' ' && str[i + 1] != '\n')
	{
		if (str[i] == ',' && (str[i + 1] >= '0' && str[i + 1] <= '9'))
		{
			chiffre = 0;
			nb++;
		}
		else if (str[i] < '0' || str[i] > '9' || chiffre > 3)
			return (-1);
		chiffre++;
		i++;
	}
	if (chiffre > 3 || nb != 3)
		return (-1);
	return (0);
}

//checks that "file" has a given "ext" extension 
int	check_extension(char *file, char *ext)
{
	char	*str;

	str = file;
	str += ft_strlen(file) - 4 ;
	if (ft_strncmp(str, ext, 4) != 0)
	{
		str = file;
		return (-1);
	}
	str = file;
	return (0);
}

// prints a given map
void	print_map(char **map)
{
	int	y;

	y = 0;
	while (map[y] != NULL)
	{
		printf("%s\n", map[y]);
		y++;
	}
}
