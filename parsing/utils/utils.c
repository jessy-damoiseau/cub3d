/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdamoise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:43:42 by jdamoise          #+#    #+#             */
/*   Updated: 2021/02/23 19:42:55 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*ft_strdup(char *str)
{
	int		i;
	char	*dest;

	i = 0;
	if (!(dest = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (0);
	while (str[i++])
		dest[i - 1] = str[i - 1];
	dest[i - 1] = '\0';
	free(str);
	return (dest);
}

int		ft_strcmp(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (str1[i] == str2[i])
		return (1);
	return (0);
}

void	clear_parse(t_parse *parse)
{
	if (parse->r)
		free(parse->r);
	if (parse->s)
		free(parse->s);
	if (parse->f)
		free(parse->f);
	if (parse->c)
		free(parse->c);
	if (parse->no)
		free(parse->no);
	if (parse->so)
		free(parse->so);
	if (parse->ea)
		free(parse->ea);
	if (parse->we)
		free(parse->we);
	if (parse->map)
		free_ds(parse->map);
}

int		ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
