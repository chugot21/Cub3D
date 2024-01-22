/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgourlai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:06:52 by mgourlai          #+#    #+#             */
/*   Updated: 2023/05/03 19:06:55 by mgourlai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "../include/cub3d.h"

// this function takes the temp string and keeps whats after \n AKA le 200
char	*keep_the_rest(char *temp)
{
	char	*rest;
	int		i;
	int		j;

	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (!temp[i])
	{
		free(temp);
		return (NULL);
	}
	rest = (char *)malloc(sizeof(char) * ((ft_strlen(temp) - i) + 1));
	if (!rest)
		return (NULL);
	i++;
	j = 0;
	while (temp[i])
		rest[j++] = temp[i++];
	rest[j] = '\0';
	free(temp);
	return (rest);
}

// writes only line from start to \n AKA le 800
char	*temp_to_line(char *temp)
{
	int		i;
	char		*line;
	i = 0;
	if (!temp[i])
		return (NULL);
	while (temp[i] && temp[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (temp[i] && temp[i] != '\n')
	{
		line[i] = temp[i];
		i++;
	}
	if (temp[i] == '\n')
	{
		line[i] = temp[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

// writes until \n with too many characters to trim later AKA le 1000
char	*read_to_temp(char *temp, int fd)
{
	char	*buffer;
	int		index;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	index = 1;
	while (!ft_strchr(temp, '\n') && index > 0)
	{
		index = read(fd, buffer, BUFFER_SIZE);
		if (index == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[index] = '\0';
		temp = ft_strjoin(temp, buffer);
	}
	free(buffer);
	return (temp);
}

// main function
char	*get_next_line(int fd)
{
	static char	*temp[260];
	char		*line;

	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0)
		return (0);
	temp[fd] = read_to_temp(temp[fd], fd);
	if (!temp[fd])
		return (NULL);
	line = temp_to_line(temp[fd]);
	temp[fd] = keep_the_rest(temp[fd]);
	return (line);
}
