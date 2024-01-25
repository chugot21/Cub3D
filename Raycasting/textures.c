/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 23:41:46 by chugot            #+#    #+#             */
/*   Updated: 2024/01/25 15:01:44 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_texture_fd(char *path)
{
	int	file;

    file = open(path, O_RDONLY);
	if (file == -1)
		perror("Error\n");
	return (file);
}

int	*texture(char *path)
{
	int		fd;
	char	*line;
	char	**stack;
	int		i;
	int		*pixel;
	pixel = malloc(sizeof(int) * 32 * 32 * 3);
	fd = get_texture_fd(path);
	line = get_next_line(fd); //<<<<<<<<<<<<<<<<<<<
	stack = ft_split(line, ','); //<<<<<<<<<<<<
    free(line);
	i = 0;
	while (stack[i])
	{
		pixel[i] = atoi(stack[i]);
		i++;
	}
    free_map(stack);
	return (pixel);
}

void    ft_textures(t_game *game)
{
    game->t_north = texture(game->tn);
    game->t_south = texture(game->ts);
    game->t_west = texture(game->tw);
    game->t_east = texture(game->te);
}
