/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 23:28:51 by user42            #+#    #+#             */
/*   Updated: 2021/05/04 23:33:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		trim_cmp(char s, char *set)
{
	int	i;

	i = 0;
	while (set[i] && set[i] != s)
		i++;
	if (set[i])
		return (1);
	return (0);
}

void	trim(char **dest, char *s, char *set)
{
	int	i;
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (trim_cmp(s[k], (char *)set))
		k++;
	if (s[k])
	{
		i = len(s) - k - 1;
		while (trim_cmp(s[k + i], (char *)set))
			i--;
		i++;
	}
	if (!((*dest) = malloc(sizeof(char) * (i + 1))))
		return ;
	while (j < i)
		(*dest)[j++] = s[k++];
	(*dest)[j] = 0;
	free(s);
}

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

int		find(int c)
{
	char	*str;
	int		i;

	i = 0;
	str = "13";
	while (str[i])
		if (str[i++] == c)
			return (1);
	return (0);
}
