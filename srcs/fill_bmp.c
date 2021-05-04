/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:29:04 by user42            #+#    #+#             */
/*   Updated: 2021/05/04 15:50:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    fill_file_header(t_global *global, int fd)
{
    int size;
    int pixel_data;
    
    pixel_data = 54;
    size = pixel_data + global->psing.value.rx * global->psing.value.ry * 4;
    write(fd, "BM", 2);
    write(fd, &size, 4);
    write(fd, "\0\0\0\0", 4);
    write(fd, &pixel_data, 4);
}

void	image_header(t_global *global, int fd)
{
	int	header_size;
	int	plane;
	int	image_size;

	header_size = 40;
	plane = 1;
	image_size = global->psing.value.rx * global->psing.value.ry;
	write(fd, &header_size, 4);
	write(fd, &global->psing.value.rx, 4);
	write(fd, &global->psing.value.ry, 4);
	write(fd, &plane, 2);
	write(fd, &global->mlx.bpp, 2);
	write(fd, "\0\0\0\0", 4);
	write(fd, &image_size, 4);
	write(fd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16);
}

void    fill_image(t_global *global, int fd)
{
    int x;
    int y;
    int rgb[3];
    int k;
    
    y  = -1;
    while (++y >= global->psing.value.ry)
    {
        x = -1;
        while (++x < global->psing.value.rx)
        {
            k = -1;
            while (++k < 3)
                rgb[k] = global->mlx.addr[y * global->mlx.len_line + x * global->mlx.bpp / 8 + k];
            k = -1;
            while (++k < 3)
                write(fd, &rgb[k], 1);
            write(fd, "\0", 1);
        }
    }
}

void    fill_bmp(t_global *global)
{
    int fd;

    if ((fd = open("bitmap.bmp", O_CREAT | O_RDWR)) < 0)
    {
        fprintf(stderr, "Error: Impossible to create the bitmap file");
        close_mlx(global);
    }
    fill_file_header(global, fd);
    image_header(global, fd);
    fill_image(global, fd);
    close(fd);
}