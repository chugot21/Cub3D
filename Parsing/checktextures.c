/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checktextures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgourlai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:16:17 by mgourlai          #+#    #+#             */
/*   Updated: 2024/01/23 19:16:18 by mgourlai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// gets texture paths
char	*texture_path(char *line)
{
	int		i;
	int		j;

	i = 0;
	while (line[i] != '\n')
	{
		if (line[i] == '.')
			break ;
		i++;
	}
	j = i;
	while (line[j] != '\0')
	{
		if (line[j] == '\n' || line[j] == ' ')
			line[j] = '\0';
		j++;
	}
	line += i;
	return (line);
}

// checks that textures can be accessed
int	can_access_textures(t_game *game)
{
	int	fdno;
	int	fdso;
	int	fdwe;
	int	fdea;
	int	fail;

	fail = 0;
	fdno = open(texture_path(game->info_map.file[game->info_map.no]), O_RDONLY);
	fdso = open(texture_path(game->info_map.file[game->info_map.so]), O_RDONLY);
	fdwe = open(texture_path(game->info_map.file[game->info_map.we]), O_RDONLY);
	fdea = open(texture_path(game->info_map.file[game->info_map.ea]), O_RDONLY);
	if (fdno < 0 || fdso < 0 || fdwe < 0 || fdea < 0)
		fail = 1;
	close(fdno);
	close(fdso);
	close(fdwe);
	close(fdea);
	if (fail == 1)
		return (-1);
	return (0);
}

void	find_textures(t_game *game, int i, int j)
{
	if (!ft_strncmp(&game->info_map.file[i][j], "NO ", 3))
		game->info_map.no = i;
	else if (!ft_strncmp(&game->info_map.file[i][j], "SO ", 3))
		game->info_map.so = i;
	else if (!ft_strncmp(&game->info_map.file[i][j], "WE ", 3))
		game->info_map.we = i;
	else if (!ft_strncmp(&game->info_map.file[i][j], "EA ", 3))
		game->info_map.ea = i;
}

// checks that all textures are present
int	has_textures(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->info_map.linecount)
	{
		j = skip_space(game->info_map.file[i]);
		find_textures(game, i, j);
		i++;
	}
	if (game->info_map.no != -1 && game->info_map.so != -1
		&& game->info_map.we != -1 && game->info_map.ea != -1)
		return (0);
	return (-1);
}
