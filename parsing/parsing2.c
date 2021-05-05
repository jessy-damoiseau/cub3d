/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 23:38:14 by user42            #+#    #+#             */
/*   Updated: 2021/05/04 23:39:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		check_r(t_global *global, t_psing *psing, int *i)
{
	if (*psing->file->line && psing->file->line[0] == 'R'
			&& psing->file->line[1] == ' ' && !psing->parse.r)
	{
		(*i)++;
		if (check_error_r(psing->file->line, &psing->parse.r, global))
			return (1);
	}
	else if (*psing->file->line && psing->file->line[0] == 'R'
			&& psing->file->line[1] == ' ' && psing->parse.r)
		return (fprintf(stderr, "Error\nDuplicate R parameter\n"));
	return (0);
}

int		check_f(t_global *global, t_psing *psing, int *i)
{
	if (*psing->file->line && psing->file->line[0] == 'F'
			&& psing->file->line[1] == ' ' && !psing->parse.f)
	{
		(*i)++;
		if (check_error_fc(psing->file->line, &psing->parse.f, global, 'F'))
			return (1);
	}
	else if (*psing->file->line && psing->file->line[0] == 'F'
			&& psing->file->line[1] == ' ' && psing->parse.f)
		return (fprintf(stderr, "Error\nDuplicate F parameter\n"));
	return (0);
}

int		check_c(t_global *global, t_psing *psing, int *i)
{
	if (*psing->file->line && psing->file->line[0] == 'C'
			&& psing->file->line[1] == ' ' && !psing->parse.c)
	{
		(*i)++;
		if (check_error_fc(psing->file->line, &psing->parse.c, global, 'C'))
			return (1);
	}
	else if (*psing->file->line && psing->file->line[0] == 'C'
			&& psing->file->line[1] == ' ' && psing->parse.c)
		return (fprintf(stderr, "Error\nDuplicate C parameter\n"));
	return (0);
}

int		check_no(t_global *global, t_psing *psing, int *i)
{
	if (*psing->file->line && psing->file->line[0] == 'N' &&
			psing->file->line[1] == 'O' &&
			psing->file->line[2] == ' ' && !psing->parse.no)
	{
		(*i)++;
		if (check_error_texture(psing->file->line, global, 'N'))
			return (1);
	}
	else if (*psing->file->line && psing->file->line[0] == 'N' &&
			psing->file->line[1] == 'O' &&
			psing->file->line[2] == ' ' && psing->parse.no)
		return (fprintf(stderr, "Error\nDuplicate NO parameter\n"));
	return (0);
}

int		check_so(t_global *global, t_psing *psing, int *i)
{
	if (*psing->file->line && psing->file->line[0] == 'S' &&
			psing->file->line[1] == 'O' &&
			psing->file->line[2] == ' ' && !psing->parse.so)
	{
		(*i)++;
		if (check_error_texture(psing->file->line, global, 'S'))
			return (1);
	}
	else if (*psing->file->line && psing->file->line[0] == 'S' &&
			psing->file->line[1] == 'O' &&
			psing->file->line[2] == ' ' && psing->parse.so)
		return (fprintf(stderr, "Error\nDuplicate SO parameter\n"));
	return (0);
}
