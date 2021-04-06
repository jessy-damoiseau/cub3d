/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:37:39 by jessy             #+#    #+#             */
/*   Updated: 2021/03/11 23:19:33 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int		cmp(char s, char *set)
{
	int i;

	i = 0;
	while (set[i] && set[i] != s)
		i++;
	if (set[i])
		return (1);
	return (0);
}

char	*ft_strtrim(char *s, char *set)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*c;

	i = 0;
	j = 0;
	k = 0;
	while (cmp(s[k], (char *)set))
		k++;
	if (s[k])
	{
		while (s[k + i])
			i++;
		i--;
		while (cmp(s[k + i], (char *)set))
			i--;
		i++;
	}
	if (!(c = malloc(sizeof(*c) * (i + 1))))
		return (0);
	while (j < i)
		c[j++] = s[k++];
	c[j] = 0;
	return (c);
}
