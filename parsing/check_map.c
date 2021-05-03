/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:11:30 by jdamoise          #+#    #+#             */
/*   Updated: 2021/05/03 21:09:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_hole(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '3' && (!find(map[i][j + 1])
			|| !find(map[i][j - 1])
			|| !find(map[i + 1][j]) || !find(map[i - 1][j])))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int        propagation(int x, int y, char **map, int stop)
{
    int    x_max;

    x_max = 0;
    while (map[x_max + 1])
        x_max++;
    if (x == x_max || x == 0 || !map[x][y + 1] || !map[x][y] || y == 0)
        return (14);
    if (!stop)
    {
        map[x][y] = '3';
        if (map[x][y + 1] == '0' || map[x][y + 1] == '2')
            propagation(x, y + 1, map, stop);
        if (map[x][y - 1] == '0' || map[x][y - 1] == '2')
            propagation(x, y - 1, map, stop);
        if (map[x + 1][y] == '0' || map[x + 1][y] == '2')
            propagation(x + 1, y, map, stop);
        if (map[x - 1][y] == '0' || map[x - 1][y] == '2')
            propagation(x - 1, y, map, stop);
    }
    if (map[x][y] == ' ' || map[x + 1][y] == ' ' || map[x - 1][y] == ' '
    || map[x][y + 1] == ' ' || map[x][y - 1] == ' ')
        stop = 1;
    return (check_hole(map));
}

char	*fill_space(char *str, int len)
{
	char *dest;
	int i;
	int str_len;

	i = 0;
	str_len = ft_strlen(str);
	if (!(dest = malloc(sizeof(char) * (len + 1))))
		return (0);
	while (i < str_len)
	{
		dest[i] = str[i];
		i++;
	}
	while (i < len)
		dest[i++] = ' ';
	dest[i] = '\0';
	free(str);
	return (dest);
}

char **fill_space_map(t_parsing *global)
{
	int i;
	int line_len;

	i = -1;
	line_len = 0;
	i = -1;
	while (global->parse.map[++i])
		if (ft_strlen(global->parse.map[i]) > line_len)
			line_len = ft_strlen(global->parse.map[i]);
	i = -1;
	while (global->parse.map[++i])
		global->parse.map[i] =  fill_space(global->parse.map[i], line_len);
	return (global->parse.map);
}

int		check_map(char **map)
{
	int x;
	int y;
	int done;

	x = 0;
	done = 0;
	while (map[x] && !done)
	{
		y = 0;
		while (map[x][y] && !done)
		{
			if (map[x][y] == 'N' || map[x][y] == 'W'
			|| map[x][y] == 'S' || map[x][y] == 'E')
				done = 1;
			else
				y++;
		}
		if (!done)
			x++;
	}
	done = propagation(x, y, map, 0);
	free_ds(map);
	if (done)
		return (1);
	return (0);
	
}
