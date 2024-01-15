
#include "../cub3d.h"

char	*ft_strjoin(char *stock, char *buff)
{
	char	*new;
	int		i;
	int		u;

	if (!stock)
	{
		stock = malloc(sizeof(char) * 1);
		stock[0] = 0;
	}
	u = 0;
	i = 0;
	new = malloc(((ft_strlen(stock) + ft_strlen(buff)) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (stock[i])
		new[u++] = stock[i++];
	i = 0;
	while (buff[i])
		new[u++] = buff[i++];
	new[u] = '\0';
	free(stock);
	return (new);
}

char	*readfd(char *stock, int fd)
{
	char	*buff;
	int		r;

	r = 1;
	buff = malloc (sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (r > 0 && (ft_strchr2(stock) == 0))
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r == -1)
		{
			free(buff);
			return (0);
		}
		buff[r] = '\0';
		stock = ft_strjoin(stock, buff);
	}
	free(buff);
	return (stock);
}

char	*linecreat(char *stock)
{
	int		i;
	int		u;
	char	*new;

	u = 0;
	if (!stock[u])
		return (NULL);
	while (stock[u] != '\n' && stock[u] != '\0')
		u++;
	new = malloc((u + 2) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (i < u)
	{
		new[i] = stock[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*delstock(t_game *data, char *stock)
{
	char	*rest;
	int		i;
	int		j;

	(void)data;
	i = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
	{
		free(stock);
		return (NULL);
	}
	rest = malloc(sizeof(char) * ((ft_strlen(stock) - i) + 1));
	if (!rest)
		return (NULL);
	i++;
	j = 0;
	while (stock[i])
		rest[j++] = stock[i++];
	rest[j] = '\0';
	free(stock);
	free(rest);
	return (NULL);
}

char	*get_next_line_special(t_game *game, int fd)
{
	static char	*stock;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 2047)
		return (NULL);
	stock = readfd(stock, fd);
	if (!stock)
		return (NULL);
	line = linecreat(stock);
	stock = delstock (game, stock);
	return (line);
}