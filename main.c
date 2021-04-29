# include "includes/cub3d.h"

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
    int i = 0;
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
	global->pixel.lineheight = 0;
	global->pixel.drawstart = 0;
	global->pixel.drawend = 0;
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

	c = global->parsing.parse.map[(int)global->constante.posx]
	[(int)global->constante.posy];
	if (c == 'N')
	{
		global->constante.dirx = -1, global->constante.diry = 0;
		global->constante.planex = 0, global->constante.planey = 0.9;
	}
	if (c == 'S')
	{
		global->constante.dirx = 1, global->constante.diry = 0;
		global->constante.planex = 0, global->constante.planey = -0.9;
	}
	if (c == 'W')
	{
		global->constante.dirx = 0, global->constante.diry = -1;
		global->constante.planex = -0.9, global->constante.planey = 0;
	}
	if (c == 'E')
	{
		global->constante.dirx = 0, global->constante.diry = 1;
		global->constante.planex = 0.9, global->constante.planey = 0;
	}
}

void	init_constante(t_global *global)
{

	global->constante.posx = get_spawn(global->parsing.parse.map, 0) + 0.5;
	global->constante.posy = get_spawn(global->parsing.parse.map, 1) + 0.5;
	get_dir(global);
	global->parsing.parse.map[(int)global->constante.posx]
	[(int)global->constante.posy] = '0';
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
