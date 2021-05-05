/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 23:36:55 by user42            #+#    #+#             */
/*   Updated: 2021/05/04 23:37:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_spawn(t_global *global)
{
	int	i;
	int	j;
	int	spawn;

	i = 0;
	spawn = 0;
	while (global->psing.parse.map[i])
	{
		j = 0;
		while (global->psing.parse.map[i][j])
		{
			if (find_spawn(global->psing.parse.map[i][j]))
			{
				global->psing.value.x = j;
				global->psing.value.y = i;
				spawn++;
			}
			j++;
		}
		i++;
	}
	if (spawn != 1)
		return (fprintf(stderr, "Error\nThere are %d spawn point\n", spawn));
	return (0);
}

int	find_spawn(int c)
{
	int		i;
	char	*str;

	str = "NSWE";
	i = 0;
	while (str[i])
		if (str[i++] == c)
			return (1);
	return (0);
}
