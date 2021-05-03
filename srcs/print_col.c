/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_col.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:43:14 by user42            #+#    #+#             */
/*   Updated: 2021/05/03 16:56:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_col(t_global *global, t_parsing *parsing, int x)
{
	int y;

	y = 0;
	while (y < global->pixel.drawstart)
		global->mlx.addr[y++
		* parsing->value.rx + x] = get_color(parsing->value.sky[0],
		parsing->value.sky[1], parsing->value.sky[2]);
	while (y <= global->pixel.drawend)
	{
		if (parsing->parse.map[global->calcul.mapx][global->calcul.mapy] == '1')
		{
			global->textures.texy = (int)global->textures.texpos &
				(global->xpm[global->textures.texnum].h - 1);
			global->textures.texpos += global->textures.step;
			global->mlx.addr[y++ * parsing->value.rx + x] =
				global->xpm[global->textures.texnum].addr
				[global->xpm[global->textures.texnum].h * global->textures.texy
				+ global->textures.texx];
		}
	}
	while (y < parsing->value.ry)
		global->mlx.addr[y++ *
		parsing->value.rx + x] = get_color(parsing->value.floor[0],
		parsing->value.floor[1], parsing->value.floor[2]);
}
