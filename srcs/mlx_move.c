/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 04:09:34 by user42            #+#    #+#             */
/*   Updated: 2021/05/03 16:52:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_move4(t_global *global)
{
	double	oldplanex;
	double	olddirx;

	if (global->mlx.tab[KEY_LEFTROT])
	{
		olddirx = global->constante.dirx;
		global->constante.dirx = global->constante.dirx
		* cos(ROTSPEED) - global->constante.diry * sin(ROTSPEED);
		global->constante.diry = olddirx * sin(ROTSPEED) +
		global->constante.diry * cos(ROTSPEED);
		oldplanex = global->constante.planex;
		global->constante.planex = global->constante.planex *
		cos(ROTSPEED) - global->constante.planey * sin(ROTSPEED);
		global->constante.planey = oldplanex * sin(ROTSPEED)
		+ global->constante.planey * cos(ROTSPEED);
	}
}

void	check_move3(t_global *global)
{
	double	oldplanex;
	double	olddirx;

	if (global->mlx.tab[KEY_RIGTHROT])
	{
		olddirx = global->constante.dirx;
		global->constante.dirx = global->constante.dirx
		* cos(-ROTSPEED) - global->constante.diry * sin(-ROTSPEED);
		global->constante.diry = olddirx * sin(-ROTSPEED) +
		global->constante.diry * cos(-ROTSPEED);
		oldplanex = global->constante.planex;
		global->constante.planex = global->constante.planex *
		cos(-ROTSPEED) - global->constante.planey * sin(-ROTSPEED);
		global->constante.planey = oldplanex * sin(-ROTSPEED)
		+ global->constante.planey * cos(-ROTSPEED);
	}
	check_move4(global);
}

void	check_move2(t_global *global, t_parsing *parsing)
{
	if (global->mlx.tab[KEY_A])
	{
		if (parsing->parse.map[(int)(global->constante.posx)]
		[(int)((global->constante.posy + global->constante.dirx
		* MOVESPEED) + (0.1 * global->constante.dirx))] == '0')
			global->constante.posy += global->constante.dirx * MOVESPEED;
		if (parsing->parse.map[(int)((global->constante.posx -
		global->constante.diry * MOVESPEED) - (0.1 * global->constante.diry))]
		[(int)global->constante.posy] == '0')
			global->constante.posx -= global->constante.diry * MOVESPEED;
	}
	if (global->mlx.tab[KEY_D])
	{
		if (parsing->parse.map[(int)(global->constante.posx)]
		[(int)((global->constante.posy - global->constante.dirx
		* MOVESPEED) - (0.02 * global->constante.dirx))] == '0')
			global->constante.posy -= global->constante.dirx * MOVESPEED;
		if (parsing->parse.map[(int)((global->constante.posx +
		global->constante.diry * MOVESPEED) + (0.02 * global->constante.diry))]
		[(int)global->constante.posy] == '0')
			global->constante.posx += global->constante.diry * MOVESPEED;
	}
	check_move3(global);
}

void	check_move(t_global *global, t_parsing *parsing)
{
	if (global->mlx.tab[KEY_W])
	{
		if (parsing->parse.map[(int)((global->constante.posx +
		global->constante.dirx * MOVESPEED) + (0.01 * global->constante.dirx))]
		[(int)(global->constante.posy)] == '0')
			global->constante.posx += global->constante.dirx * MOVESPEED;
		if (parsing->parse.map[(int)(global->constante.posx)]
		[(int)((global->constante.posy + global->constante.diry
		* MOVESPEED) + (0.01 * global->constante.diry))] == '0')
			global->constante.posy += global->constante.diry * MOVESPEED;
	}
	if (global->mlx.tab[KEY_S])
	{
		if (parsing->parse.map[(int)((global->constante.posx -
		global->constante.dirx * MOVESPEED) + (0.01 * global->constante.dirx))]
		[(int)(global->constante.posy)] == '0')
			global->constante.posx -= global->constante.dirx * MOVESPEED;
		if (parsing->parse.map[(int)(global->constante.posx)]
		[(int)((global->constante.posy - global->constante.diry
		* MOVESPEED) + (0.01 * global->constante.diry))] == '0')
			global->constante.posy -= global->constante.diry * MOVESPEED;
	}
	check_move2(global, parsing);
}

void	take_raystepsidedist(t_global *global)
{
	if (global->calcul.raydirx < 0)
	{
		global->calcul.stepx = -1;
		global->calcul.sidedistx = (global->constante.posx
				- global->calcul.mapx) * global->calcul.deltadistx;
	}
	else
	{
		global->calcul.stepx = 1;
		global->calcul.sidedistx = (global->calcul.mapx + 1.0
				- global->constante.posx) * global->calcul.deltadistx;
	}
	if (global->calcul.raydiry < 0)
	{
		global->calcul.stepy = -1;
		global->calcul.sidedisty = (global->constante.posy
				- global->calcul.mapy) * global->calcul.deltadisty;
	}
	else
	{
		global->calcul.stepy = 1;
		global->calcul.sidedisty = (global->calcul.mapy + 1.0
				- global->constante.posy) * global->calcul.deltadisty;
	}
}
