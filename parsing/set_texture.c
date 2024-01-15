
#include "../cub3d.h"

void	set_texture_c(t_game *game, char *buff) //ok
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	game->crgb = gc_malloc(&game->gc, sizeof(int) * 3);
	while (i < 3)
	{
		game->crgb[i] = 0;
		while (buff[j] && buff[j] != ',')
		{
			if (ft_isdigit(buff[j]) == 1)
			{
				game->crgb[i] *= 10;
				game->crgb[i] += (buff[j] - 48);
			}
			j++;
		}
		j++;
		i++;
	}
}

void	set_texture_f(t_game *game, char *buff) //ok
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	game->frgb = gc_malloc(&game->gc, sizeof(int) * 3); //data->tmap->f1
	while (i < 3)
	{
		game->frgb[i] = 0;
		while (buff[j] && buff[j] != ',')
		{
			if (ft_isdigit(buff[j]) == 1)
			{
				game->frgb[i] *= 10;
				game->frgb[i] += (buff[j] - 48);
			}
			j++;
		}
		j++;
		i++;
	}
}

void	set_map_data(t_game *game, char *buff, int info, int fd) //ok
{
	(void)fd;
	if (info == 1)
		game->tno = ft_strdup(game, ft_strstr(buff, "./"));
	else if (info == 2)
		game->tso = ft_strdup(game, ft_strstr(buff, "./"));
	else if (info == 3)
		game->twe = ft_strdup(game, ft_strstr(buff, "./"));
	else if (info == 4)
		game->tea = ft_strdup(game, ft_strstr(buff, "./"));
	else if (info == 5)
		set_texture_f(game, buff);
	else if (info == 6)
		set_texture_c(game, buff);
}