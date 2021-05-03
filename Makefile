# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/15 00:53:32 by jessy             #+#    #+#              #
#    Updated: 2021/05/03 16:57:09 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS = 	parsing/check_error.c\
		parsing/check_map.c\
		parsing/ft_strtrim.c\
		parsing/list.c\
		parsing/parse.c\
		parsing/parse2.c\
		parsing/parse3.c\
		parsing/parsing_rfc.c\
		parsing/gnl/get_next_line_utils.c\
		parsing/gnl/get_next_line.c\
		parsing/utils/utils.c\
		parsing/utils/utils2.c\
		parsing/init.c\
		\
		srcs/mlx_loop.c\
		srcs/mlx_utils.c\
		srcs/mlx_utils2.c\
		srcs/init_for_calcul.c\
		srcs/init_for_calcul2.c\
		srcs/mlx_move.c\
		srcs/mlx_print.c\
		srcs/print_col.c\
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
