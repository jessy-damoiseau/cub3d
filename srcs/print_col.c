/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_col.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:43:14 by user42            #+#    #+#             */
/*   Updated: 2021/05/04 23:50:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_col(t_global *global, t_psing *psing, int x)
{
	int y;

	y = 0;
	while (y < global->pixel.drawstart)
		global->mlx.addr[y++
		* psing->value.rx + x] = get_color(psing->value.sky[0],
		psing->value.sky[1], psing->value.sky[2]);
	while (y <= global->pixel.drawend)
	{
		if (psing->parse.map[global->calcul.mapx][global->calcul.mapy] == '1')
		{
			global->textures.texy = (int)global->textures.texpos &
				(global->xpm[global->textures.texnum].h - 1);
			global->textures.texpos += global->textures.step;
			global->mlx.addr[y++ * psing->value.rx + x] =
				global->xpm[global->textures.texnum].addr
				[global->xpm[global->textures.texnum].h * global->textures.texy
				+ global->textures.texx];
		}
	}
	while (y < psing->value.ry)
		global->mlx.addr[y++ *
		psing->value.rx + x] = get_color(psing->value.floor[0],
		psing->value.floor[1], psing->value.floor[2]);
}
