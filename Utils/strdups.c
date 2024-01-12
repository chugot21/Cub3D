/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdups.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:24:58 by chugot            #+#    #+#             */
/*   Updated: 2024/01/12 16:25:02 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strdup(t_game *data, const char *s)
{
	size_t		i;
	char	*dst;
	size_t		len;

	len = 0;
	i = 0;
	while (s[len])
		len++;
	//dst = malloc(sizeof(char) * len + 1);
	//(void) data;
	dst = gc_malloc(&data->gc, sizeof(char) * len + 1);
	if (dst == 0)
		return (NULL);
	while (s[i] != '\0')
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strdup_special(t_game *data, const char *s)
{
	int		i;
	size_t		j;
	char	*dst;
	int		len;

	(void) data;
	len = 0;
	i = 0;
	j = 1;
	dst = malloc(sizeof(char) * data->tmap->x_map + 3);
	if (!dst)
		return (NULL);
	dst[0] = '4';
	while (s[i] != '\0')
	{
		if (s[i] == ' ')
		{
			dst[j++] = '4';
			i++;
		}
		else
			dst[j++] = s[i++];
	}
	while(j < data->tmap->x_map + 2)
	{
		dst[j++] = '4';
	}
	dst[j + 1] = '\0';
	return (dst);
}
