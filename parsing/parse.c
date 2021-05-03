/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:41:32 by jdamoise          #+#    #+#             */
/*   Updated: 2021/05/03 17:19:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	param_rsfc(char *param, t_parse *parse)
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

int	param_nswe(char *param, t_parse *parse)
{
	if (param[0] == 'N')
	{
		if (parse->no)
			return (1);
		parse->no = ft_strtrim(&param[2], " ");
	}
	else if (param[0] == 'S')
	{
		if (parse->so)
			return (1);
		parse->so = ft_strtrim(&param[2], " ");
	}
	else if (param[0] == 'E')
	{
		if (parse->ea)
			return (1);
		parse->ea = ft_strtrim(&param[2], " ");
	}
	else if (param[0] == 'W')
	{
		if (parse->we)
			return (1);
		parse->we = ft_strtrim(&param[2], " ");
	}
	return (0);
}

int	fill_struct_param(char *param, t_parse *parse)
{
	if (!param[0])
		return (0);
	if ((param[0] == 'R' && param[1] == ' ')
	|| (param[0] == 'S' && param[1] == ' ')
	|| (param[0] == 'F' && param[1] == ' ')
	|| (param[0] == 'C' && param[1] == ' '))
		return (param_rsfc(param, parse));
	if ((param[0] == 'N' && param[1] == 'O')
	|| (param[0] == 'S' && param[1] == 'O')
	|| (param[0] == 'E' && param[1] == 'A')
	|| (param[0] == 'W' && param[1] == 'E'))
		return (param_nswe(param, parse));
	return (-1);
}

int	parse_next(int ret_get_param, t_parsing *global)
{
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
	return (0);
}

int	parse(int ac, t_parsing *global, char **arg)
{
	char	*line;
	int		fd;
	int		ret_get_param;
	int		i;

	init_parsing(global);
	if (!(i = check_file(ac, arg, global)))
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
	return (parse_next(ret_get_param, global));
}
