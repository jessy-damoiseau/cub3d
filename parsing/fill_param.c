/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 22:52:34 by user42            #+#    #+#             */
/*   Updated: 2021/05/04 23:34:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		fill_xy(char *str, t_psing *psing, int *c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		psing->value.rx = psing->value.rx * 10 + str[i++] - '0';
	if (psing->value.rx == 0)
		return (fprintf(stderr, "Error\nInvalid x resolution\n"));
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i])
		psing->value.ry = psing->value.ry * 10 + str[i++] - '0';
	if (psing->value.ry == 0)
		return (fprintf(stderr, "Error\nInvalid y resolution\n"));
	psing->parse.nb_pfill++;
	(*c)++;
	free(str);
	return (0);
}

void	fill_f(char *str, t_psing *psing)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			psing->value.floor[j] = psing->value.floor[j] * 10 + str[i++] - '0';
		else
		{
			j++;
			i++;
		}
	}
	j = 0;
	while (j < 3)
		if (psing->value.floor[j++] > 255)
			psing->value.floor[j - 1] = 255;
}

void	fill_c(char *str, t_psing *psing)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			psing->value.sky[j] = psing->value.sky[j] * 10 + str[i++] - '0';
		else
		{
			j++;
			i++;
		}
	}
	j = 0;
	while (j < 3)
		if (psing->value.sky[j++] > 255)
			psing->value.sky[j - 1] = 255;
}

void	fill_fc(char *str, t_psing *psing, int *param, int c)
{
	if (c == 'F')
	{
		fill_f(str, psing);
	}
	else
	{
		fill_c(str, psing);
	}
	psing->parse.nb_pfill++;
	(*param)++;
	free(str);
}

void	fill_texture(char *str, t_psing *psing, int c)
{
	if (c == 'N')
		psing->parse.no = str;
	else if (c == 'S')
		psing->parse.so = str;
	else if (c == 'W')
		psing->parse.we = str;
	else
		psing->parse.ea = str;
	psing->parse.nb_pfill++;
}
