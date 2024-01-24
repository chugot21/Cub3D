/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgourlai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:14:09 by mgourlai          #+#    #+#             */
/*   Updated: 2024/01/23 19:14:10 by mgourlai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	connect_to_exec(t_game *game)
{
	game->tn = texture_path(game->info_map.file[game->info_map.NO]);
	game->ts = texture_path(game->info_map.file[game->info_map.SO]);
	game->tw = texture_path(game->info_map.file[game->info_map.WE]);
	game->te = texture_path(game->info_map.file[game->info_map.EA]);
	game->mapy = game->info_map.y + 3;
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

//parsing core
int	parsing(t_game *game, char **argv)
{
	initstruct(game, argv);
	if (convert_file(game, argv) == -1)
		return(error("couldn't convert file, look out for tabs\n"));
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