/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 23:41:46 by chugot            #+#    #+#             */
/*   Updated: 2023/12/18 22:14:56 by clara            ###   ########.fr       */
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

//#include "Textures/T_1.ppm"

# define PI 3.1415926535897932384626433832795028841971693993751058
# define P2 PI / 2
# define P3 3 * PI / 2
# define DEGREE_RADIAN 0.0174533

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

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
	int *map;
	int mapy;
	int mapx;
	int maps;
	char dir;
	int *frgb;
	int *crgb;
	int	fcolor; //floor
	int ccolor; //ceiling

	int *texture_one;
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
	int flag_move;

	t_point	player; //position départ
	t_point player_pixel; //position depart pixel to draw player.
	double	pa; //angle de la camera par rapport au joueur.
	t_point	pdelta; //direction joueur
	t_point vec_plan; //plan camera
	//int	x; //initialisation pour boucle generale.
	
	int	r; //compteur pour nombre de rays affiché à l'écran. largeur de la vue camera.
	t_point m;
	int		mp;
	int dof; //compte les carrés jsuqu'au mur
	t_point ray; //trouver longueur rayon de la position du joueur jusqu'au prochain x ou y.
	double ra; //egal a pa.
	t_point xoyo; //longueur entre deux cotes x ou y.
	double dis_horiz; //distance hit horiz
	t_point horizon; //point hit wall horiz
	double dis_verti; //distance hit wall verti
	t_point vertical; //point hit wall verti
	double dist; //distance finale retenue - la plus courte.
	double line_height; //hauteur de la ligne a tracer du mur
	double line_offset; //decalage de ligne
	double ca; //calcul pour fish eye

	//wall texture
	int color; //couleur du pixel de la texture
	float shade;
	float ty_off;
	int i_pixel_width;
	int pixel_width;
	int texture_ix;
	int texture_iy;
	int y_too_high;
	float ty_step;

	//for collisions and movements
	int xco;
	int yco;
	int ipx;
	int ipy;
	int ipx_add_xo;
	int ipy_add_yo;
	int ipx_sub_xo;
	int ipy_sub_yo;
	int move_right;
	int move_left;
	int move_up;
	int move_down;
	int rotate_right;
	int rot_left;
	
}	t_game;

int		closew(t_game *game);
void	destroy_all(t_game *game);
void    parsing(t_game *game);
void	draw_background(t_game *game);
int	create_hexa_rgb(int r, int g, int b);
void	draw_minimap(t_game *game);
//void	draw_player(t_game *game);
void	my_mlx_pixel_put(t_game *data, int x, int y, int color);
void	color_square(t_game *game, int x, int y, int width, int heigth, int color);
void	draw_column(t_game *game);
int		moves_activated(int keycode, t_game *game);
//void	move_player(t_game *game);
void	init_game(t_game *game);
void	draw_direction_line(t_game *game);
int	ft_raycasting(t_game *game);

int	move_player(int keycode, t_game *game);

size_t	ft_strcmp(char *s1, char *s2);
char	*get_next_line(int fd);
char	*ft_strchr(const char *str, int c);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c);

#endif
