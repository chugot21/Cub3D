/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <abrin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 02:34:40 by abrin             #+#    #+#             */
/*   Updated: 2023/08/27 02:36:23 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	malloc_map(t_game *data, int fd, char *buff)
{
	size_t	y;

	data->tmap->y_map = 0;
	y = 0;
	while (buff != NULL)
	{
		buff = get_next_line(data, fd);
		//printf("here buff : #%s# \n", buff);
		if (ft_strstr(buff, "1") != 0)
		{
			data->tmap->y_map++;
		}
		if (ft_strlen(buff) > data->tmap->x_map)
			data->tmap->x_map = ft_strlen(buff);
		free(buff);
	}
	//data->tmap->map = malloc(sizeof(char *) * data->tmap->y_map + 1);
	data->tmap->map = gc_malloc(&data->gc, sizeof(char *) * data->tmap->y_map + 4);
	while (y < data->tmap->y_map)
	{
		//data->tmap->map[y] = malloc (sizeof(char) * data->tmap->x_map + 1);
		data->tmap->map[y] = gc_malloc(&data->gc,
				sizeof(char) * data->tmap->x_map + 4);
		y++;
	}
}

void	open_malloc_map(t_game *data)
{
	char	*buff;
	int		i;
	int		fd;

	i = 0;
	fd = open(data->path_map, O_RDONLY);
	while (i == 0 || buff != NULL)
	{
		buff = get_next_line(data, fd);
		if (ft_strstr(buff, "1111") != 0)
		{
			data->tmap->y_map++;
			data->tmap->x_map = ft_strlen(buff);
			malloc_map(data, fd, buff);
			if (data->tmap->trace != 0)
			{
				free(buff);
				break ;
			}
		}
		free(buff);
		i++;
	}
	close(fd);
}