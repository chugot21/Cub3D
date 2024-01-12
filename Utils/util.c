/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:24:58 by chugot            #+#    #+#             */
/*   Updated: 2024/01/12 16:25:02 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strchr2(char *string)
{
	char	c;
	int		i;

	i = 0;
	c = '\n';
	if (!string)
		return (0);
	while (string[i] != '\0')
	{
		if (string[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strstr(char *big, char *lit)
{
	size_t	i;
	size_t	u;
	size_t	l;

	i = 0;
	l = ft_strlen(lit);
	if (l == 0)
		return (big);
	if (!big)
		return (NULL);
	while (big[i])
	{
		u = 0;
		while (big[i] && big[i + u] == lit[u])
		{
			u++;
			if (u == l)
				return (&big[i]);
		}
		i++;
	}
	return (NULL);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_strnrchr(char *s, char *c)
{
	int		i;
	size_t		u;

	u = 0;
	i = 0;
	while (s[i] != '\0')
		i++;
	while (i >= 0 && s[i] != c[u])
	{
		i--;
		if (i < 0)
			return (0);
	}
	while (s[i] && c[i])
	{
		if (s[i] == c[u])
			u++;
		i++;
	}
	if (u == ft_strlen(c))
		return (1);
	return (0);
}
