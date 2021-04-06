/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdamoise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:33:54 by jdamoise          #+#    #+#             */
/*   Updated: 2021/02/23 20:38:28 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		check_r(char *r)
{
	int i;
	int nb_args;

	i = 0;
	nb_args = 0;
	while (r[i])
	{
		if (!ft_isdigit(r[i]) && r[i] != ' ')
		{
			if (nb_args == 2)
				return (nb_args + 1);
			return (nb_args);
		}
		if (ft_isdigit(r[i]))
		{
			nb_args++;
			while (ft_isdigit(r[i]))
				i++;
		}
		else
			i++;
	}
	return (nb_args);
}

int		check_fc(char *str)
{
	int nb_args;
	int nb_comma;

	nb_args = 0;
	nb_comma = 0;
	while (*str)
	{
		if (*str == ',')
			nb_comma++;
		if (nb_comma > 2)
			return (nb_args + 1);
		if (!ft_isdigit(*str) && *str != ',')
		{
			if ( nb_args == 3)
				return (nb_args + 1);
			return (nb_args);
		}
		if (ft_isdigit(*str))
		{
			nb_args++;
			while (ft_isdigit(*str))
				str++;
		}
		else
			str++;
	}
	return (nb_args);
}
int		check_spawn(char **map)
{
	int i;
	int j;
	int	nb_spawn;

	i = 0;
	nb_spawn = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
			|| map[i][j] == 'E' || map[i][j] == 'W')
				nb_spawn++;
			j++;
		}
		i++;
	}
	if (nb_spawn != 1)
	{
		if (nb_spawn > 1)
			return (1);
		else
			return (-1);
	}
	return (0);
}

int		check_is_param(char *line)
{
	if ((line[0] == 'R' && line[1] == ' ') || (line[0] == 'F' && line[1] == ' ')
	|| (line[0] == 'S' && line[1] == ' ') || (line[0] == 'C' && line[1] == ' ')
	|| (line[0] == 'N' && line[1] == 'O' && line [2] == ' ')
	|| (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
	|| (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
	|| (line[0] == 'E' && line[1] == 'A' && line[2] == ' '))
		return (1);
	return (0);
}
