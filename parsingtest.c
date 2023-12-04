/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingtest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 23:41:46 by chugot            #+#    #+#             */
/*   Updated: 2023/12/04 16:38:16 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    parsing(t_game *game)
{
    //int img_width;
    //int img_height;
    int i;

    i = 0;
    game->map = malloc(sizeof(char *) * 6); //a free

    while (i < 6)
    {
        game->map[i] = malloc(sizeof(char) * 14);
        i++;
    }
    game->map[i] = malloc(sizeof(char) * 1);
    game->mapx = 13;
    game->mapy = 5;
    game->maps = 13 * 5;
    game->map[0] = "1111111111111\0";
    game->map[1] = "1000000001001\0";
    game->map[2] = "1000000001001\0";
    game->map[3] = "1000000N00001\0";
    game->map[4] = "1111111111111\0";
    game->map[5] = NULL;

    //game->img_no = mlx_xpm_file_to_image(game->window.mlx, "nomfichier.xpm", &img_width, &img_height);
}
//voir type variable les couleurs de plafond et murs. dans fonction my_pixel_put c'est un int color mais avec ce format : 0x00FF0000. 
//voir comment convertir l'info de la map direct en ça.