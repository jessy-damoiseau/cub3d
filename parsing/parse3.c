/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 15:52:09 by user42            #+#    #+#             */
/*   Updated: 2021/04/28 15:53:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_param_next(t_parsing *global)
{
	int		i;
	t_file	*temp;

	i = 0;
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

int	get_param(t_parsing *global)
{
	t_file	*temp;
	int		ret_fill;

	while (global->file->line[0] != '1' && global->file->line[0] != '0'
	&& global->file->line[0] != '2' && global->file->line[0] != ' ')
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
	return (get_param_next(global));
}

int	check_error_next2(int nb_error, t_parsing *global)
{
	int	nb_spawn;

	nb_spawn = check_spawn(global->parse.map);
	if (nb_spawn)
	{
		if (nb_spawn < 0)
			fprintf(stderr, "Error: Empty spawn point\n");
		else
			fprintf(stderr, "Error: Multi spawn point\n");
		nb_error++;
	}
	else
	{
		if (check_map(str_ds_dup(global->parse.map)))
		{
			fprintf(stderr, "Error: map non valide\n");
			nb_error++;
		}
	}
	if (nb_error)
		return (1);
	return (0);
}

int	check_error_next(int nb_error, t_parsing *global)
{
	if (!check_textures(global))
	{
		fprintf(stderr, "Error: l'une des textures n'existe pas\n");
		nb_error++;
	}
	if (check_fc(global->parse.c) != 3 || check_fc(global->parse.f) != 3)
	{
		fprintf(stderr, "Error: -F/C: pas le bon nombre d'argument\n");
		nb_error++;
	}
	return (check_error_next2(nb_error, global));
}

int	check_error(t_parsing *global)
{
	int nb_error;

	nb_error = 0;
	if (check_r(global->parse.r) != 2)
	{
		fprintf(stderr, "Error: -R: pas le bon nombre d'argument\n");
		nb_error++;
	}
	if (check_args_texture(global))
	{
		fprintf(stderr,
		"Error: -NO/SO/WE/AE/S: Pas le bon nombre d'argument\n");
		nb_error++;
	}
	if (!ft_strcmp(&global->parse.no[ft_strlen(global->parse.no) - 4], ".xpm")
	|| !ft_strcmp(&global->parse.so[ft_strlen(global->parse.so) - 4], ".xpm")
	|| !ft_strcmp(&global->parse.ea[ft_strlen(global->parse.ea) - 4], ".xpm")
	|| !ft_strcmp(&global->parse.we[ft_strlen(global->parse.we) - 4], ".xpm")
	|| !ft_strcmp(&global->parse.s[ft_strlen(global->parse.s) - 4], ".xpm"))
	{
		fprintf(stderr, "Error: Texture extension in not in .xpm\n");
		nb_error++;
	}
	return (check_error_next(nb_error, global));
}
