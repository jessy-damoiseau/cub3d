/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 23:35:38 by user42            #+#    #+#             */
/*   Updated: 2021/05/04 23:37:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	nb_args_r(char *str)
{
	int i;
	int nb_args;

	i = 0;
	nb_args = 1;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			while (str[i] && str[i] == ' ')
				i++;
			nb_args++;
		}
		i++;
	}
	return (nb_args);
}

int	check_error_r(char *line, int *c, t_global *global)
{
	int		i;
	int		nb_args;
	char	*str;

	i = -1;
	trim(&str, line, "R ");
	while (str[++i])
		if ((str[i] < '0' && str[i] > '9') && str[i] != ' ')
			return (fprintf(stderr, "Error\n-R undesirable characters\n"));
	nb_args = nb_args_r(str);
	if (nb_args != 2)
		return (fprintf(stderr, "Error\n-R not the right number of args\n"));
	if (fill_xy(str, &global->psing, c))
		return (1);
	return (0);
}

int	check_error_fc2(char *str, int *param, t_global *global, int c)
{
	int nb_coma;

	nb_coma = nb_virgule(str);
	if (check_virgule(str))
		return (1);
	if (nb_coma != 3)
	{
		if (nb_coma < 3)
			return (fprintf(stderr, "Error\n-%c not enough d'args\n", c));
		else
			return (fprintf(stderr, "Error\n-%c too many args\n", c));
	}
	fill_fc(str, &global->psing, param, c);
	return (0);
}

int	check_error_fc(char *line, int *param, t_global *global, int c)
{
	int		i;
	char	*str;

	i = -1;
	if (c == 'F')
		trim(&str, line, "F ");
	else
		trim(&str, line, "C ");
	while (str[++i])
		if (!(str[i] >= '0' && str[i] <= '9') && str[i] != ',')
			return (fprintf(stderr, "Error\n-%c unwanted character\n", c));
	i = 0;
	if (str[0] == ',' || str[len(str) - 1] == ',')
	{
		return (fprintf(stderr,
		"Error\n-%c comma at the beginning or at the end of the param\n", c));
	}
	return (check_error_fc2(str, param, global, c));
}

int	check_error_texture(char *line, t_global *global, int c)
{
	int		i;
	char	*str;

	i = 0;
	if (c == 'N')
		trim(&str, line, "NO ");
	else if (c == 'S')
		trim(&str, line, "SO ");
	else if (c == 'W')
		trim(&str, line, "WE ");
	else
		trim(&str, line, "EA ");
	if (!str[i])
		return (fprintf(stderr, "Error\nTexture %c not enough args", c));
	while (str[i])
		if (str[i++] == ' ')
			return (fprintf(stderr, "Error\nTexture %c too many args\n", c));
	if (cmp(&str[len(str) - 4], ".xpm"))
	{
		return (fprintf(stderr,
		"Error\nTexture %c does not have .xpm as extension\n", c));
	}
	fill_texture(str, &global->psing, c);
	return (0);
}
