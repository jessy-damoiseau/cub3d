#include "../includes/cub3d.h"

void	init_sprite(t_sprite *sprite)
{
	sprite->distsprite = 0;
	sprite->sprite_on = 0;
	sprite->spritemx = 0;
	sprite->spritemy = 0;
	sprite->drawEndsprite = 0;
	sprite->drawStartsprite = 0;
	sprite->lineHeightsprite = 0;
	sprite->wallXsprite = 0;
	sprite->texPossprite = 0;
	sprite->stepsprite = 0;
	sprite->texXsprite = 0;
	sprite->texYsprite = 0;
	sprite->distx = 0;
	sprite->disty = 0;
}

void  print_col(int x, t_parsing *parsing, t_global *global)
{
	int y = 0;
	
	while (y < global->pixel.drawStart)
		global->mlx.addr[y++ * parsing->value.rx + x] = get_color(parsing->value.sky[0], parsing->value.sky[1], parsing->value.sky[2]);
	
	if (!global->calcul.side && global->calcul.stepX == 1)
	{
		global->textures.texX = (int)(global->textures.wallX * (double)global->textures.xn);
		if(global->calcul.side == 0 && global->calcul.rayDirX > 0)
			global->textures.texX = global->textures.xn - global->textures.texX - 1;
		global->textures.step = 1.0 * global->textures.yn / global->pixel.lineHeight;
		global->textures.texPos = (global->pixel.drawStart - global->parsing.value.ry / 2 + global->pixel.lineHeight / 2) * global->textures.step;
	}
	if (!global->calcul.side && global->calcul.stepX == -1)
	{
		global->textures.texX = (int)(global->textures.wallX * (double)global->textures.xso);
		if(global->calcul.side == 0 && global->calcul.rayDirX > 0)
			global->textures.texX = global->textures.xso - global->textures.texX - 1;
		global->textures.step = 1.0 * global->textures.yso / global->pixel.lineHeight;
		global->textures.texPos = (global->pixel.drawStart - global->parsing.value.ry / 2 + global->pixel.lineHeight / 2) * global->textures.step;
	}
	if (global->calcul.side && global->calcul.stepY == 1)
	{
		global->textures.texX = (int)(global->textures.wallX * (double)global->textures.xw);
		if(global->calcul.side == 1 && global->calcul.rayDirY < 0) global->textures.texX = global->textures.xw - global->textures.texX - 1;
			global->textures.texX = global->textures.xw - global->textures.texX - 1;
		global->textures.step = 1.0 * global->textures.yw / global->pixel.lineHeight;
		global->textures.texPos = (global->pixel.drawStart - global->parsing.value.ry / 2 + global->pixel.lineHeight / 2) * global->textures.step;
	}
	if (global->calcul.side && global->calcul.stepY == -1)
	{
		global->textures.texX = (int)(global->textures.wallX * (double)global->textures.xe);
		if(global->calcul.side == 1 && global->calcul.rayDirY < 0) global->textures.texX = global->textures.xe - global->textures.texX - 1;
			global->textures.texX = global->textures.xe - global->textures.texX - 1;
		global->textures.step = 1.0 * global->textures.ye / global->pixel.lineHeight;
		global->textures.texPos = (global->pixel.drawStart - global->parsing.value.ry / 2 + global->pixel.lineHeight / 2) * global->textures.step;
	}
	while (y <= global->pixel.drawEnd)
	{
		if (!global->calcul.side && global->calcul.stepX == 1)
		{
			global->textures.texY = (int)(global->textures.texPos) & (global->textures.yn - 1);
			global->textures.texPos += global->textures.step;
			global->mlx.addr[y * parsing->value.rx + x] = global->mlx.addr_n[global->textures.yn * global->textures.texY + global->textures.texX];
		}
		if (!global->calcul.side && global->calcul.stepX == -1)
		{
			int texY = (int)(global->textures.texPos) & (global->textures.yso - 1);
			global->textures.texPos += global->textures.step;
			global->mlx.addr[y * parsing->value.rx + x] = global->mlx.addr_so[global->textures.yso * texY + global->textures.texX];
		}
		if (global->calcul.side && global->calcul.stepY == 1)
		{
			int texY = (int)(global->textures.texPos) & (global->textures.yw - 1);
			global->textures.texPos +=global->textures.step;
			global->mlx.addr[y * parsing->value.rx + x] = global->mlx.addr_w[global->textures.yw * texY + global->textures.texX];
		}
		if (global->calcul.side && global->calcul.stepY == -1)
		{
			int texY = (int)(global->textures.texPos) & (global->textures.ye - 1);
			global->textures.texPos +=global->textures.step;
			global->mlx.addr[y * parsing->value.rx + x] = global->mlx.addr_e[global->textures.ye * texY + global->textures.texX];
		}
		y++;
	}
	while (y < global->parsing.value.ry)
		global->mlx.addr[y++ * parsing->value.rx + x] = get_color(parsing->value.floor[0], parsing->value.floor[1], parsing->value.floor[2]);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	y = global->sprite.drawStartsprite;
	if (global->sprite.sprite_on)
	{
		global->sprite.texXsprite = (int)(global->sprite.wallXsprite * (double)global->textures.xs);
		//if(global->calcul.side == 0 && global->calcul.rayDirX > 0)
			global->sprite.texXsprite = global->textures.xs - global->sprite.texXsprite - 1;
		//if(global->calcul.side == 1 && global->calcul.rayDirY < 0)
		//	global->sprite.texXsprite = global->textures.xs - global->sprite.texXsprite - 1;
		global->sprite.stepsprite = 1.0 * global->textures.ys / global->sprite.lineHeightsprite;
		global->sprite.texPossprite = (global->sprite.drawStartsprite - global->parsing.value.ry / 2 + global->sprite.lineHeightsprite / 2) * global->sprite.stepsprite;
	}
	while (global->sprite.sprite_on && y <= global->sprite.drawEndsprite)
	{
		int texYsprite = (int)(global->sprite.texPossprite) & (global->textures.ys - 1);
		global->sprite.texPossprite +=global->sprite.stepsprite;
		if (global->mlx.addr_s[global->textures.ys * texYsprite + global->sprite.texXsprite] != 0)
			global->mlx.addr[y * parsing->value.rx + x] = global->mlx.addr_s[global->textures.ys * texYsprite + global->sprite.texXsprite];
		y++;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
void	init_calcul(t_global *global, int x)
{
	global->calcul.cameraX = 2 * x / (double)global->parsing.value.rx - 1; 
	global->calcul.rayDirX = global->constante.dirX + global->constante.planeX * global->calcul.cameraX;
	global->calcul.rayDirY = global->constante.dirY + global->constante.planeY * global->calcul.cameraX;
	global->calcul.mapX = (int)global->constante.posX;
	global->calcul.mapY = (int)global->constante.posY;
	global->calcul.deltaDistX = fabs(1 / global->calcul.rayDirX);
	global->calcul.deltaDistY = fabs(1 / global->calcul.rayDirY);
	global->calcul.hit = 0; 
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
		init_sprite(&global->sprite);
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
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(parsing->parse.map[global->calcul.mapX][global->calcul.mapY] == '2')
			{
				global->sprite.sprite_on = 1;
				if (global->calcul.side == 0)
					global->sprite.distsprite = ((global->calcul.mapX - global->constante.posX + (1 - global->calcul.stepX) / 2) / global->calcul.rayDirX) + 0.5;
				else
					global->sprite.distsprite = ((global->calcul.mapY - global->constante.posY + (1 - global->calcul.stepY) / 2) / global->calcul.rayDirY) + 0.5;
				global->sprite.lineHeightsprite = (int)(parsing->value.ry /global->sprite.distsprite);
				global->sprite.drawStartsprite = -global->sprite.lineHeightsprite / 2 + parsing->value.ry / 2;
				if(global->sprite.drawStartsprite < 0)
					global->sprite.drawStartsprite = 0;
				global->sprite.drawEndsprite = global->sprite.lineHeightsprite / 2 + parsing->value.ry / 2;
				if(global->sprite.drawEndsprite >= parsing->value.ry)
					global->sprite.drawEndsprite = parsing->value.ry - 1;
				if(global->calcul.side == 0)
					global->sprite.wallXsprite = global->constante.posY + global->sprite.distsprite * global->calcul.rayDirY;
				else
					global->sprite.wallXsprite = global->constante.posX + global->sprite.distsprite * global->calcul.rayDirX;
				global->sprite.wallXsprite -= floor((global->sprite.wallXsprite));
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
      	if(global->calcul.side == 0)
			global->textures.wallX = global->constante.posY + global->calcul.perpWallDist * global->calcul.rayDirY;
      	else          
			global->textures.wallX = global->constante.posX + global->calcul.perpWallDist * global->calcul.rayDirX;
		global->textures.wallX -= floor((global->textures.wallX));
		print_col(x, parsing, global);
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
