/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 04:10:34 by user42            #+#    #+#             */
/*   Updated: 2021/05/03 17:08:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_calcul(t_global *global, int x)
{
	global->calcul.camerax = 2 * x /
		(double)global->parsing.value.rx - 1;
	global->calcul.raydirx = global->constante.dirx +
		global->constante.planex * global->calcul.camerax;
	global->calcul.raydiry = global->constante.diry +
		global->constante.planey * global->calcul.camerax;
	global->calcul.mapx = (int)global->constante.posx;
	global->calcul.mapy = (int)global->constante.posy;
	global->calcul.deltadistx = fabs(1 / global->calcul.raydirx);
	global->calcul.deltadisty = fabs(1 / global->calcul.raydiry);
	global->calcul.hit = 0;
}

void	get_texnum(t_global *global)
{
	if (!global->calcul.side && global->calcul.stepx == -1)
		global->textures.texnum = 0;
	if (!global->calcul.side && global->calcul.stepx == 1)
		global->textures.texnum = 1;
	if (global->calcul.side && global->calcul.stepy == -1)
		global->textures.texnum = 2;
	if (global->calcul.side && global->calcul.stepy == 1)
		global->textures.texnum = 3;
}

void	sprites_dist(t_global *global)
{
	int	i;

	i = -1;
	while (++i < global->constante.nsprites)
	{
		global->csprite.spriteorder[i] = i;
		global->csprite.spritedistance[i] =
			sqrt(pow((global->constante.posx - global->sprite[i].x), 2)
					+ pow((global->constante.posy - global->sprite[i].y), 2));
	}
}

void	sortsprites(t_global *global)
{
	int		i;
	int		j;
	double	tmp;

	sprites_dist(global);
	i = -1;
	while (++i < global->constante.nsprites)
	{
		j = -1;
		while (++j < global->constante.nsprites - 1)
		{
			if (global->csprite.spritedistance[j]
					< global->csprite.spritedistance[j + 1])
			{
				tmp = global->csprite.spritedistance[j];
				global->csprite.spritedistance[j] =
					global->csprite.spritedistance[j + 1];
				global->csprite.spritedistance[j + 1] = tmp;
				tmp = (double)global->csprite.spriteorder[j];
				global->csprite.spriteorder[j] =
					global->csprite.spriteorder[j + 1];
				global->csprite.spriteorder[j + 1] = (int)tmp;
			}
		}
	}
}

int		malloc_sprite(t_global *global, t_parsing *parsing)
{
	if (!(global->csprite.zbuffer = malloc(sizeof(double)
					* parsing->value.rx)))
		return (1);
	if (!(global->csprite.spriteorder = malloc(sizeof(int)
					* global->constante.nsprites)))
		return (1);
	if (!(global->csprite.spritedistance = malloc(sizeof(double)
					* global->constante.nsprites)))
		return (1);
	return (0);
}
