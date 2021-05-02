/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <jessy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 03:29:55 by jessy             #+#    #+#             */
/*   Updated: 2021/05/02 03:31:24 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    print_col(t_global *global, t_parsing *parsing, int x)
{
	int y;

	y = 0;
	while (y < global->pixel.drawstart)
		global->mlx.addr[y++
			* parsing->value.rx + x] = get_color(parsing->value.sky[0],
					parsing->value.sky[1], parsing->value.sky[2]);
	while (y <= global->pixel.drawend)
	{
		if (parsing->parse.map[global->calcul.mapx][global->calcul.mapy] == '1')
		{
			global->textures.texy = (int)global->textures.texpos &
				(global->xpm[global->textures.texnum].h - 1);
			global->textures.texpos += global->textures.step;
			global->mlx.addr[y++ * parsing->value.rx + x] =
				global->xpm[global->textures.texnum].addr[global->xpm[global->textures.texnum].h
				* global->textures.texy + global->textures.texx];
		}
	}
	while (y < parsing->value.ry)
		global->mlx.addr[y++ * parsing->value.rx + x] = get_color(parsing->value.floor[0],
				parsing->value.floor[1], parsing->value.floor[2]);
}

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

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;

	for (int i = 0; i < amount; i++)
	{
		for (int j = 0; j < amount - 1; j++)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
		}
	}
}

void	sortSprites(int *order, double *dist, int amount)
{
	t_pair	*sprites;

	sprites = (t_pair*)malloc(sizeof(t_pair) * amount);
	for (int i = 0; i < amount; i++)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	sort_order(sprites, amount);
	for (int i = 0; i < amount; i++)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
	free(sprites);
}

void	take_raystepsidedist(t_global *global)
{
	if(global->calcul.raydirx < 0)
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
	if(global->calcul.raydiry < 0)
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

void	check_hit(t_global *global, t_parsing *parsing)
{
	while (global->calcul.hit == 0)
	{

		if(global->calcul.sidedistx < global->calcul.sidedisty)
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
		if(parsing->parse.map[global->calcul.mapx][global->calcul.mapy] == '1')
			global->calcul.hit = 1;
	}
}

void	calcul_perpandlentext(t_global *global, t_parsing *parsing)
{
	if (global->calcul.side == 0)
		global->calcul.perpwalldist = (global->calcul.mapx -
				global->constante.posx + (1 - global->calcul.stepx)
				/ 2) / global->calcul.raydirx;
	else
		global->calcul.perpwalldist = (global->calcul.mapy -
				global->constante.posy + (1 - global->calcul.stepy)
				/ 2) / global->calcul.raydiry;
	global->pixel.lineheight = (int)(parsing->value.ry
			/ global->calcul.perpwalldist);
	global->pixel.drawstart = -global->pixel.lineheight
		/ 2 + parsing->value.ry / 2;
	if(global->pixel.drawstart < 0)
		global->pixel.drawstart = 0;
	global->pixel.drawend = global->pixel.lineheight
		/ 2 + parsing->value.ry / 2;
	if(global->pixel.drawend >= parsing->value.ry)
		global->pixel.drawend = parsing->value.ry - 1;
}

void	calculfortex(t_global *global, t_parsing *parsing)
{
	if(global->calcul.side == 0)
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
	global->textures.texpos = (global->pixel.drawstart - parsing->value.ry /
			2 + global->pixel.lineheight / 2) * global->textures.step;
}

void	first_part_sprite(t_global *global)
{
	int i;

	i = -1;
	while (++i < global->constante.nsprites)
	{
		global->csprite.spriteorder[i] = i;
		global->csprite.spritedistance[i] = ((global->constante.posx
					- global->sprite[i].x) * (global->constante.posy - global->sprite[i].x) +
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
	if(global->csprite.drawstarty < 0)
		global->csprite.drawstarty = 0;
	global->csprite.drawendy = global->csprite.spriteheight
		/ 2 + parsing->value.ry / 2 + global->csprite.vmovescreen;
	if(global->csprite.drawendy >= parsing->value.ry)
		global->csprite.drawendy = parsing->value.ry - 1;
	global->csprite.spritewidth = abs( (int) (parsing->value.ry
				/ (global->csprite.transformy))) / uDiv;
	global->csprite.drawstartx = -global->csprite.spritewidth
		/ 2 + global->csprite.spritescreenx;
	if(global->csprite.drawstartx < 0)
		global->csprite.drawstartx = 0;
	global->csprite.drawendx = global->csprite.spritewidth
		/ 2 + global->csprite.spritescreenx;
	if(global->csprite.drawendx >= parsing->value.rx)
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
		if(global->csprite.transformy > 0 && x > 0 && x < parsing->value.rx
				&& global->csprite.transformy < global->csprite.zbuffer[x])
			y = global->csprite.drawstarty -1;
		while (++y < global->csprite.drawendy)
		{
			global->csprite.d = (y - global->csprite.vmovescreen) * 256 -
				parsing->value.ry * 128 + global->csprite.spriteheight * 128;
			global->csprite.texy = ((global->csprite.d * global->xpm[4].h)
					/ global->csprite.spriteheight) / 256;
			if (global->xpm[4].addr[global->xpm[4].w * global->csprite.texy + global->csprite.texx])
				global->mlx.addr[y * parsing->value.rx + x] = global->xpm[4].addr[global->xpm[4].w
					* global->csprite.texy + global->csprite.texx]; 
		}
	}
}

void	print_sprite(t_global *global, t_parsing *parsing)
{
	int i;

	i = -1;
	first_part_sprite(global);
	sortSprites(global->csprite.spriteorder,
			global->csprite.spritedistance, global->constante.nsprites);
	while (++i < global->constante.nsprites)
	{
		calcul_sprite(global, parsing, i);
		calcul_lensprite(global, parsing);
		fill_addr(global, parsing);
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

void	free_sprite(t_global *global)
{
	free(global->csprite.zbuffer);
	free(global->csprite.spritedistance);
	free(global->csprite.spriteorder);
}

void	check_move4(t_global *global)
{
	int olddirx;
	int	oldplanex;

	if(global->mlx.tab[59])
	{
		olddirx = global->constante.dirx;
		global->constante.dirx = global->constante.dirx *
			cos(ROTSPEED) - global->constante.diry * sin(ROTSPEED);
		global->constante.diry = olddirx * sin(ROTSPEED)
			+ global->constante.diry * cos(ROTSPEED);
		oldplanex = global->constante.planex;
		global->constante.planex = global->constante.planex
			* cos(ROTSPEED) - global->constante.planey * sin(ROTSPEED);
		global->constante.planey = oldplanex * sin(ROTSPEED)
			+ global->constante.planey * cos(ROTSPEED);
	}
}

void	check_move3(t_global *global)
{
	int olddirx;
	int	oldplanex;

	if(global->mlx.tab[39])
	{
		olddirx = global->constante.dirx;
		global->constante.dirx = global->constante.dirx *
			cos(-ROTSPEED) - global->constante.diry * sin(-ROTSPEED);
		global->constante.diry = olddirx * sin(-ROTSPEED)
			+ global->constante.diry * cos(-ROTSPEED);
		oldplanex = global->constante.planex;
		global->constante.planex = global->constante.planex
			* cos(-ROTSPEED) - global->constante.planey * sin(-ROTSPEED);
		global->constante.planey = oldplanex * sin(-ROTSPEED)
			+ global->constante.planey * cos(-ROTSPEED);
	}
	check_move4(global);
}

void	check_move2(t_global *global, t_parsing *parsing)
{
	if (global->mlx.tab[97])
	{
		if (parsing->parse.map[(int)(global->constante.posx)][(int)((global->constante.posy
						+ global->constante.dirx * MOVESPEED) + (0.1 * global->constante.dirx))] == '0')
			global->constante.posy += global->constante.dirx * MOVESPEED;
		if (parsing->parse.map[(int)((global->constante.posx - global->constante.diry
						* MOVESPEED) - (0.1 * global->constante.diry))][(int)global->constante.posy] == '0')
			global->constante.posx -= global->constante.diry * MOVESPEED;
	}
	if (global->mlx.tab[100])
	{
		if (parsing->parse.map[(int)(global->constante.posx)][(int)((global->constante.posy
						- global->constante.dirx * MOVESPEED) - (0.02 * global->constante.dirx))] == '0')
			global->constante.posy -= global->constante.dirx * MOVESPEED;
		if (parsing->parse.map[(int)((global->constante.posx + global->constante.diry
						* MOVESPEED) + (0.02 * global->constante.diry))][(int)global->constante.posy] == '0')
			global->constante.posx += global->constante.diry * MOVESPEED;
	}
	check_move3(global);
}

void	check_move(t_global *global, t_parsing *parsing)
{
	if(global->mlx.tab[119])
	{
		if(parsing->parse.map[(int)((global->constante.posx + global->constante.dirx
						* MOVESPEED) + (0.01 * global->constante.dirx))][(int)(global->constante.posy)] == '0')
			global->constante.posx += global->constante.dirx * MOVESPEED;
		if(parsing->parse.map[(int)(global->constante.posx)][(int)((global->constante.posy
						+ global->constante.diry * MOVESPEED) + (0.01 * global->constante.diry))] == '0')
			global->constante.posy += global->constante.diry * MOVESPEED;
	}
	if(global->mlx.tab[115])
	{
		if(parsing->parse.map[(int)((global->constante.posx
						- global->constante.dirx
						* MOVESPEED) + (0.01 * global->constante.dirx))]
				[(int)(global->constante.posy)] == '0')
			global->constante.posx -= global->constante.dirx
					* MOVESPEED;
		if(parsing->parse.map[(int)(global->constante.posx)][(int)((global->constante.posy
						- global->constante.diry * MOVESPEED) + (0.01 * global->constante.diry))] == '0')
			global->constante.posy -= global->constante.diry * MOVESPEED;
	}
	check_move2(global, parsing);
}

int		my_mlx_loop2(t_global *global)
{
	print_sprite(global, &global->parsing);
	free_sprite(global);
	print_minimap(global);
	mlx_put_image_to_window(global->mlx.mlx,
			global->mlx.win, global->mlx.img, 0, 0);
	check_move(global, &global->parsing);
	return (1);
}

int 	my_mlx_loop(t_global *global)
{
	int x;

	x = -1;
	global->csprite = (t_csprite){0};
	if (global->mlx.tab[307])
		close_mlx(global);
	if (malloc_sprite(global, &global->parsing))
		return (1);
	while (++x < global->parsing.value.rx)
	{
		init_calcul(global, x);
		take_raystepsidedist(global);
		check_hit(global, &global->parsing);
		calcul_perpandlentext(global, &global->parsing);		
		get_texnum(global);
		calculfortex(global, &global->parsing);
		print_col(global, &global->parsing, x);
		global->csprite.zbuffer[x] = global->calcul.perpwalldist;
	}
	return (my_mlx_loop2(global));
}
