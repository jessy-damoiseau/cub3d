/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_for_calcul.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 04:51:37 by user42            #+#    #+#             */
/*   Updated: 2021/05/03 17:22:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_textures(t_global *global)
{
	int trash;

	global->xpm[0].img = mlx_xpm_file_to_image(global->mlx.mlx,
			global->parsing.parse.no, &global->xpm[0].w, &global->xpm[0].h);
	global->xpm[1].img = mlx_xpm_file_to_image(global->mlx.mlx,
			global->parsing.parse.so, &global->xpm[1].w, &global->xpm[1].h);
	global->xpm[2].img = mlx_xpm_file_to_image(global->mlx.mlx,
			global->parsing.parse.we, &global->xpm[2].w, &global->xpm[2].h);
	global->xpm[3].img = mlx_xpm_file_to_image(global->mlx.mlx,
			global->parsing.parse.ea, &global->xpm[3].w, &global->xpm[3].h);
	global->xpm[4].img = mlx_xpm_file_to_image(global->mlx.mlx,
			global->parsing.parse.s, &global->xpm[4].w, &global->xpm[4].h);
	global->xpm[0].addr = (int*)mlx_get_data_addr(global->xpm[0].img,
			&trash, &trash, &trash);
	global->xpm[1].addr = (int*)mlx_get_data_addr(global->xpm[1].img,
			&trash, &trash, &trash);
	global->xpm[2].addr = (int*)mlx_get_data_addr(global->xpm[2].img,
			&trash, &trash, &trash);
	global->xpm[3].addr = (int*)mlx_get_data_addr(global->xpm[3].img,
			&trash, &trash, &trash);
	global->xpm[4].addr = (int*)mlx_get_data_addr(global->xpm[4].img,
			&trash, &trash, &trash);
}

void	init_mlx(t_global *global)
{
	int i;

	i = 0;
	init_textures(global);
	value_windows_size(global);
	while (i < 512)
		global->mlx.tab[i++] = 0;
}

void	init_strut_next(t_global *global)
{
	global->textures.texpos = 0;
	global->textures.step = 0;
	global->textures.texx = 0;
	global->textures.texy = 0;
	global->textures.wallx = 0;
	global->parsing.value.save = 0;
}

void	init_struct(t_global *global)
{
	global->calcul.camerax = 0;
	global->calcul.raydirx = 0;
	global->calcul.raydiry = 0;
	global->calcul.mapx = 0;
	global->calcul.mapy = 0;
	global->calcul.sidedistx = 0;
	global->calcul.sidedisty = 0;
	global->calcul.deltadistx = 0;
	global->calcul.deltadisty = 0;
	global->calcul.perpwalldist = 0;
	global->calcul.stepx = 0;
	global->calcul.stepx = 0;
	global->calcul.hit = 0;
	global->calcul.side = 0;
	global->constante.posx = 0;
	global->constante.posy = 0;
	global->constante.dirx = 0;
	global->constante.diry = 0;
	global->constante.planex = 0;
	global->constante.planey = 0;
	global->constante.nsprites = 0;
	global->pixel.lineheight = 0;
	global->pixel.drawstart = 0;
	global->pixel.drawend = 0;
	init_strut_next(global);
}

void	init_constante(t_global *global)
{
	global->constante.posx = get_spawn(global->parsing.parse.map, 0) + 0.5;
	global->constante.posy = get_spawn(global->parsing.parse.map, 1) + 0.5;
	get_dir(global);
	global->parsing.parse.map[(int)global->constante.posx]
		[(int)global->constante.posy] = '0';
}
