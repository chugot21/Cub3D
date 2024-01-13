/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:49:50 by chugot            #+#    #+#             */
/*   Updated: 2024/01/12 16:50:07 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_parsing(t_game *data)
{
	data->tmap = gc_malloc(&data->gc, sizeof(t_map));
	data->tmap->x_map = 0;
	data->tmap->y_map = 0;
	data->tmap->trace = 0;
	data->trace = 0;
	data->tmap->trace_first_line = 0;
	data->tmap->y_map_trace = 0;
	/*data->ray_i = gc_malloc(&data->gc, sizeof(t_ray));
	data->mlx_i = gc_malloc(&data->gc, sizeof(t_mlx));*/
	data->tmap->f1 = NULL;
	data->tmap->c1 = NULL;
	data->tmap->no1 = NULL;
	data->tmap->so1 = NULL;
	data->tmap->we1 = NULL;
	data->tmap->ea1 = NULL;
	data->tmap->x_wall = 0;
	data->tmap->y_wall = 1;
	data->tmap->map_error = 0;
}

void ctoi(t_game *data)
{
	size_t y;
	size_t x;
	int i;


	y = 0;
	i = 0;
	data->map = gc_malloc(&data->gc, sizeof(int)  * (data->tmap->y_map + 2) * (data->tmap->x_map + 2));
	while (y < data->tmap->y_map + 3)
	{
		x = 0;
		while (x < data->tmap->x_map + 2)
		{
			data->map[i] = (data->tmap->map_to_int[y][x]) - 48;
			printf("%d", data->map[i]);
			i++;
			x++;
		//	printf("%c", data->tmap->map_to_int[y][x]);
		}
		printf("\n");
		y++;
	}

}

void map_to_square(t_game *data)
{
	size_t	y;
	size_t	x;

	x = 0;
	y = 0;
	data->tmap->map_to_int = gc_malloc(&data->gc,
			sizeof(char *) * data->tmap->y_map + 4);
	data->tmap->map_to_int[y] = malloc(sizeof(char) * data->tmap->x_map + 2);
	while (x < data->tmap->x_map + 2)
	{
		data->tmap->map_to_int[y][x] = '4';
		x++;
	}
	while (y < data->tmap->y_map + 1)
	{
		data->tmap->map_to_int[y + 1] = ft_strdup_special
			(data, data->tmap->map[y]);
		y++;
	}
	y++;
	x = 0;
	data->tmap->map_to_int[y] = malloc(sizeof(char) * data->tmap->x_map + 2);
	while (x < data->tmap->x_map + 2)
	{
		data->tmap->map_to_int[y][x] = '4';
		x++;
	}
	//data->tmap->map_to_int[y + 1] = NULL;
	for (size_t i = 0; i < 16; i++)
		printf("char to int [%zu]=%s=\n", i,data->tmap->map_to_int[i]);
}

void end_parss(t_game *data)
{
	map_to_square(data);
	ctoi(data);
}
