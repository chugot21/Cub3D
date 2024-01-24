/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgourlai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:16:29 by mgourlai          #+#    #+#             */
/*   Updated: 2024/01/23 19:16:30 by mgourlai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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