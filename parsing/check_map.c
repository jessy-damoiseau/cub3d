/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdamoise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:11:30 by jdamoise          #+#    #+#             */
/*   Updated: 2021/03/22 12:36:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		check_hole(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '3' && (!find(map[i][j + 1]) || !find(map[i][j - 1])
				|| !find(map[i + 1][j]) || !find(map[i - 1][j])))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

char	**propagation(int x, int y, char **map, int stop)
{
	int x_max;

	x_max = 0;
	while (map[x_max])
		x_max++;
	if (x == x_max || x == 0 || !map[x][y + 1] || !map[x][y] ||  y == 0
	|| map[x][y] == ' ' || map[x + 1][y] == ' ' || map[x - 1][y] == ' '
	|| map[x][y + 1] == ' ' || map[x][y - 1] == ' ')
		stop = 1;
	if (!stop)
	{
		map[x][y] = '3';
		if (map[x][y + 1] == '0')
			propagation(x, y + 1, map, stop);
		if (map[x][y - 1] == '0')
			propagation(x, y - 1, map, stop);
		if (map[x + 1][y] == '0')
			propagation(x + 1, y, map, stop);
		if (map[x - 1][y] == '0')
			propagation(x - 1, y, map, stop);
	}
	return (map);
}

int	check_map(char **map)
{
	int x;
	int y;
	int done;

	x = 0;
	done = 0;
	while(map[x] && !done)
	{
		y = 0;
		while (map[x][y] && !done)
		{
			if(map[x][y] == 'N' || map[x][y] == 'W'
			|| map[x][y] == 'S' || map[x][y] == 'E')
				done = 1;
			else
				y++;
		}
		if (!done)
			x++;
	}
	done = check_hole(propagation(x, y, map, 0));
	free_ds(map);
	if (done)
		return (1);
	return (0);
}
