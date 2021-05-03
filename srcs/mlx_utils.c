/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 04:14:22 by user42            #+#    #+#             */
/*   Updated: 2021/05/02 04:14:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		close_mlx(t_global *global)
{
	clear_parse(&global->parsing.parse);
	mlx_destroy_image(global->mlx.mlx, global->mlx.img);
	mlx_destroy_image(global->mlx.mlx, global->xpm[0].img);
	mlx_destroy_image(global->mlx.mlx, global->xpm[1].img);
	mlx_destroy_image(global->mlx.mlx, global->xpm[2].img);
	mlx_destroy_image(global->mlx.mlx, global->xpm[3].img);
	mlx_destroy_image(global->mlx.mlx, global->xpm[4].img);
	mlx_destroy_window(global->mlx.mlx, global->mlx.win);
	mlx_destroy_display(global->mlx.mlx);
	free(global->sprite);
	free(global->mlx.mlx);
	exit(0);
}

int		get_color(int r, int g, int b)
{
	return (256 * 256 * r + 256 * g + b);
}

int		keypress(int keycode, t_mlx *mlx)
{
	if (keycode % 1000 < 512)
		mlx->tab[keycode % 1000] = 1;
	return (0);
}

int		keyrelease(int keycode, t_mlx *mlx)
{
	if (keycode % 1000 < 512)
		mlx->tab[keycode % 1000] = 0;
	return (0);
}

void	free_sprite(t_global *global)
{
	free(global->csprite.zbuffer);
	free(global->csprite.spritedistance);
	free(global->csprite.spriteorder);
}
