/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 04:48:02 by user42            #+#    #+#             */
/*   Updated: 2021/05/05 02:19:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int		get_spawn(char **map, int i)
{
	int x;
	int y;
	int done;

	x = 0;
	done = 0;
	while (map[x] && !done)
	{
		y = 0;
		while (map[x][y] && !done)
		{
			if (map[x][y] == 'N' || map[x][y] == 'S'
					|| map[x][y] == 'W' || map[x][y] == 'E')
				done = 1;
			if (!done)
				y++;
		}
		if (!done)
			x++;
	}
	if (i)
		return (y);
	return (x);
}

void	check_sprite2(t_global *global)
{
	int i;
	int j;
	int k;

	k = 0;
	while (k < global->constante.nsprites)
	{
		i = -1;
		while (global->psing.parse.map[++i])
		{
			j = -1;
			while (global->psing.parse.map[i][++j])
				if (global->psing.parse.map[i][j] == '2')
				{
					global->sprite[k].x = i + 0.5;
					global->sprite[k++].y = j + 0.5;
				}
		}
	}
}

void	check_sprite(t_global *global)
{
	int i;
	int j;

	i = -1;
	while (global->psing.parse.map[++i])
	{
		j = -1;
		while (global->psing.parse.map[i][++j])
			if (global->psing.parse.map[i][j] == '2')
				global->constante.nsprites++;
	}
	if (!(global->sprite = malloc(sizeof(t_sprite)
					* global->constante.nsprites)))
		return ;
	check_sprite2(global);
}

int		main(int ac, char **av)
{
	t_global	global;

	init_struct(&global);
	if (parse(ac, av, &global, &global.psing))
		return (clear_parse(&global.psing.parse));
	init_constante(&global);
	global.mlx.mlx = mlx_init();
	if (init_mlx(&global))
		return (1);
	global.mlx.img = mlx_new_image(global.mlx.mlx, global.psing.value.rx,
			global.psing.value.ry);
	global.mlx.addr = (int*)mlx_get_data_addr(global.mlx.img, &global.mlx.bpp,
			&global.mlx.len_line, &global.mlx.endian);
	check_sprite(&global);
	if (global.psing.value.save)
		my_mlx_loop(&global);
	global.mlx.win = mlx_new_window(global.mlx.mlx,
		global.psing.value.rx, global.psing.value.ry, "cub3D");
	mlx_hook(global.mlx.win, 2, 1L << 0, keypress, &global.mlx);
	mlx_hook(global.mlx.win, 3, 1L << 1, keyrelease, &global.mlx);
	mlx_hook(global.mlx.win, 33, 1L << 17, close_mlx, &global);
	mlx_loop_hook(global.mlx.mlx, my_mlx_loop, &global);
	mlx_loop(global.mlx.mlx);
}
