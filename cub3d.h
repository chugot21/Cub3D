/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 23:41:46 by chugot            #+#    #+#             */
/*   Updated: 2023/11/24 17:35:26 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <stdlib.h>
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <pthread.h>
# include <math.h>

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_window
{
	void	*mlx;
	void	*win;
}	t_window;

typedef struct s_game
{
	t_window	window;
	int win_x;
	int	win_y;
	char	**map;
	void	*img_no;
	void	*img_so;
	void	*img_we;
	void	*img_ea;

	//Pour afficher
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;

	//For raycasting

	t_point	player; //position départ
	t_point player_pixel; //position depart pixel to draw player.
	int	x; //initialisation pour boucle generale.

	//t_point	vec_dir; //direction joueur
	//t_point vec_plan; //plan camera
	//double	camerax; //coordonnee x de la camera.
	//t_point raydir; //rayon de la camera.
	//t_point map_here; // position exacte du joueur.
	//t_point sidedist; //longueur du rayon depuis la position actuelle jusqu'au prochain côté x ou y.
	//t_point deltadist; //longueur entre deux côtés x ou y.
	//double perpWallDist; //calcul la longueur du rayon. perpendiculaire au plan camera.
	//t_point step; //sens de direction de x et y (+1 ou -1)
	//int hit; //est-ce qu'on a touché un mur ?
	//int side; //si x (mur EW) alors 0 si y (mur NS) alors 1.

	//variable for drawing
	//int line_height;
	//int drawstart;
	//int	drawend;
	//int color;
	//double movespeed; //squares/second
	//double rotspeed; //radians/second

	int move_right;
	int move_left;
	int move_up;
	int move_down;
	//int rotate_right;
	//int rotate_left;
	
}	t_game;

int		closew(t_game *game);
void	destroy_all(t_game *game);
void    parsing(t_game *game);
void	draw_minimap(t_game *game);
void	draw_player(t_game *game);
void	my_mlx_pixel_put(t_game *data, int x, int y, int color);
int		moves_activated(int keycode, t_game *game);
void	move_player(t_game *game);
int		moves_disactivated(int keycode, t_game *game);
void	init_game(t_game *game);

size_t	ft_strcmp(char *s1, char *s2);

#endif
