# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/15 00:53:32 by jessy             #+#    #+#              #
#    Updated: 2021/05/04 16:10:11 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS = 	parsing/gnl/gnl.c\
		parsing/gnl/gnl_utils.c\
		parsing/check_error.c\
		parsing/fill_param.c\
		parsing/parsing.c\
		parsing/utils.c\
		parsing/utils2.c\
		\
		srcs/mlx_loop.c\
		srcs/mlx_utils.c\
		srcs/mlx_utils2.c\
		srcs/init_for_calcul.c\
		srcs/init_for_calcul2.c\
		srcs/mlx_move.c\
		srcs/mlx_print.c\
		srcs/print_col.c\
		srcs/fill_bmp.c\
		\
		main.c\

OBJS = ${SRCS:.c=.o}

CC = gcc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -c

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:	${NAME}

${NAME}:	${OBJS} compil_other
		
		${CC} -o ${NAME} ${OBJS} -L./minilibx-linux/ -lmlx_Linux -lm -lbsd -lX11 -lXext
clean:	clean_other
		${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

compil_other:
		cd minilibx-linux && make

clean_other:
		cd minilibx-linux && make clean

test: ${NAME} clean
	./cub3d map/txt.cub

re:		fclean all

.PHONY: clean all fclean re
