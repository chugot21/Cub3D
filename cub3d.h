/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:56:51 by mgourlai          #+#    #+#             */
/*   Updated: 2024/02/02 13:50:58 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//tab non gerer, voir subject_map
//pb avec angle_map, on dirait qu'il n'y a pas de \n a la fin des 
//lignes de game->info_map.copy et que ca cause un  soucis sur les maps d'apres

#ifndef CUB3D_H
# define CUB3D_H
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <math.h>
# include <pthread.h>
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include "libft/libft.h"

# define PI 3.1415926535897932384626433832795028841971693993751058
# define DEGREE_RADIAN 0.0174533

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_map
{
	char			**file;
	char			**map;
	char			**copy;
	int				linecount;
	int				map_start;
	int				map_end;
	int				longest;
	int				no;
	int				so;
	int				we;
	int				ea;
	int				floor;
	unsigned long	hexf;
	int				ceiling;
	unsigned long	hexc;
	int				x;
	int				y;
}	t_map;

typedef struct s_window
{
	void	*mlx;
	void	*win;
}	t_window;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_player
{
	int	x;
	int	y;
}	t_player;

typedef struct s_data
{
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_game
{
	t_player		player;
	t_map			info_map;
	t_window		window;
///////////////////////////
	int				*map;
	int				*minimap;
	int				mapy;
	int				mapx;
	int				maps;
	char			dir;
	unsigned long	fcolor; //floor
	unsigned long	ccolor; //ceiling
///////////////////////////
	int				win_x;
	int				win_y;
	int				xco;
	int				yco;
	int				ipx;
	int				ipy;
	int				ipx_add_xo;
	int				ipy_add_yo;
	int				ipx_sub_xo;
	int				ipy_sub_yo;
	int				move_right;
	int				move_left;
	int				move_up;
	int				move_down;
	int				rotate_right;
	int				rot_left;
	int				map_flag;
	int				proportion;
	//wall texture
	char			*tn;
	char			*ts;
	char			*tw;
	char			*te;
	int				color; //couleur du pixel de la texture
	float			shade;
	float			ty_off;
	float			texture_ix;
	float			texture_iy;
	float			ty_step;
	int				*t_north;
	int				*t_south;
	int				*t_west;
	int				*t_east;
	int				side;
	//Pour afficher
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	//For raycasting
	t_point			player_pixel; //position depart pixel to draw player.
	double			pa; //angle de la camera par rapport au joueur.
	t_point			pdelta; //direction joueur
	int				r; //compteur nombre rays écran. largeur vue camera.
	t_point			m;
	int				mp;
	int				dof; //compte les carrés jsuqu'au mur
	t_point			ray; //find dist ray position joueur jusqu'a next x ou y
	double			ra; //egal a pa.
	t_point			xoyo; //longueur entre deux cotes x ou y.
	double			dis_horiz; //distance hit horiz
	t_point			horizon; //point hit wall horiz
	double			dis_verti; //distance hit wall verti
	t_point			vertical; //point hit wall verti
	double			dist; //distance finale retenue - la plus courte.
	double			line_height; //hauteur de la ligne a tracer du mur
	double			line_offset; //decalage de ligne
	double			ca; //calcul pour fish eye
	double			draw_px;
	double			draw_py;
	int				width_player;
}	t_game;

///// PARSING FUNCTIONS /////
// main.c
int				main(int argc, char **argv);
int				parsing(t_game *game, char **argv);
void			initstruct(t_game *game, char **argv);
int				connect_to_exec(t_game *game);
int				minimap_to_map(t_game *game);
// errors.c
void			ft_error_frees(t_game *game, int n);
// checkfile.c
int				convert_file(t_game *game, char **argv);
int				check_file(t_game *game, char **argv);
int				map_start(t_game *game);
int				map_end(t_game *game);
int				has_floor_ceiling(t_game *game);
// maps.c
int				maps(t_game *game);
int				map_maker(t_game *game);
int				strs_to_ints(t_game *game);
// maps2.c
int				copy_maker(t_game *game);
void			add_map_copy(t_game *game);
int				add_map_copy2(t_game *game, int i, int j);
// checkmap.c
int				check_map(t_game *game);
int				only_numbers(t_game *game);
int				only_one_player(t_game *game);
int				find_player(t_game *game);
void			longest_line(t_game *game);
// checkmap2.c
int				handle_spaces(t_game *game);
int				ft_get_linecount(int fd);
int				zeros_corner(t_game *game, char **map);
int				final_check(t_game *game, char **map);
void			flood(t_game *game, int x, int y);
// checktextures.c
int				has_textures(t_game *game);
int				can_access_textures(t_game *game);
char			*texture_path(char *line);
// checktextures2.c
int				texture_extension(t_game *game);
int				texture_extension2(t_game *game, int i, int j);
// colors.c
int				get_hexa_color(t_game *game);
int				get_red(t_game *game, int floor);
int				get_green(t_game *game, int floor);
int				get_green2(char *green, int i, int res);
unsigned long	rgb_to_hexa(int red, int green, int blue);
// colors2.c
int				get_blue(t_game *game, int floor);
int				get_blue2(t_game *game, int floor, int i);
int				get_blue3(char *blue, int i, int res);
// parsing_utils.c
void			print_map(char **map);
int				check_extension(char *file, char *ext);
int				valid_rgb(char *str);
int				has_floor_ceiling2(t_game *game, int i, int floor, int ceiling);
int				error(char *str);
// parsing_utils2.c
void			top_bot_line(t_game *game);
void			left_right_line(t_game *game);
int				check_tab(t_game *game);
int				skip_space(char *str);
int				ft_get_tabcount(int fd);

/////GRAPHIC ENGINE FUNCTIONS /////
//void			engine(t_game *game);
void			init_game(t_game *game);
void			draw_background(t_game *game);
int				proportions_minimap(t_game *game);
void			draw_minimap(t_game *game);
int				ft_raycasting(t_game *game);
void			horizontal_rays(t_game *game, double atan);
void			horizontal_rays_next(t_game *game);
void			horizontal_rays_calcul(t_game *game);
void			vertical_rays(t_game *game, double ntan);
void			vertical_rays_next(t_game *game);
void			vertical_rays_calcul(t_game *game);
double			dist(double ax, double ay, double bx, double by);
void			low_rays(t_game *game);
void			fix_fish_eye(t_game *game);
void			draw_column(t_game *game);
void			draw_column_next(t_game *game);
void			draw_textures(t_game *game, int start_pixel);
int				find_pixel_color(int x, int y, int *texture);
void			limits_rays(t_game *game);
void			my_mlx_pixel_put(t_game *data, int x, int y, int color);
int				create_hexa_rgb(int r, int g, int b);
void			ft_textures(t_game *game);
int				move_player(int keycode, t_game *game);
void			move_right(t_game *game);
void			move_left(t_game *game);
void			move_up(t_game *game);
void			move_down(t_game *game);
int				closew(t_game *game);
void			free_map(char **map);
void			destroy_all(t_game *game);
size_t			ft_strcmp(char *s1, char *s2);
char			*get_next_line(int fd);
char			*ft_strchr(const char *str, int c);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strdup(const char *s);
size_t			ft_strlen(const char *str);
char			**ft_split(char const *s, char c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
