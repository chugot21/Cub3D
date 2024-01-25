/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgourlai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:24:38 by mgourlai          #+#    #+#             */
/*   Updated: 2024/01/23 19:24:39 by mgourlai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	flood(t_game *game, int x, int y)
{
	if (x < 1 || y < 1 || y > game->info_map.y
		|| x >= game->info_map.x || game->info_map.copy[y][x] == '1')
		return ;
	game->info_map.copy[y][x] = '1';
	flood(game, x - 1, y);
	flood(game, x + 1, y);
	flood(game, x, y -1);
	flood(game, x, y +1);
}

//checks that 0s arent next to any two, 
//which would lead to rendering issues in game
int	final_check(t_game *game, char **map)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (j < game->info_map.y + 3)
	{
		while (i < game->info_map.longest + 2)
		{
			if (map[j][i] == '0' && (map[j][i + 1] == '2' ||
				map[j][i - 1] == '2' || map[j + 1][i] == '2' ||
				map[j - 1][i] == '2' || map[j + 1][i + 1] == '2' ||
				map[j - 1][i + 1] == '2' || map[j + 1][i - 1] == '2' ||
				map[j - 1][i - 1] == '2'))
			{
				return (-1);
			}
			i++;
		}
		i = 1;
		j++;
	}
	return (0);
}

int	zeros_corner(t_game *game, char **map)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (map[j + 1] != NULL)
	{
		while (i < game->info_map.longest)
		{
			if (map[j][i] == '0' && map[j + 1][i + 1] == '2'
				&& map[j + 1][i - 1] == '2'
				&& map[j - 1][i + 1] == '2'
				&& map[j - 1][i - 1] == '2' )
				return (-1);
			i++;
		}
		i = 1;
		j++;
	}
	return (0);
}

// calculates amount of lines in file
int	ft_get_linecount(int fd)
{
	int		str_count;
	char	*buffer;
	int		linecount;

	linecount = 0;
	buffer = malloc(sizeof(char) * 1 + 1);
	if (!buffer)
		return (-1);
	str_count = 1;
	buffer[1] = '\0';
	while (str_count > 0)
	{
		str_count = read(fd, buffer, 1);
		if (!ft_strncmp(buffer, "\n", 1))
			linecount++;
		if (str_count == -1)
		{
			free(buffer);
			return (-1);
		}
	}
	free(buffer);
	return (linecount - 1);
}

// converts stray spaces into 2s
int	handle_spaces(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < game->info_map.y)
	{
		while (game->info_map.map[j][i] != '\n')
		{
			if (game->info_map.map[j][i] == 'N' ||
				game->info_map.map[j][i] == 'S' ||
				game->info_map.map[j][i] == 'E' ||
				game->info_map.map[j][i] == 'W')
				i++;
			if (game->info_map.map[j][i] == ' ')
				game->info_map.map[j][i] = '2';
			if (game->info_map.map[j][i] < '0' ||
				game->info_map.map[j][i] > '2' )
				return (-1);
			i++;
		}
		i = 0;
		j++;
	}
	return (0);
}
