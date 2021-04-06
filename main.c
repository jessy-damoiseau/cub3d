# include "includes/cub3d.h"

void	init_textures(t_global *global)
{
	int trash;

	global->mlx.img_n = mlx_xpm_file_to_image(global->mlx.mlx,
	global->parsing.parse.no, &global->textures.xn, &global->textures.yn);
	global->mlx.img_so = mlx_xpm_file_to_image(global->mlx.mlx,
	global->parsing.parse.so, &global->textures.xso, &global->textures.yso);
	global->mlx.img_w = mlx_xpm_file_to_image(global->mlx.mlx,
	global->parsing.parse.we, &global->textures.xw, &global->textures.yw);
	global->mlx.img_e = mlx_xpm_file_to_image(global->mlx.mlx,
	global->parsing.parse.ea, &global->textures.xe, &global->textures.ye);
	global->mlx.img_s = mlx_xpm_file_to_image(global->mlx.mlx,
	global->parsing.parse.s, &global->textures.xs, &global->textures.ys);
	global->mlx.addr_n = (int*)mlx_get_data_addr(global->mlx.img_n,
	&trash, &trash, &trash);
	global->mlx.addr_so = (int*)mlx_get_data_addr(global->mlx.img_so,
	&trash, &trash, &trash);
	global->mlx.addr_w = (int*)mlx_get_data_addr(global->mlx.img_w,
	&trash, &trash, &trash);
	global->mlx.addr_e = (int*)mlx_get_data_addr(global->mlx.img_e,
	&trash, &trash, &trash);
	global->mlx.addr_s = (int*)mlx_get_data_addr(global->mlx.img_s,
	&trash, &trash, &trash);
}

void	init_mlx(t_global *global)
{
    int i = 0;
	init_textures(global);
    value_windows_size(global);
    while (i < 512)
      global->mlx.tab[i++] = 0;
}

void	init_strut_next(t_global *global)
{
	global->textures.yn = 0;
	global->textures.xn = 0;
	global->textures.yso = 0;
	global->textures.xso = 0;
	global->textures.ye = 0;
	global->textures.xe = 0;
	global->textures.yw = 0;
	global->textures.xw = 0;
	global->textures.ys = 0;
	global->textures.xs = 0;
	global->textures.texPos = 0;
	global->textures.step = 0;
	global->textures.texX = 0;
	global->textures.texY = 0;
	global->textures.wallX = 0;
}


void	init_struct(t_global *global)
{
	global->calcul.cameraX = 0;
	global->calcul.rayDirX = 0;
	global->calcul.rayDirY = 0;
	global->calcul.mapX = 0;
	global->calcul.mapY = 0;
	global->calcul.sideDistX = 0;
	global->calcul.sideDistY = 0;
	global->calcul.deltaDistX = 0;
	global->calcul.deltaDistY = 0;
	global->calcul.perpWallDist = 0;
	global->calcul.stepX = 0;
	global->calcul.stepY = 0;
	global->calcul.hit = 0;
	global->calcul.side = 0;
	global->constante.posX = 0;
	global->constante.posY = 0;
	global->constante.dirX = 0;
	global->constante.dirY = 0;
	global->constante.planeX = 0;
	global->constante.planeY = 0;
	global->pixel.lineHeight = 0;
	global->pixel.drawStart = 0;
	global->pixel.drawEnd = 0;
	init_strut_next(global);
}

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

void	get_dir(t_global *global)
{
	char c;

	c = global->parsing.parse.map[(int)global->constante.posX]
	[(int)global->constante.posY];
	if (c == 'N')
	{
		global->constante.dirX = -1, global->constante.dirY = 0;
		global->constante.planeX = 0, global->constante.planeY = 0.9;
	}
	if (c == 'S')
	{
		global->constante.dirX = 1, global->constante.dirY = 0;
		global->constante.planeX = 0, global->constante.planeY = -0.9;
	}
	if (c == 'W')
	{
		global->constante.dirX = 0, global->constante.dirY = -1;
		global->constante.planeX = -0.9, global->constante.planeY = 0;
	}
	if (c == 'E')
	{
		global->constante.dirX = 0, global->constante.dirY = 1;
		global->constante.planeX = 0.9, global->constante.planeY = 0;
	}
}

void	init_constante(t_global *global)
{

	global->constante.posX = get_spawn(global->parsing.parse.map, 0) + 0.5;
	global->constante.posY = get_spawn(global->parsing.parse.map, 1) + 0.5;
	get_dir(global);
	global->parsing.parse.map[(int)global->constante.posX]
	[(int)global->constante.posY] = '0';
}

int main(int ac, char **av)
{
	t_global global;
	int trash;

	init_struct(&global);
	if (parse(ac, &global.parsing, av))
		return (1);
	init_constante(&global);
	global.mlx.mlx = mlx_init();
	init_mlx(&global);
	global.mlx.win = mlx_new_window(global.mlx.mlx, global.parsing.value.rx,
	global.parsing.value.ry, "cub3d");
	mlx_hook(global.mlx.win, 2, 1L<<0, keypress, &global.mlx);
	mlx_hook(global.mlx.win, 3, 1L<<1, keyrelease, &global.mlx);
	mlx_hook(global.mlx.win, 33, 1L<<17, close_mlx, &global.mlx);
	global.mlx.img = mlx_new_image(global.mlx.mlx, global.parsing.value.rx,
	global.parsing.value.ry);
	global.mlx.addr = (int*)mlx_get_data_addr(global.mlx.img, &trash,
	&trash, &trash);
	mlx_loop_hook(global.mlx.mlx, my_mlx_loop, (void*)&global);
	mlx_loop(global.mlx.mlx);
}