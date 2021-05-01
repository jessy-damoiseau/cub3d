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

int my_mlx_loop(t_global *global)
{
	t_parsing *parsing;

	parsing = &global->parsing;
	int x = 0;

	global->sprite->x = 2.5;
	global->sprite->y = 14.5;
	int numSprites = 1;
	double ZBuffer[parsing->value.rx];
	int spriteOrder[numSprites];
	double spriteDistance[1];


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
	  ZBuffer[x] = global->calcul.perpwalldist;
		x++;
	}

	for(int i = 0; i < numSprites; i++)
    {
      spriteOrder[i] = i;
      spriteDistance[i] = ((global->constante.posx - global->sprite[i].x) * (global->constante.posx - global->sprite[i].x) + (global->constante.posy - global->sprite[i].y) * (global->constante.posy - global->sprite[i].y));
    }
    sortSprites(spriteOrder, spriteDistance, numSprites);

    for(int i = 0; i < numSprites; i++)
    {
      double spriteX = global->sprite[spriteOrder[i]].x - global->constante.posx;
      double spriteY = global->sprite[spriteOrder[i]].y - global->constante.posy;

      double invDet = 1.0 / (global->constante.planex * global->constante.diry - global->constante.dirx * global->constante.planey);

      double transformX = invDet * (global->constante.diry * spriteX - global->constante.dirx * spriteY);
      double transformY = invDet * (-global->constante.planey * spriteX + global->constante.planex * spriteY);

      int spriteScreenX = (int)((parsing->value.rx / 2) * (1 + transformX / transformY));

      #define uDiv 1
      #define vDiv 1
      #define vMove 0.0
      int vMoveScreen = (int)(vMove / transformY);
      int spriteHeight = abs((int)(parsing->value.ry / (transformY))) / vDiv;
      int drawStartY = -spriteHeight / 2 + parsing->value.ry / 2 + vMoveScreen;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + parsing->value.ry / 2 + vMoveScreen;
      if(drawEndY >= parsing->value.ry) drawEndY = parsing->value.ry - 1;

      int spriteWidth = abs((int)(parsing->value.ry / (transformY))) / uDiv;
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= parsing->value.rx) drawEndX = parsing->value.ry - 1;

      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * global->xpm[4].w / spriteWidth) / 256;
        if(transformY > 0 && stripe > 0 && stripe < parsing->value.rx && transformY < ZBuffer[stripe])
        for(int y = drawStartY; y < drawEndY; y++)
        {
          int d = (y-vMoveScreen) * 256 - parsing->value.ry * 128 + spriteHeight * 128;
          int texY = ((d * global->xpm[global->textures.texnum].h) / spriteHeight) / 256;
		  if (global->xpm[4].addr[global->xpm[global->textures.texnum].w * texY + texX])
          	global->mlx.addr[y * parsing->value.rx + stripe] = global->xpm[4].addr[global->xpm[global->textures.texnum].w * texY + texX];
        }
      }
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
