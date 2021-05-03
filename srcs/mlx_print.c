/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 04:06:15 by user42            #+#    #+#             */
/*   Updated: 2021/05/03 17:01:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	first_part_sprite(t_global *global)
{
	int i;

	i = -1;
	while (++i < global->constante.nsprites)
	{
		global->csprite.spriteorder[i] = i;
		global->csprite.spritedistance[i] =
		((global->constante.posx - global->sprite[i].x)
		* (global->constante.posy - global->sprite[i].x) +
		(global->constante.posy - global->sprite[i].y)
		* (global->constante.posy - global->sprite[i].y));
	}
}

void	calcul_sprite(t_global *global, t_parsing *parsing, int i)
{
	global->csprite.spritex = global->sprite[global->csprite.spriteorder[i]].x
		- global->constante.posx;
	global->csprite.spritey = global->sprite[global->csprite.spriteorder[i]].y
		- global->constante.posy;
	global->csprite.invdet = 1.0 / (global->constante.planex
			* global->constante.diry
			- global->constante.dirx * global->constante.planey);
	global->csprite.transformx = global->csprite.invdet *
		(global->constante.diry * global->csprite.spritex -
		global->constante.dirx * global->csprite.spritey);
	global->csprite.transformy = global->csprite.invdet *
		(-global->constante.planey * global->csprite.spritex +
		global->constante.planex * global->csprite.spritey);
	global->csprite.spritescreenx = (int)((parsing->value.rx / 2) *
			(1 + global->csprite.transformx / global->csprite.transformy));
	global->csprite.vmovescreen = (int)(vMove / global->csprite.transformy);
	global->csprite.spriteheight = abs((int)(parsing->value.ry /
				(global->csprite.transformy))) / vDiv;
}

void	calcul_lensprite(t_global *global, t_parsing *parsing)
{
	global->csprite.drawstarty = -global->csprite.spriteheight
		/ 2 + parsing->value.ry / 2 + global->csprite.vmovescreen;
	if (global->csprite.drawstarty < 0)
		global->csprite.drawstarty = 0;
	global->csprite.drawendy = global->csprite.spriteheight
		/ 2 + parsing->value.ry / 2 + global->csprite.vmovescreen;
	if (global->csprite.drawendy >= parsing->value.ry)
		global->csprite.drawendy = parsing->value.ry - 1;
	global->csprite.spritewidth = abs((int)(parsing->value.ry
				/ (global->csprite.transformy))) / uDiv;
	global->csprite.drawstartx = -global->csprite.spritewidth
		/ 2 + global->csprite.spritescreenx;
	if (global->csprite.drawstartx < 0)
		global->csprite.drawstartx = 0;
	global->csprite.drawendx = global->csprite.spritewidth
		/ 2 + global->csprite.spritescreenx;
	if (global->csprite.drawendx >= parsing->value.rx)
		global->csprite.drawendx = parsing->value.rx - 1;
}

void	fill_addr(t_global *global, t_parsing *parsing)
{
	int x;
	int y;

	x = global->csprite.drawstartx - 1;
	while (++x < global->csprite.drawendx)
	{
		global->csprite.texx = (int)(256 * (x -
		(-global->csprite.spritewidth / 2 + global->csprite.spritescreenx))
		* global->xpm[4].w / global->csprite.spritewidth) / 256;
		if (global->csprite.transformy > 0 && x > 0 && x < parsing->value.rx
		&& global->csprite.transformy < global->csprite.zbuffer[x])
			y = global->csprite.drawstarty - 1;
		while (++y < global->csprite.drawendy)
		{
			global->csprite.d = (y - global->csprite.vmovescreen) * 256 -
			parsing->value.ry * 128 + global->csprite.spriteheight * 128;
			global->csprite.texy = ((global->csprite.d * global->xpm[4].h)
			/ global->csprite.spriteheight) / 256;
			if (global->xpm[4].addr[global->xpm[4].w *
			global->csprite.texy + global->csprite.texx])
				global->mlx.addr[y * parsing->value.rx + x] =
				global->xpm[4].addr[global->xpm[4].w *
				global->csprite.texy + global->csprite.texx];
		}
	}
}

void	print_sprite(t_global *global, t_parsing *parsing)
{
	int i;

	i = -1;
	first_part_sprite(global);
	sortsprites(global);
	while (++i < global->constante.nsprites)
	{
		calcul_sprite(global, parsing, i);
		calcul_lensprite(global, parsing);
		fill_addr(global, parsing);
	}
}
