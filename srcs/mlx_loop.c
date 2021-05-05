/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 03:29:55 by jessy             #+#    #+#             */
/*   Updated: 2021/05/05 02:17:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_hit(t_global *global, t_psing *psing)
{
	while (global->calcul.hit == 0)
	{
		if (global->calcul.sidedistx < global->calcul.sidedisty)
		{
			global->calcul.sidedistx += global->calcul.deltadistx;
			global->calcul.mapx += global->calcul.stepx;
			global->calcul.side = 0;
		}
		else
		{
			global->calcul.sidedisty += global->calcul.deltadisty;
			global->calcul.mapy += global->calcul.stepy;
			global->calcul.side = 1;
		}
		if (psing->parse.map[global->calcul.mapx][global->calcul.mapy] == '1')
			global->calcul.hit = 1;
	}
}

void	calcul_perpandlentext(t_global *global, t_psing *psing)
{
	if (global->calcul.side == 0)
		global->calcul.perpwalldist = (global->calcul.mapx -
				global->constante.posx + (1 - global->calcul.stepx)
				/ 2) / global->calcul.raydirx;
	else
		global->calcul.perpwalldist = (global->calcul.mapy -
				global->constante.posy + (1 - global->calcul.stepy)
				/ 2) / global->calcul.raydiry;
	global->pixel.lineheight = (int)(psing->value.ry
			/ global->calcul.perpwalldist);
	global->pixel.drawstart = -global->pixel.lineheight
		/ 2 + psing->value.ry / 2;
	if (global->pixel.drawstart < 0)
		global->pixel.drawstart = 0;
	global->pixel.drawend = global->pixel.lineheight
		/ 2 + psing->value.ry / 2;
	if (global->pixel.drawend >= psing->value.ry)
		global->pixel.drawend = psing->value.ry - 1;
}

void	calculfortex(t_global *global, t_psing *psing)
{
	if (global->calcul.side == 0)
		global->textures.wallx = global->constante.posy
			+ global->calcul.perpwalldist * global->calcul.raydiry;
	else
		global->textures.wallx = global->constante.posx
			+ global->calcul.perpwalldist * global->calcul.raydirx;
	global->textures.wallx -= floor((global->textures.wallx));
	global->textures.texx = (int)(global->textures.wallx *
			(double)global->xpm[global->textures.texnum].w);
	if (global->calcul.side == 0 && global->calcul.raydirx > 0)
		global->textures.texx = global->xpm[global->textures.texnum].w
			- global->textures.texx - 1;
	if (global->calcul.side == 1 && global->calcul.raydiry < 0)
		global->textures.texx = global->xpm[global->textures.texnum].w
			- global->textures.texx - 1;
	global->textures.step = 1.0 * global->xpm[global->textures.texnum].h /
		global->pixel.lineheight;
	global->textures.texpos = (global->pixel.drawstart - psing->value.ry /
			2 + global->pixel.lineheight / 2) * global->textures.step;
}

int		my_mlx_loop2(t_global *global)
{
	print_sprite(global, &global->psing);
	free_sprite(global);
	if (global->psing.value.save)
	{
		fill_bmp(global);
		close_mlx(global);
	}
	mlx_put_image_to_window(global->mlx.mlx,
			global->mlx.win, global->mlx.img, 0, 0);
	check_move(global, &global->psing);
	return (0);
}

int		my_mlx_loop(t_global *global)
{
	int x;

	x = -1;
	global->csprite = (t_csprite){0};
	if (global->mlx.tab[307])
		close_mlx(global);
	if (malloc_sprite(global, &global->psing))
		return (1);
	while (++x < global->psing.value.rx)
	{
		init_calcul(global, x);
		take_raystepsidedist(global);
		check_hit(global, &global->psing);
		calcul_perpandlentext(global, &global->psing);
		get_texnum(global);
		calculfortex(global, &global->psing);
		print_col(global, &global->psing, x);
		global->csprite.zbuffer[x] = global->calcul.perpwalldist;
	}
	return (my_mlx_loop2(global));
}
