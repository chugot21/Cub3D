# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clara <clara@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 12:00:49 by chugot            #+#    #+#              #
#    Updated: 2023/11/24 17:39:46 by clara            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	cub3D

SRCS =	cub3d.c \
		parsingtest.c \
		parsing/init_parsing.c \
		parsing/check_border.c \
		parsing/malloc_map.c \
		parsing/parsing.c \
		parsing/set_texture.c \
		parsing/flood_fill.c \
		parsing/copy_map.c \
		parsing/check_error.c \
		Raycasting/init_raycasting.c \
		Raycasting/raycasting.c \
		Raycasting/horizontal_rays.c \
		Raycasting/vertical_rays.c \
		Raycasting/draw_rays.c \
		Raycasting/draw_pixels.c \
		Raycasting/player_moves.c \
		Raycasting/moves.c \
		destroy.c \
		Utils/utils.c \
		Utils/get_next_line_bonus.c \
		Utils/get_next_line_special.c \
		Utils/ft_split.c \
		Utils/util.c \
		Utils/strdups.c \

CC = cc

FLAGS = -g -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

LIBGCDIR = gc

LIBGC = libgc.a

LIBGCFLAGS = -L $(LIBGCDIR) -l:$(LIBGC)

MLX_LIB	= ./minilibx-linux/libmlx.a

MLX_FLAG =	-lX11 -lXext

MLX_EX =	$(MLX_LIB) $(MLX_FLAG)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all:	$(NAME)

$(NAME):	$(LIBGCDIR)/$(LIBGC) $(OBJS)
			$(CC) $(OBJS) $(MLX_EX) $(LIBGCFLAGS) -o $(NAME) -lm
clean:
		rm -f $(OBJS)

fclean:
		rm -f $(OBJS) $(NAME)

re:		fclean $(NAME)

.PHONY:	all clean fclean re
