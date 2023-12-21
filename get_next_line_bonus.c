/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:32:41 by chugot            #+#    #+#             */
/*   Updated: 2023/05/02 13:32:42 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*next_line(char *tmp)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (tmp[i] != '\n' && tmp[i] != '\0')
		i++;
	if (!tmp[i])
	{
		free(tmp);
		return (NULL);
	}
	new = malloc(sizeof(char) * (ft_strlen(tmp) - i + 1));
	if (!new)
		return (NULL);
	i++;
	while (tmp[i] != '\0')
		new[j++] = tmp[i++];
	new[j] = '\0';
	free(tmp);
	return (new);
}

char	*get_line_n(char *tmp)
{
	int		i;
	char	*line;

	i = 0;
	if (!tmp[i])
		return (NULL);
	while (tmp[i] != '\n' && tmp[i] != '\0')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (tmp[i] != '\n' && tmp[i] != '\0')
	{
		line[i] = tmp[i];
		i++;
	}
	if (tmp[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line_tmp(int fd, char *tmp)
{
	char	*buffer;
	int		byte;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	byte = 1;
	while (byte > 0 && !ft_strchr(tmp, '\n'))
	{
		byte = read(fd, buffer, BUFFER_SIZE);
		if (byte == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[byte] = '\0';
		tmp = ft_strjoin(tmp, buffer);
	}
	free (buffer);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*tmp[257];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 257)
		return (NULL);
	tmp[fd] = get_next_line_tmp(fd, tmp[fd]);
	if (!tmp[fd])
		return (NULL);
	line = get_line_n(tmp[fd]);
	tmp[fd] = next_line(tmp[fd]);
	return (line);
}
