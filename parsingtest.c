/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingtest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 23:41:46 by chugot            #+#    #+#             */
/*   Updated: 2023/12/08 18:07:54 by clara            ###   ########.fr       */
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
    //char **mapchar;
    //int i = 0;
    //int j;
    //int k = 0;

    //mapchar = malloc(sizeof(char *) * 6 + 1);
    game->mapy = 7;
    game->mapx = 14;
    game->maps = game->mapx * game->mapy;
    game->map = malloc(sizeof(int) * game->maps);
    game->dir = 'N';

    //int mapinit[] =
    //{
    //    1,1,1,1,1,1,1,1,1,1,1,1,1,
    //    1,7,0,0,0,0,0,0,0,0,0,1,1,
    //    1,0,0,0,0,0,0,0,0,0,0,0,1,
    //    1,0,0,0,0,0,0,0,0,0,0,0,1,
    //    1,1,1,1,1,1,1,1,1,1,1,1,1,
    //};
    //game->map = mapinit;

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
    game->map[13] = 1; //14
    game->map[14] = 1;
    game->map[15] = 1;
    game->map[16] = 7;
    game->map[17] = 0;
    game->map[18] = 0;
    game->map[19] = 0;
    game->map[20] = 0;
    game->map[21] = 0;
    game->map[22] = 0;
    game->map[23] = 0;
    game->map[24] = 0;
    game->map[25] = 0;
    game->map[26] = 1;
    game->map[27] = 1; //14
    game->map[28] = 1;
    game->map[29] = 0;
    game->map[30] = 0;
    game->map[31] = 0;
    game->map[32] = 0;
    game->map[33] = 0;
    game->map[34] = 0;
    game->map[35] = 0;
    game->map[36] = 0;
    game->map[37] = 0;
    game->map[38] = 0;
    game->map[39] = 0;
    game->map[40] = 1;
    game->map[41] = 1; //14
    game->map[42] = 1;
    game->map[43] = 0;
    game->map[44] = 0;
    game->map[45] = 0;
    game->map[46] = 0;
    game->map[47] = 0;
    game->map[48] = 0;
    game->map[49] = 0;
    game->map[50] = 0;
    game->map[51] = 0;
    game->map[52] = 0;
    game->map[53] = 0;
    game->map[54] = 1;
    game->map[55] = 1; //14
    game->map[56] = 1;
    game->map[57] = 0;
    game->map[58] = 0;
    game->map[59] = 0;
    game->map[60] = 0;
    game->map[61] = 0;
    game->map[62] = 0;
    game->map[63] = 0;
    game->map[64] = 0;
    game->map[65] = 0;
    game->map[66] = 0;
    game->map[67] = 0;
    game->map[68] = 1;
    game->map[69] = 1; //14
    game->map[70] = 1;
    game->map[71] = 1;
    game->map[72] = 1;
    game->map[73] = 1;
    game->map[74] = 1;
    game->map[75] = 1;
    game->map[76] = 1;
    game->map[77] = 1;
    game->map[78] = 1;
    game->map[79] = 1;
    game->map[80] = 1;
    game->map[81] = 1;
    game->map[82] = 1;
    game->map[83] = 1;
    game->map[84] = 1;
    game->map[85] = 1;
    game->map[86] = 1;
    game->map[87] = 1;
    game->map[88] = 1;
    game->map[89] = 1;
    game->map[90] = 1;
    game->map[91] = 1;
    game->map[92] = 1;
    game->map[93] = 1;
    game->map[94] = 1;
    game->map[95] = 1;
    game->map[96] = 1;
    game->map[97] = 1;

    //mapchar[0] = "1111111111111\0";
    //mapchar[1] = "1700000000001\0";
    //mapchar[2] = "1000000000001\0";
    //mapchar[3] = "1000000000001\0";
    //mapchar[4] = "1111111111111\0";
    //mapchar[5] = NULL;
    
    //while(mapchar[i] != NULL)
    //{
    //    j = 0;
    //    while (mapchar[i][j] != '\0')
    //    {
    //        game->map[k] = mapchar[i][j] - 48;
    //        printf("map[%d] : %d", k, game->map[k]);
    //        j++;
    //        k++;
    //    }
    //    i++;
    //}
    //k = 0;
    //while(k < 78)
    //{
    //    k++;
    //}

    //game->img_no = mlx_xpm_file_to_image(game->window.mlx, "nomfichier.xpm", &img_width, &img_height);
}
//voir type variable les couleurs de plafond et murs. dans fonction my_pixel_put c'est un int color mais avec ce format : 0x00FF0000. 
//voir comment convertir l'info de la map direct en ça.