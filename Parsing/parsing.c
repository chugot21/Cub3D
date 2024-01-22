/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgourlai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:32:20 by mgourlai          #+#    #+#             */
/*   Updated: 2024/01/12 17:32:22 by mgourlai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// writes Error and then details error
int	error(char *str)
{
	char	*err;

	err = "Error\n";
	while(*err)
		write(2, err++, 1);
	while(*str)
		write(2, str++, 1);
	return (-1);
}

// finds player location and stocks orientation
int	find_player(t_game *game)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (game->info_map.map[y] != NULL)
	{
		while (game->info_map.map[y][x] != '\n')
		{
			if (game->info_map.map[y][x] == 'N' || game->info_map.map[y][x] == 'S' ||
				game->info_map.map[y][x] == 'E' || game->info_map.map[y][x] == 'W')
			{
				game->player.x = x;
				game->player.y = y;
				game->dir = game->info_map.map[y][x];
				return(0);
			}
			x++;
		}
		x = 0;
		y++;
	}
	return(-1);
}

// calculates amount of lines in file
int	ft_get_linecount(int fd)
{
	int		str_count;
	char	*buffer;
	int		linecount;

	linecount = 0;
	buffer = malloc(sizeof(char) * 1 + 1);
	if (!buffer)
		return (-1);
	str_count = 1;
	buffer[1] = '\0';
	while (str_count > 0)
	{
		str_count = read(fd, buffer, 1);
		if (!ft_strncmp(buffer, "\n", 1))
			linecount++;
		if (str_count == -1)
		{
			free(buffer);
			return (-1);
		}
	}
	free(buffer);
	return(linecount - 1);
}

// checks the map has at least one player and no more than one
int	only_one_player(t_game *game)
{
	int	i;
	int	j;
	int player;

	i = 0;
	j = 0;
	player = 0;
	while(j < game->info_map.y)
	{
		while (game->info_map.map[j][i] != '\n')
		{
			if(game->info_map.map[j][i] == 'N' || game->info_map.map[j][i] == 'S' ||
				game->info_map.map[j][i] == 'W' ||
				game->info_map.map[j][i] == 'E')
				player++;
			i++;
		}
		i = 0;
		j++;
	}
	if (player != 1)
		return(-1);
	return(0);
}

// checks that map has only the possible numbers and character
int	only_numbers(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(j < game->info_map.y)
	{
		while (game->info_map.map[j][i] != '\n')
		{
			if(game->info_map.map[j][i] != '1' &&
				game->info_map.map[j][i] != '0' &&
				game->info_map.map[j][i] != '2' &&
				game->info_map.map[j][i] != 'N' &&
				game->info_map.map[j][i] != 'S' &&
				game->info_map.map[j][i] != 'W' &&
				game->info_map.map[j][i] != 'E' )
				return (-1);
			i++;
		}
		i = 0;
		j++;
	}
	return (0);
}

// finds longest line in map
void	longest_line(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	game->info_map.longest = 0;
	while(j <= game->info_map.y)
	{
		while (game->info_map.map[j][i] != '\n')
			i++;
		if(i > game->info_map.longest)
			game->info_map.longest = i;
		i = 0;
		j++;
	}
}


// converts stray spaces into 2s
int	handle_spaces(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(j <= game->info_map.y )
	{
		while (game->info_map.map[j][i] != '\n')
		{
			if(game->info_map.map[j][i] == 'N' ||
				game->info_map.map[j][i] == 'S' ||
				game->info_map.map[j][i] == 'E' ||
				game->info_map.map[j][i] == 'W')
				i++;
			if(game->info_map.map[j][i] == ' ')
				game->info_map.map[j][i] = '2';
			if (game->info_map.map[j][i] < '0' || 
				game->info_map.map[j][i] > '2' )
				return (-1);
			i++;
		}
		printf("%s", game->info_map.map[j]);
		i = 0;
		j++;
	}
	return (0);
}

// prints a given map
void    print_map(char **map) 
{
    int y;

    y = 0;
    while (map[y] != NULL)
    {
        printf("%s\n", map[y]);
		y++;
    }
}

void	flood(t_game *game, int x, int y)
{
	if (x < 1 || y < 1 || y > game->info_map.y || x >= game->info_map.x || game->info_map.copy[y][x] == '1')
		return;
	game->info_map.copy[y][x] = '1';
	flood(game, x - 1, y);
	flood(game, x + 1, y);
	flood(game, x, y -1);
	flood(game, x, y +1);
}

int zeros_corner(t_game *game, char **map)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (map[j + 1] != NULL)
	{
		while (i < game->info_map.longest )
		{	

			if (map[j][i] == '0' && map[j + 1][i + 1] == '2' 
				&& map[j + 1][i - 1] == '2' 
				&& map[j - 1][i + 1] == '2' 
				&& map[j - 1][i - 1] == '2' )
				return(-1);
			i++;
		}
		i = 1;
		j++;
	}
	return(0);
}

//checks that 0s arent next to any two, 
//which would lead to rendering issues in game
int	final_check(t_game *game, char **map)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (j < game->info_map.y + 3)
	{
		while(i <= game->info_map.longest + 2)
		{
			if (map[j][i] == '0' && (map[j][i + 1] == '2' ||
				map[j][i - 1] == '2' || map[j + 1][i] == '2' ||
				map[j - 1][i] == '2' || map[j + 1][i + 1] == '2' ||
				map[j - 1][i + 1] == '2' || map[j + 1][i - 1] == '2' ||
				map[j - 1][i - 1] == '2'))
			{
				return(-1);
			}
			i++;
		}
		i = 1;
		j++;
	}
	return (0);
}


// hub that checks that the map is valid
int	check_map(t_game *game)
{
	if (only_numbers(game) == -1 || only_one_player(game) == -1)
		return(-1);
	find_player(game);
	if(zeros_corner(game, game->info_map.copy) == -1)
		return(-1);
	if (final_check(game, game->info_map.copy) == -1)
		return (-1);
	flood(game, game->player.x, game->player.y);
	print_map(game->info_map.copy);
	return (0);
}

// adds a line on the right and left of the map
void	left_right_line(t_game *game)
{
	int	i;
	int j;

	i = 0;
	j = 1;
	while(j < game->info_map.y + 2)
	{
		while(i <= game->info_map.longest + 1)
		{
			if(i == 0 || i == game->info_map.longest + 1)
				game->info_map.copy[j][i] = '2';
			else
				game->info_map.copy[j][i] = '0';
			i++;
		}
		i = 0;
		j++;
	}
}

// adds a line above the map and at the bottom
void	top_bot_line(t_game *game)
{
	int	i;

	i = 0;
	while(i < game->info_map.longest + 2)
	{
		game->info_map.copy[0][i] = '2';
		i++;
	}
	game->info_map.copy[0][game->info_map.longest + 3] = '\0';
	i = 0;
	while(i < game->info_map.longest + 2)
	{
		game->info_map.copy[game->info_map.y + 2][i] = '2';
		i++;
	}
	game->info_map.copy[game->info_map.y + 2][game->info_map.longest + 3] = '\0';
}

int	strs_to_ints(t_game *game)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	game->map = malloc(sizeof(int) * ((game->info_map.y + 3) * (game->info_map.longest + 2)));
	if(!game->map)
		return (-1);
	while (j < game->info_map.y + 3)
	{
		while(i < game->info_map.longest + 2)
		{
			if (ft_isalpha(game->info_map.copy[j][i]) ==  1)
				game->map[k] = 7;
			else
				game->map[k] = game->info_map.copy[j][i] - '0';
			printf("%d", game->map[k]);
			i++;
			k++;
		}
		printf("\n");
		i = 0;
		j++;
	}
	return(0);
}

// adds map to the copy
void	add_map_copy(t_game *game)
{
	int	i;
	int	j;
	int k;
	int	l;

	i = 1;
	j = 1;
	k = 0;
	l = 0;
    while (j < game->info_map.y + 2)
	{
		while (i < game->info_map.longest + 2)
		{
			if (game->info_map.map[k][l] == '\n')
			{
				while (i < game->info_map.longest + 2)
				{
					game->info_map.copy[j][i] = '2';
					i++;
				}
			}
			else 
			{
				game->info_map.copy[j][i] = game->info_map.map[k][l];
				i++;
			}
			l++;
		}
		k++;
		j++;
		i = 1;
		l = 0;
	}
}

// makes a copy of the map
int copy_maker(t_game *game)
{
    int i;

    i = 0;
    game->info_map.copy = malloc(sizeof(char *) * (game->info_map.y + 4));
	if (!game->info_map.copy)
		return (-1);
	while(i < game->info_map.y + 4)
	{
		game->info_map.copy[i] = malloc(sizeof(char) * game->info_map.longest + 2);
		i++;
	}
	game->info_map.copy[i- 1] = NULL;
	top_bot_line(game);
	left_right_line(game);
	add_map_copy(game);
    return(0);
}

// converts map from file into a char **map
int	map_maker(t_game *game)
{
	int	i;
	int	j;

	i = game->info_map.map_start;
	j = 0;
	game->info_map.map = malloc((sizeof(char *) * ((game->info_map.map_end - game->info_map.map_start) + 2)));
	if (!game->info_map.map)
		return (-1);
	while ("Redbone - Childish Gambino")
	{
		game->info_map.map[j] = game->info_map.file[i];
		if (game->info_map.file[i] == NULL)
			break;
		j++;
		i++;
	}
	game->info_map.map[j] = NULL;
	game->info_map.y = j - 1;
	game->info_map.x = ft_strlen(game->info_map.map[0]);
	return (0);
}

// hub that handles maps
int	maps(t_game *game)
{
	printf("--creating map\n");
	if (map_maker(game) == -1)
		return (error("make map\n"));
	printf("--map created\n");
	longest_line(game);
	if (handle_spaces(game)== -1)
		return(-1);
	printf("--handled spaces\n");
    if (copy_maker(game) == -1)
		return (error("could not make map copy\n"));
	print_map(game->info_map.copy);
	printf("--created map copy\n");
	if (strs_to_ints(game) == -1)
		return (error("couldnt convert char map to int array\n"));
	printf("--char map converted to int array\n");
	if (check_map(game) == -1)
		return (error("map incorrect\n"));
	printf("--map is correct\n");
	print_map(game->info_map.copy);
	return(0);
}

//checks that "file" has a given "ext" extension 
int check_extension(char *file, char *ext)
{
	char *str;

	str = file;
	str += ft_strlen(file) - 4 ;
	if (ft_strncmp(str, ext, 4) != 0)
	{
		str = file;
		return (-1);
	}
	str = file;
    return(0);
}

void	initstruct(t_game *game, char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	game->info_map.linecount = ft_get_linecount(fd);
	close(fd);
	game->info_map.map_start = 0;
	game->info_map.map_end = 0;
	game->info_map.longest = 0;
	game->info_map.NO = 0;
	game->info_map.SO = 0;
	game->info_map.WE = 0;
	game->info_map.EA = 0;
	game->info_map.floor = 0;
	game->info_map.hexf = 0;
	game->info_map.ceiling = 0;
	game->info_map.hexc = 0;
	game->info_map.x = 0;
	game->info_map.y = 0;
}

// checks that rgb colors are valid
int	valid_rgb(char *str)
{
	int	i;
	int chiffre;
	int nb;

	i = 0; 
	chiffre = 1;
	nb = 1;
	while(str[i] != '\0' && str[i] != ' ' && str[i] != '\n')
	{
		if(str[i] == ',' && (str[i + 1] >= '0' && str[i + 1] <= '9'))
		{
			chiffre = 0;
			nb++;
		}
		else if(str[i] < '0' || str[i] > '9' || chiffre > 3)
			return (-1);
		chiffre++;
		i++;
	}
	if (chiffre > 3 || nb != 3)
		return (-1);
	return (0);
}

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
		if (line[j] == '\n')
			line[j] = '\0';
		j++;
	}
	line += i;
	printf("line is %s\n", line);
	return (line);
}

// checks that textures can be accessed
int	can_access_textures(t_game *game)
{
	int	fdNO;
	int fdSO;
	int fdWE;
	int fdEA;
	//int fail;

	//fail = 0;
	printf("NO %d, SO %d, WE %d, EA %d\n", game->info_map.NO, game->info_map.SO, game->info_map.WE, game->info_map.EA);
	fdNO = open(texture_path(game->info_map.file[game->info_map.NO]), O_RDONLY);
	fdSO = open(texture_path(game->info_map.file[game->info_map.SO]), O_RDONLY);
	fdWE = open(texture_path(game->info_map.file[game->info_map.WE]), O_RDONLY);
	fdEA = open(texture_path(game->info_map.file[game->info_map.EA]), O_RDONLY);
	printf("N %d, s %d, w %d, e %d\n", fdNO, fdSO, fdWE, fdEA);
	//if (fdNO < 0 || fdSO < 0 || fdWE < 0 || fdEA < 0)
	//	fail = 1;
	close(fdNO);
	close(fdSO);
	close(fdWE);
	close(fdEA);
	//if (fail == 1)
		//return(-1);
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

// finds the last line of the map in file
int	map_end(t_game *game)
{
	int	i;
	int	j;

	i = game->info_map.linecount - 1;
	j = 0;
	while(i >= 0)
	{
		while(game->info_map.file[i][j] == ' ')
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
		while(game->info_map.file[i][j] == ' ')
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

//turns rgb into hexa colors
unsigned long rgb_to_hexa(int red, int green, int blue)
{   
    return ((red & 0xff) << 16) + ((green & 0xff) << 8) + (blue & 0xff);
}

//isolates blue color code in rgb
int	get_blue(t_game *game, int floor)
{
	char *blue;
	int	res;
	int i;
	int j;
	int num;

	i = 0;
	j = 0;
	num = 0;
	while(game->info_map.file[floor] && num < 2)
	{
		if (game->info_map.file[floor][i] == ',')
			num++;
		i++;
	}
	j = i;
	while(game->info_map.file[floor][i] >= '0' && 
		game->info_map.file[floor][i] <= '9')
		i++;
	blue = malloc(sizeof(char) * ((i - j) + 1));
	i = 0;
	while(game->info_map.file[floor][j] >= '0' && 
		game->info_map.file[floor][j] <= '9')
	{
		blue[i] = game->info_map.file[floor][j];
		i++;
		j++;
	}
	blue[i] = '\0';
	res = ft_atoi(blue);
	free(blue);
	return (res);
}

//isolates green color code in rgb
int	get_green(t_game *game, int floor)
{
	char *green;
	int	res;
	int i;
	int j;

	i = 0;
	j = 0;
	while(game->info_map.file[floor][i] != '\n' && game->info_map.file[floor][i] != ',')
		i++;
	i += 1;
	j = i;
	while(game->info_map.file[floor][i] != '\n' && game->info_map.file[floor][i] >= '0' && 
		game->info_map.file[floor][i] <= '9')
		i++;
	green = malloc(sizeof(char) * ((i - j) + 1));
	i = 0;
	while(game->info_map.file[floor][i] != '\n' && game->info_map.file[floor][j] >= '0' && 
		game->info_map.file[floor][j] <= '9')
	{
		green[i] = game->info_map.file[floor][j];
		i++;
		j++;
	}
	green[i] = '\0';
	res = ft_atoi(green);
	free(green);
	return (res);
}

//isolates red color code in rgb
int	get_red(t_game *game, int floor)
{
	char *red;
	int	res;
	int i;
	int j;

	i = 0;
	j = 0;
	while(game->info_map.file[floor] && game->info_map.file[floor][i] < '0'
		&& game->info_map.file[floor][i] > '9')
		i++;
	j = i;
	while(game->info_map.file[floor][i] >= '0' && 
		game->info_map.file[floor][i] <= '9')
		i++;
	red = malloc(sizeof(char) * ((i - j) + 1));
	i = 0;
	while(game->info_map.file[floor][j] >= '0' && 
		game->info_map.file[floor][j] <= '9')
	{
		red[i] = game->info_map.file[floor][j];
		i++;
		j++;
	}
	red[i] = '\0';
	res = ft_atoi(red);
	free(red);
	return (res);
}

//  gathers rgb colors and converts them into hexa
int	get_hexa_color(t_game *game)
{
	int	red;
	int green;
	int blue;

	red = get_red(game, game->info_map.floor);
	green = get_green(game, game->info_map.floor);
	blue = get_blue(game, game->info_map.floor);
	if(red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
		return(-1);
	game->info_map.hexf = rgb_to_hexa(red, green, blue);
	red = get_red(game, game->info_map.ceiling);
	green = get_green(game, game->info_map.ceiling);
	blue = get_blue(game, game->info_map.ceiling);
	if(red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
		return(-1);
	game->info_map.hexc = rgb_to_hexa(red, green, blue);
	return(0);
}

int	get_file_data(t_game *game)
{
	if(get_hexa_color(game) == -1)
		return(-1);
	return(0);
}

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
	if (get_file_data(game) == -1)
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
	game->info_map.file[i] = NULL;
	game->info_map.x = ft_strlen(game->info_map.file[0]) ;
	return (0);
}

void	connect_to_exec(t_game *game)
{
	game->tn = texture_path(game->info_map.file[game->info_map.NO]);
	game->ts = texture_path(game->info_map.file[game->info_map.SO]);
	game->tw = texture_path(game->info_map.file[game->info_map.WE]);
	game->te = texture_path(game->info_map.file[game->info_map.EA]);
	game->mapy = game->info_map.y + 2;
	game->mapx = game->info_map.longest + 2;
	game->maps = game->mapy * game->mapx;
	game->fcolor = game->info_map.hexf;
	game->ccolor = game->info_map.hexc;
	printf("tn est %s\n", game->tn);
	printf("ts est %s\n", game->ts);
	printf("tw est %s\n", game->tw);
	printf("te est %s\n", game->te);
	printf("map y est %d\n", game->mapy);
	printf("map x %d\n", game->mapx);
	printf("map s est %d\n", game->maps);
	printf("hexf est %lx\n", game->fcolor);
	printf("hexc est %lx\n", game->ccolor);
	printf("dir est %c\n", game->dir);
}


//parsing core
int	parsing(t_game *game, char **argv)
{
	initstruct(game, argv);
	if (convert_file(game, argv))
		return(-1);
	printf("--file converted\n");
	if (check_file(game, argv) == -1)
		return(-1);
	if (maps(game) == -1)
		return(-1);
	return(0);
}

int main(int argc, char **argv)
{
    t_game game;

	if (argc != 2)
		return(1);
	if (parsing(&game, argv) == -1)
		return(1);
	connect_to_exec(&game);
	engine(&game);
}