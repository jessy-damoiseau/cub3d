/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:29:04 by user42            #+#    #+#             */
/*   Updated: 2021/05/05 01:36:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_header(t_global *global, int fd)
{
	int	tmp;

	write(fd, "BM", 2);
	tmp = 14 + 40 + 4 * global->psing.value.rx * global->psing.value.ry;
	write(fd, &tmp, 4);
	tmp = 0;
	write(fd, &tmp, 2);
	write(fd, &tmp, 2);
	tmp = 54;
	write(fd, &tmp, 4);
	tmp = 40;
	write(fd, &tmp, 4);
	write(fd, &global->psing.value.rx, 4);
	write(fd, &global->psing.value.ry, 4);
	tmp = 1;
	write(fd, &tmp, 2);
	write(fd, &global->mlx.bpp, 2);
	tmp = 0;
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
}

int		fill_bmp(t_global *global)
{
	int	fd;
	int	x;
	int	y;

	y = global->psing.value.ry;
	if ((fd = open("./bitmap.bmp", O_CREAT | O_RDWR)) == -1)
		return (fprintf(stderr, "Error\nImpossible to create the file"));
	ft_header(global, fd);
	while (y >= 0)
	{
		x = 0;
		while (x < global->psing.value.rx)
		{
			write(fd, &global->mlx.addr[y * global->mlx.len_line / 4 + x],
				4);
			x++;
		}
		y--;
	}
	system("chmod 777 bitmap.bmp");
	return (0);
}
