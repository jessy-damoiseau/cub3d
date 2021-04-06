/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdamoise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:41:32 by jdamoise          #+#    #+#             */
/*   Updated: 2021/03/22 12:35:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int check_textures(t_parsing *global)
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

int		check_args_texture(t_parsing *global)
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


int		check_error(t_parsing *global)
{
	int nb_spawn;
	int nb_error;

	nb_error = 0;
	if (check_r(global->parse.r) != 2)
	{
		fprintf(stderr, "Error: -R: pas le bon nombre d'argument\n");
		nb_error++;
	}
	if (check_args_texture(global))
	{
		fprintf(stderr, "Error: -NO/SO/WE/AE/S: Pas le bon nombre d'argument\n");
		nb_error++;
	}
	else if (!ft_strcmp(&global->parse.no[ft_strlen(global->parse.no) - 4], ".xpm")
	|| !ft_strcmp(&global->parse.so[ft_strlen(global->parse.so) - 4], ".xpm")
	|| !ft_strcmp(&global->parse.ea[ft_strlen(global->parse.ea) - 4], ".xpm")
	|| !ft_strcmp(&global->parse.we[ft_strlen(global->parse.we) - 4], ".xpm")
	|| !ft_strcmp(&global->parse.s[ft_strlen(global->parse.s) - 4], ".xpm"))
	{
		fprintf(stderr, "Error: Texture extension in not in .xpm\n");
		nb_error++;
	}
	else if(!check_textures(global))
	{
		fprintf(stderr, "Error: l'une des textures n'existe pas\n");
		nb_error++;
	}
	if (check_fc(global->parse.c) != 3 || check_fc(global->parse.f) != 3)
	{
		fprintf(stderr, "Error: -F/C: pas le bon nombre d'argument\n");
		nb_error++;
	}
	nb_spawn = check_spawn(global->parse.map);
	if (nb_spawn)
	{
		fprintf(stderr, "check13.1\n");
		if (nb_spawn < 0)
			fprintf(stderr, "Error: Empty spawn point\n");
		else
			fprintf(stderr, "Error: Multi spawn point\n");
		nb_error++;
	}
	else
		if(check_map(str_ds_dup(global->parse.map)))
		{
			fprintf(stderr, "Error: map non valide\n");
			nb_error++;
		}
	if (nb_error)
		return (1);
	return (0);
}

int		fill_struct_param(char *param, t_parse *parse)
{
	if (!param[0])
		return (0);
	if ((param[0] == 'R' && param[1] == ' ') || (param[0] == 'S' && param[1] == ' ')
	|| (param[0] == 'F' && param[1] == ' ') || (param[0] == 'C' && param[1] == ' '))
	{
		if (param[0] == 'R')
		{
			if (parse->r)
				return (1);
			parse->r = ft_strdup(ft_strtrim(&param[1], " "));
		}
		else if (param[0] == 'S')
		{
			if (parse->s)
				return (1);
			parse->s = ft_strdup(ft_strtrim(&param[1], " "));
		}
		else if (param[0] == 'F')
		{
			if (parse->f)
				return (1);
			parse->f = ft_strdup(ft_strtrim(&param[1], " "));
		}
		else if (param[0] == 'C')
		{
			if (parse->c)
				return (1);
			parse->c = ft_strdup(ft_strtrim(&param[1], " "));
		}
		return (0);
	}
	else if ((param[0] == 'N' && param[1] == 'O') || (param[0] == 'S' && param[1] == 'O')
		|| (param[0] == 'E' && param[1] == 'A') || (param[0] == 'W' && param[1] == 'E'))
	{
		if (param[0] == 'N')
		{
			if (parse->no)
				return (1);
			parse->no = ft_strdup(ft_strtrim(&param[2], " "));
		}
		else if (param[0] == 'S')
		{
			if (parse->so)
				return (1);
			parse->so = ft_strdup(ft_strtrim(&param[2], " "));
		}
		else if (param[0] == 'E')
		{
			if (parse->ea)
				return (1);
			parse->ea = ft_strdup(ft_strtrim(&param[2], " "));
		}
		else if (param[0] == 'W')
		{
			if (parse->we)
				return (1);
			parse->we = ft_strdup(ft_strtrim(&param[2], " "));
		}
		return (0);
	}
	return (-1);
}

int		get_param(t_parsing *global)
{
	int		i;
	t_file	*temp;
	int	ret_fill;
	
	i = 0;
	while (global->file->line[0] != '1' && global->file->line[0] != '0' && global->file->line[0] != '2' && global->file->line[0] != ' ')
	{
		temp = global->file;
		if (check_is_param(global->file->line))
			global->parse.nb_param_fill++;
		if (!(check_is_param(global->file->line) || !global->file->line[0]))
			return (-1);
		ret_fill = fill_struct_param(global->file->line, &global->parse);
		if (ret_fill)
		{
			ft_lstclear(&global->file);
			clear_parse(&global->parse);
			return (ret_fill);
		}
		free(global->file->line);
		global->file = global->file->next;
		free(temp);
	}
	if (!(global->parse.map = malloc(sizeof(char *)
					* (ft_lstsize(global->file) + 1))))
		return (1);
	while (global->file)
	{
		global->parse.map[i++] = global->file->line;
		temp = global->file;
		global->file = global->file->next;
		free(temp);
	}
	global->parse.map[i] = 0;
	return (0);
}

int		check_file(int ac, char **arg)
{
	int fd;
	int i;

	i = 1;
	if (ac == 3)
	{
		if (!ft_strcmp(arg[1], "--save"))
		{
			fprintf(stderr, "Error: mauvais argument\n");
			return (0);
		}
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
	fd = open(arg[i], O_RDONLY);
	if (read(fd, 0, 0) == -1)
	{
		fprintf(stderr, "ce ficher n'exite pas\n");
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

int		parse(int ac, t_parsing *global, char **arg)
{
	char	*line;
	int		fd;
	int		ret_get_param;
	int		i;
	
	init_parsing(global);
	if (!(i = check_file(ac, arg)))
		return (1);
	fd = open(arg[i], O_RDONLY);
	line = 0;
	global->file = 0;
	if (fd < 0)
		return (1);
	while (get_next_line(fd, &line) == 1)
		ft_lstadd_back(&global->file, ft_lstnew(line));
	ft_lstadd_back(&global->file, ft_lstnew(line));
	close(fd);
	ret_get_param = get_param(global);
	if (global->parse.nb_param_fill != 8 && !ret_get_param)
	{
		fprintf(stderr, "Error: Not enough parameter\n");
		clear_parse(&global->parse);
		return (1);
	}
	if (ret_get_param)
	{
		if (ret_get_param == -1)
			fprintf(stderr, "Error: unwanted parameter\n");
		else
			fprintf(stderr, "Error: duplicate parameter\n");
		clear_parse(&global->parse);
		return (1);
	}
	if (check_error(global))
	{
		clear_parse(&global->parse);
		return (1);
	}
	parsing_rfc(global);
	//if (ac == 3)
	//	print_bmp();
	return (0);
}
