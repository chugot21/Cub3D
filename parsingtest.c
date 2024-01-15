/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingtest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 23:41:46 by chugot            #+#    #+#             */
/*   Updated: 2023/12/22 16:17:36 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture_fd(char *path)
{
	int		file;
	//path[ft_strlen(path) - 1] = 0;
	//file = open(path + 3, O_RDONLY); //revoir le + 3 car il peut y avoir plus d'espaces.
    file = open(path, O_RDONLY);
	if (file == -1)
		perror("Error : can't open texture\n");
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
	line = get_next_line(fd);
	stack = ft_split(line, ',');
	i = 0;
	while (stack[i])
	{
		pixel[i] = atoi(stack[i]);
		i++;
	}
	return (pixel);
}

void    parsing(t_game *game)
{
    /* feuille de route :
        en cours de verif 
    */


    /*Gestion d'erreurs :
    nbr of argument -> ok
    .cub -> ok
    erreur d'open ? est-ce qu'on gere tout ?
    ok si espace sur la ligne pour les couleurs et textures
    texture si open et toutes les textures sont presentes
    textures en format .ppm
    il y a bien un joueur


    */



   /*check si pb :
        mapy et mapx
        map
        dir
        crgb
        frgb
        tno, tso, twe, tea
        printf map
        printf copy_map
    */
    
    //game->mapy = 7; //hauteur map
    //game->mapx = 14; //largeur map
    game->mapy = (int)game->tmap->y_map;
    game->mapx = (int)game->tmap->x_map;
    game->maps = game->mapx * game->mapy;
    //game->dir = 'S'; ok fait dans is_players

    //game->crgb = malloc(sizeof(int) * 3); //recup couleur ceiling
    //game->frgb = malloc(sizeof(int) * 3); //recup couleur floor.
    //game->crgb[0] = 102;
    //game->crgb[1] = 204;
    //game->crgb[2] = 255;
    //game->frgb[0] = 102;
    //game->frgb[1] = 51;
    //game->frgb[2] = 51;

    //char *tno;
	//char *tso;
	//char *twe;
	//char *tea;
    //tno = "./Textures/texture_north.ppm"; // recup textures de chaque direction.
    //tso = "./Textures/texture_south.ppm";
    //twe = "./Textures/texture_west.ppm";
    //tea = "./Textures/texture_east.ppm";

    game->t_north = texture(game->tno);
    game->t_south = texture(game->tso);
    game->t_west = texture(game->twe);
    game->t_east = texture(game->tea);
   
    //int mapinit[] = //fonctionne pas car local
    //{
    //    1,1,1,1,1,1,1,1,1,1,1,1,1,
    //    1,7,0,0,0,0,0,0,0,0,0,1,1,
    //    1,0,0,0,0,0,0,0,0,0,0,0,1,
    //    1,0,0,0,0,0,0,0,0,0,0,0,1,
    //    1,1,1,1,1,1,1,1,1,1,1,1,1,
    //};
    //game->map = mapinit;

    /*game->map[0] = 1;
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
    game->map[15] = 0;
    game->map[16] = 0;
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
    game->map[34] = 7;
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
    game->map[97] = 1;*/
}
