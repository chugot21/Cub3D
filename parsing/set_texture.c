
#include "../cub3d.h"

void	set_texture_c(t_game *data, char *buff)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	data->tmap->c1 = gc_malloc(&data->gc, sizeof(int) * 3);
	while (i < 3)
	{
		data->tmap->c1[i] = 0;
		while (buff[j] && buff[j] != ',')
		{
			if (ft_isdigit(buff[j]) == 1)
			{
				data->tmap->c1[i] *= 10;
				data->tmap->c1[i] += (buff[j] - 48);
			}
			j++;
		}
		j++;
		i++;
	}
}

void	set_texture_f(t_game *data, char *buff)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	data->tmap->f1 = gc_malloc(&data->gc, sizeof(int) * 3);
	while (i < 3)
	{
		data->tmap->f1[i] = 0;
		while (buff[j] && buff[j] != ',')
		{
			if (ft_isdigit(buff[j]) == 1)
			{
				data->tmap->f1[i] *= 10;
				data->tmap->f1[i] += (buff[j] - 48);
			}
			j++;
		}
		j++;
		i++;
	}
}

void	set_map_data(t_game *data, char *buff, int info, int fd)
{
	(void)fd;
	if (info == 1)
		data->tmap->no1 = ft_strdup(data, ft_strstr(buff, "./"));
	else if (info == 2)
		data->tmap->so1 = ft_strdup(data, ft_strstr(buff, "./"));
	else if (info == 3)
		data->tmap->we1 = ft_strdup(data, ft_strstr(buff, "./"));
	else if (info == 4)
		data->tmap->ea1 = ft_strdup(data, ft_strstr(buff, "./"));
	else if (info == 5)
		set_texture_f(data, buff);
	else if (info == 6)
		set_texture_c(data, buff);
}