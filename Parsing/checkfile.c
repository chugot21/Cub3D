/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkfile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgourlai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:15:21 by mgourlai          #+#    #+#             */
/*   Updated: 2024/01/23 19:15:21 by mgourlai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// checks that file has floor and ceiling color values
int	has_floor_ceiling(t_game *game)
{
	int	i;
	int floor;
	int ceiling;

	i = 0;
	floor = 0;
	ceiling = 0;
	while(i < game->info_map.linecount)
	{
		if (!ft_strncmp(game->info_map.file[i], "F ", 2))
		{
			game->info_map.file[i] += 2;
			if(valid_rgb(game->info_map.file[i]) == -1)
				return(-1);
			floor++;
			game->info_map.floor = i;
		}
		if (!ft_strncmp(game->info_map.file[i], "C ", 2))
		{
			game->info_map.file[i] += 2;
			if(valid_rgb(game->info_map.file[i]) == -1)
				return(-1);
			ceiling++;
			game->info_map.ceiling = i;
		}
		i++;
	}
	if (floor == 1 && ceiling == 1)
		return (0);
	return(-1);
}

// finds the last line of the map in file
int	map_end(t_game *game)
{
	int	i;
	int	j;

	i = game->info_map.linecount - 1;
	j = 0;
	while(i >= 0)
	{
		while(game->info_map.file[i][j] == ' ' || game->info_map.file[i][j] == '\t')
			j++;
		game->info_map.file[i] += j;
		if (!ft_strncmp(game->info_map.file[i], "111", 3))
		{
			game->info_map.map_end = i;
			return(0);
		}
		i--;
	}
	return(-1);
}

//finds the first line of the map in file
int	map_start(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(game->info_map.file[i] != NULL)
	{
		while(game->info_map.file[i][j] == ' ' || game->info_map.file[i][j] == '\t')
			j++;
		game->info_map.file[i] += j;
		if (!ft_strncmp(game->info_map.file[i], "111", 3))
		{
			game->info_map.map_start = i;
			game->info_map.file[i] -=j;
			return(0);
		}
		i++;
	}
	return(-1);
}

// hub of functions that analyze the file, find the map, texture coordinates
// and rgb, while storing the data required for the latter part of the parsing
// as well as the execution/rendering
int	check_file(t_game *game, char **argv)
{
	int	fd;
	
	printf("-analyzing file info\n");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return(error("couldn't open .cub file\n"));
	close(fd);
	printf("--valid access to file\n");
	if(map_start(game) == -1 || map_end(game) == -1)
		return(error("couldn't find a map in .cub file\n"));
	game->info_map.y = game->info_map.map_end - game->info_map.map_start;
	printf("--file has a map\n");
	if (has_textures(game) == -1)
		return(error("your file is missing at least one texture\n"));
	printf("--file has all textures\n");
	if (can_access_textures(game) == -1)
		return(error("could not access at least one texture\n"));
	printf("---all textures can be accessed\n");
	if (texture_extension(game) == -1)
		return(error("please use .ppm textures exclusively\n"));
	if (has_floor_ceiling(game) == -1)
		return(error("your map appears not to specify floor and ceiling colors correctly\n"));
	printf("--file has valid rgb for floor and ceiling\n");
	if(get_hexa_color(game) == -1)
		return(error("could not gather all file data\n"));
	printf("--file has valid rgb for floor and ceiling\n");
	return(0);
}

//converts the file into a string tab using get_next_line
int	convert_file(t_game *game, char **argv)
{
	int	i;
	int fd;

	i = 0;
	if (check_extension(argv[1], ".cub") == -1)
		return(error("incorrect extension or format\n"));
	printf("--file extension is okay\n");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return(error("couldn't open file\n"));
	printf("HERE\n");
	game->info_map.file = malloc((sizeof(char *) * (game->info_map.linecount +1)));
	if (!game->info_map.file)
		return (-1);
	while ("Redbone - Childish Gambino")
	{
		game->info_map.file[i] = get_next_line(fd);
		if (game->info_map.file[i] == NULL)
			break;
		printf("%s", game->info_map.file[i]);
		i++;
	}
	if (check_tab(game) == -1)
		return (-1);
	game->info_map.file[i] = NULL;
	game->info_map.x = ft_strlen(game->info_map.file[0]) ;
	return (0);
}