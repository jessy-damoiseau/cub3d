#include "../includes/cub3d.h"

void    print_col(t_global *global, t_parsing *parsing, int x)
{
    int y;

    y = 0;
    while (y < global->pixel.drawStart)
        global->mlx.addr[y++ * parsing->value.rx + x] = get_color(parsing->value.sky[0],
		parsing->value.sky[1], parsing->value.sky[2]);
    while (y <= global->pixel.drawEnd)
    {
        if (parsing->parse.map[global->calcul.mapX][global->calcul.mapY] == '1')
        {
            global->textures.texY = (int)global->textures.texPos &
                (global->xpm[global->textures.texnum].h - 1);
            global->textures.texPos += global->textures.step;
           global->mlx.addr[y++ * parsing->value.rx + x] =
            global->xpm[global->textures.texnum].addr[global->xpm[global->textures.texnum].h
                * global->textures.texY + global->textures.texX];
        }
        else
            global->mlx.addr[y++ * parsing->value.rx + x] = 0x3F51B5;
    }
    while (y < parsing->value.ry)
        global->mlx.addr[y++ * parsing->value.rx + x] = get_color(parsing->value.floor[0],
		parsing->value.floor[1], parsing->value.floor[2]);
}

void	init_calcul(t_global *global, int x)
{
	global->calcul.cameraX = 2 * x / (double)global->parsing.value.rx - 1; 
	global->calcul.rayDirX = global->constante.dirX +
	global->constante.planeX * global->calcul.cameraX;
	global->calcul.rayDirY = global->constante.dirY +
	global->constante.planeY * global->calcul.cameraX;
	global->calcul.mapX = (int)global->constante.posX;
	global->calcul.mapY = (int)global->constante.posY;
	global->calcul.deltaDistX = fabs(1 / global->calcul.rayDirX);
	global->calcul.deltaDistY = fabs(1 / global->calcul.rayDirY);
	global->calcul.hit = 0; 
}

void	get_texnum(t_global *global)
{
	if (!global->calcul.side && global->calcul.stepX == -1)
		global->textures.texnum = 0;
	if (!global->calcul.side && global->calcul.stepX == 1)
		global->textures.texnum = 1;
	if (global->calcul.side && global->calcul.stepY == -1)
		global->textures.texnum = 2;
	if (global->calcul.side && global->calcul.stepY == 1)
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
		if(global->calcul.rayDirX < 0)
		{
			global->calcul.stepX = -1;
			global->calcul.sideDistX = (global->constante.posX - global->calcul.mapX) * global->calcul.deltaDistX;
		}
		else
		{
			global->calcul.stepX = 1;
			global->calcul.sideDistX = (global->calcul.mapX + 1.0 - global->constante.posX) * global->calcul.deltaDistX;
		}
		if(global->calcul.rayDirY < 0)
		{
			global->calcul.stepY = -1;
			global->calcul.sideDistY = (global->constante.posY - global->calcul.mapY) * global->calcul.deltaDistY;
		}
		else
		{
			global->calcul.stepY = 1;
			global->calcul.sideDistY = (global->calcul.mapY + 1.0 - global->constante.posY) * global->calcul.deltaDistY;
		}
		while (global->calcul.hit == 0)
		{

			if(global->calcul.sideDistX < global->calcul.sideDistY)
			{
				global->calcul.sideDistX += global->calcul.deltaDistX;
				global->calcul.mapX += global->calcul.stepX;
				global->calcul.side = 0;
			}
			else
			{
				global->calcul.sideDistY += global->calcul.deltaDistY;
				global->calcul.mapY += global->calcul.stepY;
				global->calcul.side = 1;
			}
			if (parsing->parse.map[global->calcul.mapX][global->calcul.mapY] == '2')
			{
				
			}
			if(parsing->parse.map[global->calcul.mapX][global->calcul.mapY] == '1')
				global->calcul.hit = 1;
		}
		if (global->calcul.side == 0)
			global->calcul.perpWallDist = (global->calcul.mapX - global->constante.posX + (1 - global->calcul.stepX) / 2) / global->calcul.rayDirX;
		else
			global->calcul.perpWallDist = (global->calcul.mapY - global->constante.posY + (1 - global->calcul.stepY) / 2) / global->calcul.rayDirY;
		global->pixel.lineHeight = (int)(parsing->value.ry /global->calcul.perpWallDist);
		global->pixel.drawStart = -global->pixel.lineHeight / 2 + parsing->value.ry / 2;
		if(global->pixel.drawStart < 0)
			global->pixel.drawStart = 0;
		global->pixel.drawEnd = global->pixel.lineHeight / 2 + parsing->value.ry / 2;
		if(global->pixel.drawEnd >= parsing->value.ry)
			global->pixel.drawEnd = parsing->value.ry - 1;

		get_texnum(global);

      	if(global->calcul.side == 0)
			global->textures.wallX = global->constante.posY + global->calcul.perpWallDist * global->calcul.rayDirY;
      	else          
			global->textures.wallX = global->constante.posX + global->calcul.perpWallDist * global->calcul.rayDirX;
		global->textures.wallX -= floor((global->textures.wallX));

		global->textures.texX = (int)(global->textures.wallX *
        (double)global->xpm[global->textures.texnum].w);

    	if (global->calcul.side == 0 && global->calcul.rayDirX > 0)
        	global->textures.texX = global->xpm[global->textures.texnum].w - global->textures.texX - 1;
    	if (global->calcul.side == 1 && global->calcul.rayDirY < 0)
        	global->textures.texX = global->xpm[global->textures.texnum].w - global->textures.texX - 1;

    	global->textures.step = 1.0 * global->xpm[global->textures.texnum].h /
        global->pixel.lineHeight;
    	global->textures.texPos = (global->pixel.drawStart - parsing->value.ry /
        2 + global->pixel.lineHeight / 2) * global->textures.step;

		print_col(global, parsing, x);
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
		if(parsing->parse.map[(int)((global->constante.posX + global->constante.dirX * moveSpeed) + (0.01 * global->constante.dirX))][(int)(global->constante.posY)] == '0')
			global->constante.posX += global->constante.dirX * moveSpeed;
		if(parsing->parse.map[(int)(global->constante.posX)][(int)((global->constante.posY + global->constante.dirY * moveSpeed) + (0.01 * global->constante.dirY))] == '0')
			global->constante.posY += global->constante.dirY * moveSpeed;
	}

	if(global->mlx.tab[115])
	{
		if(parsing->parse.map[(int)((global->constante.posX - global->constante.dirX * moveSpeed) + (0.01 * global->constante.dirX))][(int)(global->constante.posY)] == '0')
			global->constante.posX -= global->constante.dirX * moveSpeed;
		if(parsing->parse.map[(int)(global->constante.posX)][(int)((global->constante.posY - global->constante.dirY * moveSpeed) + (0.01 * global->constante.dirY))] == '0')
			global->constante.posY -= global->constante.dirY * moveSpeed;
	}
	if (global->mlx.tab[97])
	{
		if (parsing->parse.map[(int)(global->constante.posX)][(int)((global->constante.posY + global->constante.dirX * moveSpeed) + (0.1 * global->constante.dirX))] == '0')
			global->constante.posY += global->constante.dirX * moveSpeed;
		if (parsing->parse.map[(int)((global->constante.posX - global->constante.dirY * moveSpeed) - (0.1 * global->constante.dirY))][(int)global->constante.posY] == '0')
			global->constante.posX -= global->constante.dirY * moveSpeed;
	}
	if (global->mlx.tab[100])
	{
		if (parsing->parse.map[(int)(global->constante.posX)][(int)((global->constante.posY - global->constante.dirX * moveSpeed) - (0.02 * global->constante.dirX))] == '0')
			global->constante.posY -= global->constante.dirX * moveSpeed;
		if (parsing->parse.map[(int)((global->constante.posX + global->constante.dirY * moveSpeed) + (0.02 * global->constante.dirY))][(int)global->constante.posY] == '0')
			global->constante.posX += global->constante.dirY * moveSpeed;
	}
	if(global->mlx.tab[39])
	{
		oldDirX = global->constante.dirX;
		global->constante.dirX = global->constante.dirX * cos(-rotSpeed) - global->constante.dirY * sin(-rotSpeed);
		global->constante.dirY = oldDirX * sin(-rotSpeed) + global->constante.dirY * cos(-rotSpeed);
		oldPlaneX = global->constante.planeX;
		global->constante.planeX = global->constante.planeX * cos(-rotSpeed) - global->constante.planeY * sin(-rotSpeed);
		global->constante.planeY = oldPlaneX * sin(-rotSpeed) + global->constante.planeY * cos(-rotSpeed);
	}
	if(global->mlx.tab[59])
	{
		oldDirX = global->constante.dirX;
		global->constante.dirX = global->constante.dirX * cos(rotSpeed) - global->constante.dirY * sin(rotSpeed);
		global->constante.dirY = oldDirX * sin(rotSpeed) + global->constante.dirY * cos(rotSpeed);
		oldPlaneX = global->constante.planeX;
		global->constante.planeX = global->constante.planeX * cos(rotSpeed) - global->constante.planeY * sin(rotSpeed);
		global->constante.planeY = oldPlaneX * sin(rotSpeed) + global->constante.planeY * cos(rotSpeed);
	}
	return (0);
}
