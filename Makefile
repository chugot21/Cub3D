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

SRCS =	parsingtest.c \
		cub3d.c \
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
		Utils/ft_split.c \

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
