# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jessy <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/15 00:53:32 by jessy             #+#    #+#              #
#    Updated: 2021/03/19 15:57:08 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS = 	parsing/check_error.c\
		parsing/check_map.c\
		parsing/ft_strtrim.c\
		parsing/list.c\
		parsing/parse.c\
		parsing/parsing_rfc.c\
		parsing/gnl/get_next_line_utils.c\
		parsing/gnl/get_next_line.c\
		parsing/utils/utils.c\
		parsing/utils/utils2.c\
		parsing/init.c\
		\
		mlx/mlx_loop.c\
		mlx/mlx_utils.c\
		mlx/print_map.c\
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
