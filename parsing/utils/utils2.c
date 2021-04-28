/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 20:36:03 by jessy             #+#    #+#             */
/*   Updated: 2021/03/19 15:25:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	**str_ds_dup(char **str)
{
	char	**dest;
	int		i;
	int		j;

	i = 0;
	dest = 0;
	while (str[i])
		i++;
	if (!(dest = malloc(sizeof(char *) * (i + 1))))
		return (0);
	i = -1;
	while (str[++i])
	{
		j = 0;
		while (str[i][j])
			j++;
		if (!(dest[i] = malloc(sizeof(char) * (j + 1))))
			return (0);
		j = -1;
		while (str[i][++j])
			dest[i][j] = str[i][j];
		dest[i][j] = '\0';
	}
	dest[i] = 0;
	return (dest);
}

void	free_ds(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	while (i >= 0)
		free(map[i--]);
	free(map);
}

int		find(char c)
{
	char	*str;
	int		i;

	i = 0;
	str = "123";
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

void	value_windows_size(t_global *global)
{
	int	wx;
	int	wy;

	mlx_get_screen_size(global->mlx.mlx, &wx, &wy);
	if (global->parsing.value.rx > wx)
		global->parsing.value.rx = wx;
	if (global->parsing.value.ry > wy)
		global->parsing.value.ry = wy;
}
