/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rfc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 20:49:04 by jessy             #+#    #+#             */
/*   Updated: 2021/02/23 21:47:12 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_atoi_r(char *str)
{
	int result;
	int i;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9' && result >= 0)
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (result < 0)
		return (2147483647);
	return (result);
}

int		ft_atoi_fc(char *str)
{
	int result;
	int i;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9' && result >= 0)
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (result < 0 || result > 255)
		return (255);
	return (result);
}

void	parsing_r(t_parsing *global)
{
	int	i;

	i = 0;
	global->value.rx = ft_atoi_r(global->parse.r);
	while (global->parse.r[i] != ' ')
		i++;
	global->value.ry = ft_atoi_r(&global->parse.r[i + 1]);
}

void	parsing_rfc(t_parsing *global)
{
	int i;
	int j;

	i = -1;
	j = 0;
	parsing_r(global);
	global->value.floor[j++] = ft_atoi_fc(global->parse.f);
	while (global->parse.f[++i])
		if (global->parse.f[i] == ',')
			global->value.floor[j++] = ft_atoi_fc(&global->parse.f[i + 1]);
	i = -1;
	j = 0;
	global->value.sky[j++] = ft_atoi_fc(global->parse.c);
	while (global->parse.c[++i])
		if (global->parse.c[i] == ',')
			global->value.sky[j++] = ft_atoi_fc(&global->parse.c[i + 1]);
}
