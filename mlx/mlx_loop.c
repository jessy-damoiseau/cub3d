#include "../includes/cub3d.h"

void    print_col(t_global *global, t_parsing *parsing, int x)
{
    int y;

    y = 0;
    while (y < global->pixel.drawstart)
        global->mlx.addr[y++ * parsing->value.rx + x] = get_color(parsing->value.sky[0],
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

void	init_csprite(t_csprite *csprite)
{
	csprite->step = 0;
	csprite->texpos = 0;
	csprite->texx = 0;
	csprite->texy = 0;
	csprite->wallx = 0;
}

void        print_sprite(t_global *global, int y, int x, t_sprite *tmp)
{
    while (global->sprite)
    {
		init_csprite(&global->csprite);
        if (global->sprite->side == 0)
            global->csprite.wallx = global->constante.posy + global->sprite->spritedist * global->calcul.raydiry;
        else
            global->csprite.wallx = global->constante.posx + global->sprite->spritedist * global->calcul.raydirx;
        global->csprite.wallx -= floor(global->csprite.wallx);
        global->csprite.texx = (int)(global->csprite.wallx * (double)global->xpm[4].w);
        if (global->sprite->side == 0 && global->calcul.raydirx > 0)
            global->csprite.texx = global->xpm[4].w - global->csprite.texx - 1;
        if (global->sprite->side == 1 && global->calcul.raydiry < 0)
            global->csprite.texx = global->xpm[4].w - global->csprite.texx - 1;
        global->csprite.step = 1.0 * global->xpm[4].h / global->sprite->lineheight;
        global->csprite.texpos = (global->sprite->draws_start - global->parsing.value.ry / 2 + global->sprite->lineheight / 2) * global->csprite.step;
        y = global->sprite->draws_start;
        while (y <= global->sprite->draws_end)
        {
            global->csprite.texy = (int)global->csprite.texpos & (global->xpm[4].h - 1);
            global->csprite.texpos += global->csprite.step;
            if (global->xpm[4].addr[global->xpm[4].h * global->csprite.texy + global->csprite.texx])
                global->mlx.addr[y * global->parsing.value.rx + x] = global->xpm[4].addr[global->xpm[4].h * global->csprite.texy + global->csprite.texx];
            y++;
        }
        global->sprite = global->sprite->next;
    }
    global->sprite = tmp;
}
void	init_calcul(t_global *global, int x)
{
	global->calcul.camerax = 2 * x / (double)global->parsing.value.rx - 1; 
	global->calcul.raydirx = global->constante.dirx +
	global->constante.planex * global->calcul.camerax;
	global->calcul.raydiry = global->constante.diry +
	global->constante.planey * global->calcul.camerax;
	global->calcul.mapx = (int)global->constante.posx;
	global->calcul.mapy = (int)global->constante.posy;
	global->calcul.deltadistx = fabs(1 / global->calcul.raydirx);
	global->calcul.deltadisty = fabs(1 / global->calcul.raydiry);
	global->calcul.hit = 0;
	global->sprite = 0; 
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

int my_mlx_loop(t_global *global)
{
	t_parsing *parsing;

	parsing = &global->parsing;
	int x = 0;
	if (global->mlx.tab[307])
		close_mlx(global);
	while (x < parsing->value.rx)
	{
		init_calcul(global, x);
		if(global->calcul.raydirx < 0)
		{
			global->calcul.stepx = -1;
			global->calcul.sidedistx = (global->constante.posx - global->calcul.mapx) * global->calcul.deltadistx;
		}
		else
		{
			global->calcul.stepx = 1;
			global->calcul.sidedistx = (global->calcul.mapx + 1.0 - global->constante.posx) * global->calcul.deltadistx;
		}
		if(global->calcul.raydiry < 0)
		{
			global->calcul.stepy = -1;
			global->calcul.sidedisty = (global->constante.posy - global->calcul.mapy) * global->calcul.deltadisty;
		}
		else
		{
			global->calcul.stepy = 1;
			global->calcul.sidedisty = (global->calcul.mapy + 1.0 - global->constante.posy) * global->calcul.deltadisty;
		}
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
			if (parsing->parse.map[global->calcul.mapx][global->calcul.mapy] == '2')
				lst_sprite_addfront(&global->sprite, lst_sprite(global));
			if(parsing->parse.map[global->calcul.mapx][global->calcul.mapy] == '1')
				global->calcul.hit = 1;
		}
		if (global->calcul.side == 0)
			global->calcul.perpwalldist = (global->calcul.mapx - global->constante.posx + (1 - global->calcul.stepx) / 2) / global->calcul.raydirx;
		else
			global->calcul.perpwalldist = (global->calcul.mapy - global->constante.posy + (1 - global->calcul.stepy) / 2) / global->calcul.raydiry;
		global->pixel.lineheight = (int)(parsing->value.ry / global->calcul.perpwalldist);
		global->pixel.drawstart = -global->pixel.lineheight / 2 + parsing->value.ry / 2;
		if(global->pixel.drawstart < 0)
			global->pixel.drawstart = 0;
		global->pixel.drawend = global->pixel.lineheight / 2 + parsing->value.ry / 2;
		if(global->pixel.drawend >= parsing->value.ry)
			global->pixel.drawend = parsing->value.ry - 1;

		get_texnum(global);

      	if(global->calcul.side == 0)
			global->textures.wallx = global->constante.posy + global->calcul.perpwalldist * global->calcul.raydiry;
      	else          
			global->textures.wallx = global->constante.posx + global->calcul.perpwalldist * global->calcul.raydirx;
		global->textures.wallx -= floor((global->textures.wallx));

		global->textures.texx = (int)(global->textures.wallx *
        (double)global->xpm[global->textures.texnum].w);

    	if (global->calcul.side == 0 && global->calcul.raydirx > 0)
        	global->textures.texx = global->xpm[global->textures.texnum].w - global->textures.texx - 1;
    	if (global->calcul.side == 1 && global->calcul.raydiry < 0)
        	global->textures.texx = global->xpm[global->textures.texnum].w - global->textures.texx - 1;

    	global->textures.step = 1.0 * global->xpm[global->textures.texnum].h /
        global->pixel.lineheight;
    	global->textures.texpos = (global->pixel.drawstart - parsing->value.ry /
        2 + global->pixel.lineheight / 2) * global->textures.step;

		print_col(global, parsing, x);
		if (global->sprite)
			print_sprite(global, 0, x, global->sprite);
		lst_sclear(&global->sprite);
		x++;
	}
	print_minimap(global);
	mlx_put_image_to_window(global->mlx.mlx, global->mlx.win, global->mlx.img, 0, 0);


	double moveSpeed = 0.05;
	double rotSpeed = 0.03;
	double oldPlaneX;
	double oldDirX;

	if(global->mlx.tab[119])
	{
		if(parsing->parse.map[(int)((global->constante.posx + global->constante.dirx * moveSpeed) + (0.01 * global->constante.dirx))][(int)(global->constante.posy)] == '0')
			global->constante.posx += global->constante.dirx * moveSpeed;
		if(parsing->parse.map[(int)(global->constante.posx)][(int)((global->constante.posy + global->constante.diry * moveSpeed) + (0.01 * global->constante.diry))] == '0')
			global->constante.posy += global->constante.diry * moveSpeed;
	}

	if(global->mlx.tab[115])
	{
		if(parsing->parse.map[(int)((global->constante.posx - global->constante.dirx * moveSpeed) + (0.01 * global->constante.dirx))][(int)(global->constante.posy)] == '0')
			global->constante.posx -= global->constante.dirx * moveSpeed;
		if(parsing->parse.map[(int)(global->constante.posx)][(int)((global->constante.posy - global->constante.diry * moveSpeed) + (0.01 * global->constante.diry))] == '0')
			global->constante.posy -= global->constante.diry * moveSpeed;
	}
	if (global->mlx.tab[97])
	{
		if (parsing->parse.map[(int)(global->constante.posx)][(int)((global->constante.posy + global->constante.dirx * moveSpeed) + (0.1 * global->constante.dirx))] == '0')
			global->constante.posy += global->constante.dirx * moveSpeed;
		if (parsing->parse.map[(int)((global->constante.posx - global->constante.diry * moveSpeed) - (0.1 * global->constante.diry))][(int)global->constante.posy] == '0')
			global->constante.posx -= global->constante.diry * moveSpeed;
	}
	if (global->mlx.tab[100])
	{
		if (parsing->parse.map[(int)(global->constante.posx)][(int)((global->constante.posy - global->constante.dirx * moveSpeed) - (0.02 * global->constante.dirx))] == '0')
			global->constante.posy -= global->constante.dirx * moveSpeed;
		if (parsing->parse.map[(int)((global->constante.posx + global->constante.diry * moveSpeed) + (0.02 * global->constante.diry))][(int)global->constante.posy] == '0')
			global->constante.posx += global->constante.diry * moveSpeed;
	}
	if(global->mlx.tab[39])
	{
		oldDirX = global->constante.dirx;
		global->constante.dirx = global->constante.dirx * cos(-rotSpeed) - global->constante.diry * sin(-rotSpeed);
		global->constante.diry = oldDirX * sin(-rotSpeed) + global->constante.diry * cos(-rotSpeed);
		oldPlaneX = global->constante.planex;
		global->constante.planex = global->constante.planex * cos(-rotSpeed) - global->constante.planey * sin(-rotSpeed);
		global->constante.planey = oldPlaneX * sin(-rotSpeed) + global->constante.planey * cos(-rotSpeed);
	}
	if(global->mlx.tab[59])
	{
		oldDirX = global->constante.dirx;
		global->constante.dirx = global->constante.dirx * cos(rotSpeed) - global->constante.diry * sin(rotSpeed);
		global->constante.diry = oldDirX * sin(rotSpeed) + global->constante.diry * cos(rotSpeed);
		oldPlaneX = global->constante.planex;
		global->constante.planex = global->constante.planex * cos(rotSpeed) - global->constante.planey * sin(rotSpeed);
		global->constante.planey = oldPlaneX * sin(rotSpeed) + global->constante.planey * cos(rotSpeed);
	}
	return (0);
}
