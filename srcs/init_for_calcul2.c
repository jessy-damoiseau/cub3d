/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_for_calcul2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 04:53:52 by user42            #+#    #+#             */
/*   Updated: 2021/05/04 15:50:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_dir2(t_global *global, char c)
{
	if (c == 'W')
	{
		global->constante.dirx = 0;
		global->constante.diry = -1;
		global->constante.planex = -0.9;
		global->constante.planey = 0;
	}
	if (c == 'E')
	{
		global->constante.dirx = 0;
		global->constante.diry = 1;
		global->constante.planex = 0.9;
		global->constante.planey = 0;
	}
}

void	get_dir(t_global *global)
{
	char c;

	c = global->psing.parse.map[(int)global->constante.posx]
		[(int)global->constante.posy];
	if (c == 'N')
	{
		global->constante.dirx = -1;
		global->constante.diry = 0;
		global->constante.planex = 0;
		global->constante.planey = 0.9;
	}
	if (c == 'S')
	{
		global->constante.dirx = 1;
		global->constante.diry = 0;
		global->constante.planex = 0;
		global->constante.planey = -0.9;
	}
	get_dir2(global, c);
}
