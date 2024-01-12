/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 23:24:40 by chugot            #+#    #+#             */
/*   Updated: 2023/11/13 15:49:48 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_character(t_game *data, char pos, int x, int y)
{
	(void) data;
	(void) pos;
	(void) x;
	(void) y;
	/*
	if (pos == 'N' || pos == 'S' || pos == 'E' || pos == 'W')
	{
		if (pos == 'S')
			rotate_player(data, 3.141592);
		else if (pos == 'E')
			rotate_player(data, -1.57);
		else if (pos == 'W')
			rotate_player(data, 1.57);
		data->player.x = y;
		data->player.y = x;
	}*/
}

void	check_info(t_game *data, char *buff, int fd)
{
	if (ft_strncmp(buff, "NO", 2) == 0)
		set_map_data(data, buff, 1, fd);
	else if (ft_strncmp(buff, "SO", 2) == 0)
		set_map_data(data, buff, 2, fd);
	else if (ft_strncmp(buff, "WE", 2) == 0)
		set_map_data(data, buff, 3, fd);
	else if (ft_strncmp(buff, "EA", 2) == 0)
		set_map_data(data, buff, 4, fd);
	else if (ft_strncmp(buff, "F", 1) == 0)
		set_map_data(data, buff, 5, fd);
	else if (ft_strncmp(buff, "C", 1) == 0)
		set_map_data(data, buff, 6, fd);
	else if (ft_strstr(buff, "1") != 0)
		copy_first_line_map(data, buff, fd);
}

void	transfert_map(t_game *data, int fd)
{
	char	*buff;
	int		i;

	i = 0;
	while (i == 0 || buff != NULL)
	{
		buff = get_next_line(data, fd);
		if (!buff || buff == NULL)
		{
			free(buff);
			break ;
		}
		check_info(data, buff, fd);
		if (data->trace != 0)
		{
			free(buff);
			break ;
		}
		i++;
		free(buff);
	}
}

void	get_map(t_game *data, char *argv)
{
	int	fd;

	data->path_map = ft_strdup(data, argv);
	open_malloc_map(data);
	fd = 0;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		printf("Error : to run the program use a map.cub\n");
		exit(0);
	}
	transfert_map(data, fd);
	close(fd);
}
