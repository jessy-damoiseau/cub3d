/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 23:03:00 by user42            #+#    #+#             */
/*   Updated: 2021/05/05 01:41:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gnl.h"
#include "../includes/cub3d.h"

int		fill_and_checkerror2(t_global *global, t_psing *psing)
{
	t_file	*tmp;

	(void)tmp;
	while (psing->file && !psing->file->line[0])
	{
		tmp = psing->file;
		psing->file = psing->file->next;
	}
	if (!psing->file)
		return (fprintf(stderr, "Error\nNo map\n"));
	fill_map(psing);
	if (check_error_map(global))
		return (1);
	return (0);
}

int		fill_and_checkerror(t_global *global, t_psing *psing)
{
	t_file	*tmp;
	int		i;

	while (psing->parse.nb_pfill != 8 && psing->file)
	{
		i = 0;
		if (check_r(global, psing, &i) || check_f(global, psing, &i)
				|| check_c(global, psing, &i) || check_no(global, psing, &i)
				|| check_so(global, psing, &i) || check_we(global, psing, &i)
				|| check_ea(global, psing, &i) || check_s(global, psing, &i))
			return (1);
		if (!i && psing->file->line[0] && psing->parse.nb_pfill < 8)
		{
			if (check_if_map(psing->file->line))
			{
				return (fprintf(stderr, "Error\n%d parameter(s) are missing\n",
							8 - psing->parse.nb_pfill));
			}
			return (fprintf(stderr, "Error\nBad parameter\n"));
		}
		tmp = psing->file;
		psing->file = psing->file->next;
		free(tmp);
	}
	return (fill_and_checkerror2(global, psing));
}

int		parse(int ac, char **av, t_global *global, t_psing *psing)
{
	int		i;
	int		fd;
	char	*line;

	line = 0;
	psing->file = 0;
	i = 1;
	init_parse(global);
	if (check_file(ac, av, &i, psing))
		return (1);
	fd = open(av[i], O_RDONLY);
	if (fd == -1)
		return (fprintf(stderr, "Error\nInvalid map path \n"));
	while (gnl(fd, &line) == 1)
		lstadd_back(&psing->file, lstnew(line));
	lstadd_back(&psing->file, lstnew(line));
	if (lst_size(psing->file, psing) < 1)
		return (fprintf(stderr, "Error\nEmpty file\n"));
	if (fill_and_checkerror(global, psing))
		return (1);
	return (0);
}

void	init_parse(t_global *global)
{
	int	i;

	i = 0;
	global->psing.parse.r = 0;
	global->psing.parse.no = 0;
	global->psing.parse.so = 0;
	global->psing.parse.we = 0;
	global->psing.parse.ea = 0;
	global->psing.parse.s = 0;
	global->psing.parse.f = 0;
	global->psing.parse.c = 0;
	global->psing.parse.map = 0;
	global->psing.parse.nb_pfill = 0;
	global->psing.value.rx = 0;
	global->psing.value.ry = 0;
	global->psing.value.save = 0;
	global->psing.parse.len_map = 0;
	while (i < 3)
	{
		global->psing.value.floor[i] = 0;
		global->psing.value.sky[i++] = 0;
	}
}

int		clear_parse(t_parse *parse)
{
	if (parse->s)
		free(parse->s);
	if (parse->no)
		free(parse->no);
	if (parse->so)
		free(parse->so);
	if (parse->ea)
		free(parse->ea);
	if (parse->we)
		free(parse->we);
	if (parse->map)
		free_ds(parse->map);
	return (1);
}
