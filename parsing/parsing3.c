/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 23:39:03 by user42            #+#    #+#             */
/*   Updated: 2021/05/04 23:44:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		check_if_map(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '2'
				&& line[i] != '0' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int		check_file(int ac, char **av, int *i, t_psing *psing)
{
	int	j;

	j = 1;
	if (ac == 3)
	{
		if (cmp(av[1], "--save"))
			return (fprintf(stderr, "Error\n movais paramettre\n"));
		else
			j = 2;
		psing->value.save = 1;
	}
	if (ac < 2 || ac > 3)
	{
		if (ac < 2)
			fprintf(stderr, "Error\n pas assez d'args\n");
		else
			fprintf(stderr, "Error\n trop d'args\n");
		return (1);
	}
	if (cmp(&av[j][len(av[j]) - 4], ".cub"))
		return (fprintf(stderr, "Error\n fichier sans extention .cub\n"));
	*i = j;
	return (0);
}

int		check_we(t_global *global, t_psing *psing, int *i)
{
	if (*psing->file->line && psing->file->line[0] == 'W' &&
			psing->file->line[1] == 'E' &&
			psing->file->line[2] == ' ' && !psing->parse.we)
	{
		(*i)++;
		if (check_error_texture(psing->file->line, global, 'W'))
			return (1);
	}
	else if (*psing->file->line && psing->file->line[0] == 'W' &&
			psing->file->line[1] == 'E' &&
			psing->file->line[2] == ' ' && psing->parse.we)
		return (fprintf(stderr, "Error\nDuplicate WE parameter\n"));
	return (0);
}

int		check_ea(t_global *global, t_psing *psing, int *i)
{
	if (*psing->file->line && psing->file->line[0] == 'E' &&
			psing->file->line[1] == 'A' &&
			psing->file->line[2] == ' ' && !psing->parse.ea)
	{
		(*i)++;
		if (check_error_texture(psing->file->line, global, 'E'))
			return (1);
	}
	else if (*psing->file->line && psing->file->line[0] == 'E' &&
			psing->file->line[1] == 'A' &&
			psing->file->line[2] == ' ' && psing->parse.ea)
		return (fprintf(stderr, "Error\nDuplicate EA parameter\n"));
	return (0);
}

int		check_s(t_global *global, t_psing *psing, int *i)
{
	if (*psing->file->line && psing->file->line[0] == 'S' &&
			psing->file->line[1] == ' ' && !psing->parse.s)
	{
		(*i)++;
		if (check_error_sprite(psing->file->line, global))
			return (1);
	}
	else if (*psing->file->line && psing->file->line[0] == 'S' &&
			psing->file->line[1] == ' ' && psing->parse.s)
		return (fprintf(stderr, "Error\nDuplicate S parameter\n"));
	return (0);
}
