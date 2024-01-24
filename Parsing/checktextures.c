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

//checks that texture extensions are valid
int	texture_extension(t_game *game)
{
	int ppm;
	int	i;
	int j;

	ppm = 0;
	i = 0;
	while(i++ < 4)
	{
		if (i == 0)
			j = game->info_map.NO;
		else if (i == 1)
			j = game->info_map.SO;
		else if (i == 2)
			j = game->info_map.WE;
		else if (i == 3)
			j = game->info_map.EA;
		if(check_extension(game->info_map.file[j], ".xpm") == 0)
		{
			printf("incompatible format detected\n");
			printf(".xpm files aren't supported yet\n");
			return(-1);
		}
		else if (check_extension(game->info_map.file[j], ".ppm") == 0)
			ppm++;
	}
	if (ppm == 4)
		return(0);
	printf("incompatible format detected\n");
	return (-1);
}

// gets texture paths
char	*texture_path(char *line)
{
	int		i;
	int		j;

	i = 0;
	while (line[i] != '\n')
	{
		if (line[i] == '.')
			break;
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
	int	fdNO;
	int fdSO;
	int fdWE;
	int fdEA;
	int fail;

	fail = 0;
	fdNO = open(texture_path(game->info_map.file[game->info_map.NO]), O_RDONLY);
	fdSO = open(texture_path(game->info_map.file[game->info_map.SO]), O_RDONLY);
	fdWE = open(texture_path(game->info_map.file[game->info_map.WE]), O_RDONLY);
	fdEA = open(texture_path(game->info_map.file[game->info_map.EA]), O_RDONLY);
	if (fdNO < 0 || fdSO < 0 || fdWE < 0 || fdEA < 0)
		fail = 1;
	close(fdNO);
	close(fdSO);
	close(fdWE);
	close(fdEA);
	if (fail == 1)
		return(-1);
	return(0);
}

// checks that all textures are present
int	has_textures(t_game *game)
{
	int	i;
	int	NO;
	int	SO;
	int	WE;
	int	EA;

	i = 0;
	NO = 0;
	SO = 0;
	WE = 0;
	EA = 0;
	while(i < game->info_map.linecount)
	{
		if (!ft_strncmp(game->info_map.file[i], "NO ", 3))
		{
			game->info_map.NO = i;
			NO++;
		}
		else if (!ft_strncmp(game->info_map.file[i], "SO ", 3))
		{
			game->info_map.SO = i;
			SO++;
		}
		else if (!ft_strncmp(game->info_map.file[i], "WE ", 3))
		{
			game->info_map.WE = i;
			WE++;
		}
		else if (!ft_strncmp(game->info_map.file[i], "EA ", 3))
		{
			game->info_map.EA = i;
			EA++;
		}
		i++;
	}
	if (NO == 1 && SO == 1 && WE == 1 && EA == 1)
		return(0);
	return(-1);
}