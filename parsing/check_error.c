/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 22:22:38 by user42            #+#    #+#             */
/*   Updated: 2021/05/04 23:37:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_error_sprite(char *line, t_global *global)
{
	int		i;
	char	*str;

	i = 0;
	trim(&str, line, "S ");
	if (!str[i])
		return (fprintf(stderr, "Error\nNot enough args for sprites"));
	while (str[i])
		if (str[i++] == ' ')
			return (fprintf(stderr, "Error\nToo many args for sprites\n"));
	if (cmp(&str[len(str) - 4], ".xpm"))
	{
		return (fprintf(stderr,
		"Error\nPath for sprites does not have .xpm as extension\n"));
	}
	global->psing.parse.s = str;
	global->psing.parse.nb_pfill++;
	return (0);
}

int	check_char_map(t_global *global)
{
	int	i;
	int	j;

	i = 0;
	while (global->psing.parse.map[i])
	{
		j = 0;
		while (global->psing.parse.map[i][j])
		{
			if (global->psing.parse.map[i][j] != ' '
			&& global->psing.parse.map[i][j] != '0' &&
			global->psing.parse.map[i][j] != '1' &&
			global->psing.parse.map[i][j] != '2' &&
			global->psing.parse.map[i][j] != 'N' &&
			global->psing.parse.map[i][j] != 'W' &&
			global->psing.parse.map[i][j] != 'S' &&
			global->psing.parse.map[i][j] != 'E')
				return (fprintf(stderr, "Error\nUnwanted char in the map\n"));
			j++;
		}
		i++;
	}
	return (0);
}

int	check_hole(char **map)
{
	int	i;
	int	j;

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

int	propagation(int x, int y, char **map, int stop)
{
	int	x_max;

	x_max = 0;
	while (map[x_max + 1])
		x_max++;
	if (x == x_max || x == 0 || !map[x][y + 1] || !map[x][y] || y == 0)
		return (1);
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

int	check_error_map(t_global *global)
{
	char	**str;

	if (check_char_map(global))
		return (1);
	if (check_spawn(global))
		return (1);
	str = str_ds_dup(global->psing.parse.map);
	str[global->psing.value.y][global->psing.value.x] = '0';
	if (propagation(global->psing.value.y, global->psing.value.x, str, 0))
		return (fprintf(stderr, "Error\nThe accessible map has a hole\n"));
	free_ds(str);
	return (0);
}
