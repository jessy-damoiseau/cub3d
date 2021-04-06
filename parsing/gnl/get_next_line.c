/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 17:38:36 by jessy             #+#    #+#             */
/*   Updated: 2021/02/23 19:39:58 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*get_next_str(char *str)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (0);
	}
	if (!(dest = malloc(sizeof(char) * ((ft_strlen(str) - i) + 1))))
		return (0);
	i++;
	while (str[i])
		dest[j++] = str[i++];
	dest[j] = '\0';
	free(str);
	return (dest);
}

char	*get_line_return(char *str)
{
	int		i;
	char	*dest;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (!(dest = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		get_next_line(int fd, char **line)
{
	char			*buff;
	static char		*str;
	int				i;

	i = 1;
	if (fd < 0 || !line)
		return (-1);
	if (!(buff = malloc(sizeof(char) * (33))))
		return (-1);
	while (!check_return(str) && i != 0)
	{
		if ((i = read(fd, buff, 32)) == -1)
		{
			free(buff);
			return (-1);
		}
		buff[i] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	*line = get_line_return(str);
	str = get_next_str(str);
	if (i == 0)
		return (0);
	return (1);
}
