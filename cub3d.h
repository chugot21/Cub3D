/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 23:41:46 by chugot            #+#    #+#             */
/*   Updated: 2023/12/22 15:58:52 by clara            ###   ########.fr       */
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
# include "gc/gc.h"

# define PI 3.1415926535897932384626433832795028841971693993751058
# define P2 PI / 2
# define P3 3 * PI / 2
# define DEGREE_RADIAN 0.0174533

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
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

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_map
{
	t_point 	start_player; //idem que player mais axel utilise player pour ses calculs ?
	size_t		x_map; // = game->mapx -> on change ? pour le moment juste relie dans parsing(t_game *game)
	size_t		y_map; // = game->mapy -> on change ? pour le moment juste relie dans parsing(t_game *game)
	char		**map; //ok laisse la
	char 		**map_to_int; //ok laisse la 
	char		**copy_map; //ok laisse la

	char		*no1; //tn
	char		*so1; //ts
	char		*we1; //tw
	char		*ea1; //te
	t_texture	no;
	t_texture	so;
	t_texture	we;
	t_texture	ea;
	int			*f1;
	int			*c1;
	int			x_wall;
	int			y_wall;
	int			map_error;
	int			cell_color;
	int			floor_color;
	int			trace;
	int 		trace_first_line;
	int			y_map_trace;
}	t_map;

typedef struct s_game
{
	t_map *tmap;
	char *path_map;
	int			trace;
	t_gcan	gc;




	t_window	window;
	int			win_x;
	int			win_y;
	int			*map;
	int			mapy;
	int			mapx;
	int			maps;
	char		dir;
	int			*frgb;
	int			*crgb;
	int			fcolor; //floor
	int			ccolor; //ceiling
	//Pour afficher
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	//For raycasting
	t_point		player; //position départ
	t_point		player_pixel; //position depart pixel to draw player.
	double		pa; //angle de la camera par rapport au joueur.
	t_point		pdelta; //direction joueur
	int			r; //compteur pour nombre de rays affiché à l'écran. largeur de la vue camera.
	t_point		m;
	int			mp;
	int			dof; //compte les carrés jsuqu'au mur
	t_point		ray; //trouver longueur rayon de la position du joueur jusqu'au prochain x ou y.
	double		ra; //egal a pa.
	t_point		xoyo; //longueur entre deux cotes x ou y.
	double		dis_horiz; //distance hit horiz
	t_point		horizon; //point hit wall horiz
	double		dis_verti; //distance hit wall verti
	t_point		vertical; //point hit wall verti
	double		dist; //distance finale retenue - la plus courte.
	double		line_height; //hauteur de la ligne a tracer du mur
	double		line_offset; //decalage de ligne
	double		ca; //calcul pour fish eye
	//wall texture
	int			color; //couleur du pixel de la texture
	float		shade;
	float		ty_off;
	float		texture_ix;
	float		texture_iy;
	float		ty_step;
	int			*t_north;
	int			*t_south;
	int			*t_west;
	int			*t_east;
	int			side;
	//for collisions and movements
	int			xco;
	int			yco;
	int			ipx;
	int			ipy;
	int			ipx_add_xo;
	int			ipy_add_yo;
	int			ipx_sub_xo;
	int			ipy_sub_yo;
	int			move_right;
	int			move_left;
	int			move_up;
	int			move_down;
	int			rotate_right;
	int			rot_left;
}	t_game;

void	parsing(t_game *game);
void	init_game(t_game *game);
void	draw_background(t_game *game);
void	draw_minimap(t_game *game);
void	draw_player(t_game *game);
int		ft_raycasting(t_game *game);
void	horizontal_rays(t_game *game, double atan);
void	horizontal_rays_next(t_game *game);
void	horizontal_rays_calcul(t_game *game);
void	vertical_rays(t_game *game, double ntan);
void	vertical_rays_next(t_game *game);
void	vertical_rays_calcul(t_game *game);
double	dist(double ax, double ay, double bx, double by);
void	low_rays(t_game *game);
void	fix_fish_eye(t_game *game);
void	draw_column(t_game *game);
void	draw_column_next(t_game *game);
void	draw_textures(t_game *game, int start_pixel);
int		find_pixel_color(int x, int y, int *texture);
void	limits_rays(t_game *game);
void	my_mlx_pixel_put(t_game *data, int x, int y, int color);
void	color_square(t_game *game, int x, int y, int width);
int		create_hexa_rgb(int r, int g, int b);
int		move_player(int keycode, t_game *game);
void	move_right(t_game *game);
void	move_left(t_game *game);
void	move_up(t_game *game);
void	move_down(t_game *game);
int		closew(t_game *game);
void	destroy_all(t_game *game);
size_t	ft_strcmp(char *s1, char *s2);
char	*get_next_line(int fd);
char	*ft_strchr(const char *str, int c);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c);



int		ft_strchr2(char *string);
char	*ft_strstr(char *big, char *lit);
char	*ft_strdup(t_game *data, const char *s);
char	*ft_strdup_special(t_game *data, const char *s);
int		ft_strncmp(char *str1, char *str2, int length);
int		ft_isdigit(int c);
int		ft_strnrchr(char *s, char *c);

//Revu ok
int		check_name(char *argv); //ok

int		is_players(char c, t_game *game); //ok
int		check_player(t_game *game); //presaue idem init_game dans raycasting.
void	open_malloc_map(t_game *data); //ok

//en cours de verif
void	get_map(t_game *game, char *argv);
void	transfert_map(t_game *game, int fd); //->check_info

//a recheck
void	init_parsing(t_game *data);

//a revoir
void	ctoi(t_game *data);
void	map_to_square(t_game *data);
void	end_parss(t_game *data);
void	check_character(t_game *data, char pos, int x, int y);
void	check_info(t_game *data, char *buff, int fd);
void	copy_first_line_map(t_game *data, char *buff, int fd);
void	copy_other_line_map(t_game *data, int fd, char *buff);
void	check_right(t_game *data);
void	check_down(t_game *data);
void	check_left(t_game *data);
void	check_up(t_game *data);
void	check_exit(t_game *data);
int		check_error(t_game *game, char *argv);
int		check_border_map(t_game *game);
void	set_map_data(t_game *data, char *buff, int info, int fd);

void	rotate_player(t_game *data, double angle); //fonction pour lorientation du player au debut 

#endif
