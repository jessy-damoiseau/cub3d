/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 23:32:22 by user42            #+#    #+#             */
/*   Updated: 2021/05/04 23:33:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		nb_virgule(char *str)
{
	int	i;
	int	nb_coma;

	i = 0;
	nb_coma = 1;
	while (str[i])
	{
		if (str[i] == ',')
		{
			nb_coma++;
			i++;
		}
		else
			i++;
	}
	return (nb_coma);
}

int		check_virgule(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == ',' && str[i + 1] == ',')
			return (fprintf(stderr, "Error\nTwo consecutive comma\n"));
	return (0);
}

int		len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
