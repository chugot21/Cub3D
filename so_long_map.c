/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:08:43 by chugot            #+#    #+#             */
/*   Updated: 2023/11/13 15:13:33 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**malloc_tab_map(t_map *map, int fd1)
{
	char	*line;

	map->countline = 0;
	line = get_next_line(fd1);
	while (line)
	{
		free(line);
		line = get_next_line(fd1);
		map->countline++;
	}
	free(line);
	map->map = malloc(sizeof(char *) * (map->countline + 1));
	if (!map->map)
		exit (0);
	return (map->map);
}

void	malloc_line_map(t_map *map, int fd2)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd2);
	while (line)
	{
		map->map[i] = line;
		free(line);
		line = get_next_line(fd2);
		i++;
	}
	free(line);
}

char	**write_map(t_map *map, int fd)
{ 
	int	i;

	i = 0;
	map->map[map->countline] = NULL;
	map->map[i] = get_next_line(fd);
	while (map->map[i] != NULL)
	{
		i++;
		map->map[i] = get_next_line(fd);
	}
	return (map->map);
}

char	**ft_map(t_map *map, int fd, int fd1, int fd2)
{
	map->map = malloc_tab_map(map, fd1);
	malloc_line_map(map, fd2);
	map->map = write_map(map, fd);
	return (map->map);
}
