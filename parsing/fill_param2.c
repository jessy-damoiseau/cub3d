/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_param2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 23:34:22 by user42            #+#    #+#             */
/*   Updated: 2021/05/04 23:35:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		fill_map2(t_psing *psing, int i, int len_map)
{
	int		j;
	t_file	*tmp;

	while (psing->file)
	{
		j = 0;
		if (!(psing->parse.map[i] = malloc(sizeof(char) * (len_map + 1))))
			return (fprintf(stderr, "Error\n malloc fail\n"));
		while (psing->file->line[j])
		{
			psing->parse.map[i][j] = psing->file->line[j];
			j++;
		}
		while (j < psing->parse.len_map)
			psing->parse.map[i][j++] = ' ';
		psing->parse.map[i][j] = 0;
		tmp = psing->file;
		psing->file = psing->file->next;
		free(tmp);
		i++;
	}
	psing->parse.map[i] = 0;
	return (0);
}

int		fill_map(t_psing *psing)
{
	int		nb_map;

	nb_map = lst_size(psing->file, psing);
	if (!nb_map)
		return (fprintf(stderr, "Error\nThe map doesn't exist\n"));
	if (!(psing->parse.map = malloc(sizeof(char *) * (nb_map + 1))))
		return (fprintf(stderr, "Error\n malloc fail\n"));
	return (fill_map2(psing, 0, psing->parse.len_map));
}
