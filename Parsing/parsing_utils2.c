/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:29:14 by mgourlai          #+#    #+#             */
/*   Updated: 2024/01/30 19:00:12 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// calculates amount of lines in file
int	ft_get_tabcount(int fd)
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
		if (!ft_strncmp(buffer, "\t", 1))
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

// converts tab to spaces
void	tab_to_spaces(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->info_map.file[i] != NULL)
	{
		while (game->info_map.file[i][j] != '\n')
		{
			if (game->info_map.file[i][j] == '\t')
			{
				game->info_map.file[i][j] = ' ';
				game->info_map.file[i + 1][j] = ' ';
				game->info_map.file[i + 2][j] = ' ';
				game->info_map.file[i + 3][j] = ' ';
				i += 3;
			}
			i++;
		}
		j++;
	}
}

// security option to reject files that have tabs 
int	check_tab(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < game->info_map.map_end - game->info_map.map_start)
	{
		while (game->info_map.file[i][j] != '\0' &&
			game->info_map.file[i][j] != '\n')
		{
			if (game->info_map.file[i][j] == '\t')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

// adds a line on the right and left of the map
void	left_right_line(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (j < game->info_map.y + 2)
	{
		while (i <= game->info_map.longest + 1)
		{
			if (i == 0 || i == game->info_map.longest + 1)
				game->info_map.copy[j][i] = '2';
			else
				game->info_map.copy[j][i] = '0';
			i++;
		}
		i = 0;
		j++;
	}
}

// adds a line above the map and at the bottom
void	top_bot_line(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->info_map.longest + 2)
	{
		game->info_map.copy[0][i] = '2';
		i++;
	}
	//game->info_map.copy[0][i] = '\n';
	i = 0;
	while (i < game->info_map.longest + 2)
	{
		game->info_map.copy[game->info_map.y + 2][i] = '2';
		i++;
	}
	//game->info_map.copy[game->info_map.y + 2][i] = '\n';
}
