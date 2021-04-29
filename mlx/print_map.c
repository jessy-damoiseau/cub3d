/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:43:14 by user42            #+#    #+#             */
/*   Updated: 2021/04/29 14:34:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_minimap(t_global *global)
{
	int loop;
	int leep;
	int x;
	int y;
	int x_pixel;
	int y_pixel;
	y = -1;
	y_pixel = 0;
	while (global->parsing.parse.map[++y])
	{
		x = -1;
		x_pixel = 0;
		while (global->parsing.parse.map[y][++x])
		{
			loop = -4;
			while (loop <=4)
			{
				leep = -4;
				while (leep <= 4)
				{
					if (global->parsing.parse.map[y][x] == '1') 
						global->mlx.addr[(y_pixel + 4 + loop) * global->parsing.value.rx + (x_pixel + 4)+ leep] = get_color(100, 100, 100);
					else if (global->parsing.parse.map[y][x] == '0' || global->parsing.parse.map[y][x] == '2' || global->parsing.parse.map[y][x] == 'W'
							|| global->parsing.parse.map[y][x] == 'N'|| global->parsing.parse.map[y][x] == 'S'|| global->parsing.parse.map[y][x] == 'E')
						global->mlx.addr[(y_pixel + 4 + loop) * global->parsing.value.rx + (x_pixel + 4) + leep] = get_color(200, 200, 200);
					leep++;
				}
				loop++;
			}
			x_pixel += 9;
		}
		y_pixel += 9;
	}
	global->mlx.addr[(int)(global->constante.posx * 9) * global->parsing.value.rx  + (int)(global->constante.posy * 9 )] = get_color(255, 0, 0);
}
