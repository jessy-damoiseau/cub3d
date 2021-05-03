/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 15:49:55 by user42            #+#    #+#             */
/*   Updated: 2021/05/03 17:42:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_textures(t_parsing *global)
{
	int fd;

	fd = open(global->parse.no, O_RDONLY);
	if (read(fd, 0, 0) == -1)
		return (close(fd));
	close(fd);
	fd = open(global->parse.so, O_RDONLY);
	if (read(fd, 0, 0) == -1)
		return (close(fd));
	close(fd);
	fd = open(global->parse.we, O_RDONLY);
	if (read(fd, 0, 0) == -1)
		return (close(fd));
	close(fd);
	fd = open(global->parse.ea, O_RDONLY);
	if (read(fd, 0, 0) == -1)
		return (close(fd));
	close(fd);
	fd = open(global->parse.s, O_RDONLY);
	if (read(fd, 0, 0) == -1)
		return (close(fd));
	close(fd);
	return (1);
}

int	check_args_texture_next(t_parsing *global)
{
	int	i;

	i = 0;
	while (global->parse.ea[i])
		if (global->parse.ea[i] == ' ' || !++i)
			return (1);
	i = 0;
	while (global->parse.s[i])
		if (global->parse.s[i] == ' ' || !++i)
			return (1);
	return (0);
}

int	check_args_texture(t_parsing *global)
{
	int i;

	i = 0;
	if (!global->parse.no[0] || !global->parse.so[0] || !global->parse.we[0]
	|| !global->parse.ea[0] || !global->parse.s[0])
		return (1);
	while (global->parse.no[i])
		if (global->parse.no[i] == ' ' || !++i)
			return (1);
	i = 0;
	while (global->parse.so[i])
		if (global->parse.so[i] == ' ' || !++i)
			return (1);
	i = 0;
	while (global->parse.we[i])
		if (global->parse.we[i] == ' ' || !++i)
			return (1);
	return (check_args_texture_next(global));
}

int	check_file_next(int i, char **arg)
{
	int fd;

	fd = open(arg[i], O_RDONLY);
	if (read(fd, 0, 0) == -1)
	{
		fprintf(stderr, "this file doesn't exist\n");
		close(fd);
		return (0);
	}
	close(fd);
	if (!ft_strcmp(&arg[i][ft_strlen(arg[i]) - 4], ".cub"))
	{
		fprintf(stderr, "Error: File extension is not in .cub\n");
		return (0);
	}
	return (i);
}

int	check_file(int ac, char **arg, t_parsing *global)
{
	int i;

	i = 1;
	if (ac == 3)
	{
		if (!ft_strcmp(arg[1], "--save"))
		{
			fprintf(stderr, "Error: bad argument\n");
			return (0);
		}
		global->value.save = 1;
		i = 2;
	}
	if (ac > 3 || ac < 2)
	{
		if (ac > 3)
			fprintf(stderr, "Error: Too many arguments\n");
		else
			fprintf(stderr, "Error: not enough argument\n");
		return (0);
	}
	return (check_file_next(i, arg));
}
