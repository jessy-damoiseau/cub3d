/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_for_calcul2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 04:53:52 by user42            #+#    #+#             */
/*   Updated: 2021/05/04 23:53:11 by user42           ###   ########.fr       */
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

int		init_textures2(t_global *global)
{
	int trash;

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
	return (0);
}

int		init_textures(t_global *global)
{
	if (!(global->xpm[0].img = mlx_xpm_file_to_image(global->mlx.mlx,
			global->psing.parse.no, &global->xpm[0].w, &global->xpm[0].h)))
		return (fprintf(stderr, "Error\n texture N non valide\n"));
	if (!(global->xpm[1].img = mlx_xpm_file_to_image(global->mlx.mlx,
			global->psing.parse.so, &global->xpm[1].w, &global->xpm[1].h)))
		return (fprintf(stderr, "Error\n texture S non valide\n"));
	if (!(global->xpm[2].img = mlx_xpm_file_to_image(global->mlx.mlx,
			global->psing.parse.we, &global->xpm[2].w, &global->xpm[2].h)))
		return (fprintf(stderr, "Error\n texture W non valide\n"));
	if (!(global->xpm[3].img = mlx_xpm_file_to_image(global->mlx.mlx,
			global->psing.parse.ea, &global->xpm[3].w, &global->xpm[3].h)))
		return (fprintf(stderr, "Error\n texture E non valide\n"));
	if (!(global->xpm[4].img = mlx_xpm_file_to_image(global->mlx.mlx,
			global->psing.parse.s, &global->xpm[4].w, &global->xpm[4].h)))
		return (fprintf(stderr, "Error\n texture de sprite non valide\n"));
	return (init_textures2(global));
}
