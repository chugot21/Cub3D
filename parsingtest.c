/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingtest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 23:41:46 by chugot            #+#    #+#             */
/*   Updated: 2023/12/06 18:33:20 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    parsing(t_game *game)
{
    //int img_width;
    //int img_height;
    //int i;

    //i = 0;
    //game->map = malloc(sizeof(int) * 13 * 5); //a free

    //while (i < 6)
    //{
    //    game->map[i] = malloc(sizeof(char) * 14);
    //    i++;
    //}
    //game->map[i] = malloc(sizeof(char) * 1);
    game->mapy = 6;
    game->mapx = 13;
    game->maps = game->mapx * game->mapy;
    game->map = malloc(sizeof(int) * game->maps);
    game->dir = 'N';
    game->map[0] = 1;
    game->map[1] = 1;
    game->map[2] = 1;
    game->map[3] = 1;
    game->map[4] = 1;
    game->map[5] = 1;
    game->map[6] = 1;
    game->map[7] = 1;
    game->map[8] = 1;
    game->map[9] = 1;
    game->map[10] = 1;
    game->map[11] = 1;
    game->map[12] = 1;
    game->map[13] = 1;
    game->map[14] = 0;
    game->map[15] = 0;
    game->map[16] = 0;
    game->map[17] = 0;
    game->map[18] = 0;
    game->map[19] = 0;
    game->map[20] = 0;
    game->map[21] = 0;
    game->map[22] = 1;
    game->map[23] = 0;
    game->map[24] = 0;
    game->map[25] = 1;
    game->map[26] = 1;
    game->map[27] = 0;
    game->map[28] = 0;
    game->map[29] = 0;
    game->map[30] = 0;
    game->map[31] = 0;
    game->map[32] = 0;
    game->map[33] = 0;
    game->map[34] = 0;
    game->map[35] = 1;
    game->map[36] = 0;
    game->map[37] = 0;
    game->map[38] = 1;
    game->map[39] = 1;
    game->map[40] = 0;
    game->map[41] = 0;
    game->map[42] = 0;
    game->map[43] = 0;
    game->map[44] = 0;
    game->map[45] = 0;
    game->map[46] = 7;
    game->map[47] = 0;
    game->map[48] = 0;
    game->map[49] = 0;
    game->map[50] = 0;
    game->map[51] = 1;
    game->map[52] = 1;
    game->map[53] = 0;
    game->map[54] = 0;
    game->map[55] = 0;
    game->map[56] = 0;
    game->map[57] = 0;
    game->map[58] = 0;
    game->map[59] = 0;
    game->map[60] = 0;
    game->map[61] = 0;
    game->map[62] = 0;
    game->map[63] = 0;
    game->map[64] = 1;
    game->map[65] = 1;
    game->map[66] = 1;
    game->map[67] = 1;
    game->map[68] = 1;
    game->map[69] = 1;
    game->map[70] = 1;
    game->map[71] = 1;
    game->map[72] = 1;
    game->map[73] = 1;
    game->map[74] = 1;
    game->map[75] = 1;
    game->map[76] = 1;
    game->map[77] = 1;
    //game->map[0] = "1111111111111\0";
    //game->map[1] = "1000000001001\0";
    //game->map[2] = "1000000001001\0";
    //game->map[3] = "1000000N00001\0";
    //game->map[4] = "1111111111111\0";
    //game->map[5] = NULL;

    //game->img_no = mlx_xpm_file_to_image(game->window.mlx, "nomfichier.xpm", &img_width, &img_height);
}
//voir type variable les couleurs de plafond et murs. dans fonction my_pixel_put c'est un int color mais avec ce format : 0x00FF0000. 
//voir comment convertir l'info de la map direct en ça.