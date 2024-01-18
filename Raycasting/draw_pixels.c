/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:40:57 by chugot            #+#    #+#             */
/*   Updated: 2024/01/18 16:29:58 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_game *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	create_hexa_rgb(int r, int g, int b)
{
	int	color;

	color = ((r & 0xff) << 16) + ((g & 0xff) << 8) + ((b & 0xff));
	return (color);
}

int	find_pixel_color(int x, int y, int *texture)
{
	int	pixel;
	int	r;
	int	g;
	int	b;

	pixel = ((int)y * 32 + (int)x) * 3;
	r = texture[pixel + 0];
	g = texture[pixel + 1];
	b = texture[pixel + 2];
	return (create_hexa_rgb(r, g, b));
}
