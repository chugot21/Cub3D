# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clara <clara@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 12:00:49 by chugot            #+#    #+#              #
#    Updated: 2024/01/25 15:50:22 by clara            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	cub3D

SRCS =	Parsing/main.c \
		Parsing/checkfile.c \
		Parsing/maps.c \
		Parsing/maps2.c \
		Parsing/checkmap.c \
		Parsing/checkmap2.c \
		Parsing/colors.c \
		Parsing/colors2.c \
		Parsing/checktextures.c \
		Parsing/checktextures2.c \
		Parsing/parsing_utils.c \
		Parsing/parsing_utils2.c \
		Raycasting/init_raycasting.c \
		Raycasting/raycasting.c \
		Raycasting/horizontal_rays.c \
		Raycasting/vertical_rays.c \
		Raycasting/draw_rays.c \
		Raycasting/draw_pixels.c \
		Raycasting/player_moves.c \
		Raycasting/moves.c \
		Raycasting/textures.c \
		Raycasting/minimap.c \
		destroy.c \
		Utils/utils.c \
		Utils/get_next_line_bonus.c \
		Utils/ft_split.c \
		#Raycasting/engine.c \#

CC = cc

FLAGS = -g -Wall -Wextra -Werror

DEBUG	= -g3 #-fsanitize=address

OBJS = $(SRCS:.c=.o)

MLX_LIB	= ./minilibx-linux/libmlx.a

MLX_FLAG =	-lX11 -lXext

MLX_EX =	$(MLX_LIB) $(MLX_FLAG) ./libft/libft.a

all:	$(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME):	$(LIBGCDIR)/$(LIBGC) $(OBJS)
			make all -C libft
			$(CC) $(OBJS) $(MLX_EX) $(DEBUG) -o $(NAME) -lm
clean:
		make clean -C libft
		rm -f $(OBJS)

fclean:
		make fclean -C libft
		rm -f $(OBJS) $(NAME)

re:		fclean all

.PHONY:	all clean fclean re

.SILENT: