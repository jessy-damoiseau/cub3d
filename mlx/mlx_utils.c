#include "../includes/cub3d.h"

int	close_mlx(t_global *global)
{
	clear_parse(&global->parsing.parse);
	mlx_destroy_image(global->mlx.mlx, global->mlx.img);
	mlx_destroy_image(global->mlx.mlx, global->mlx.img_n);
	mlx_destroy_image(global->mlx.mlx, global->mlx.img_so);
	mlx_destroy_image(global->mlx.mlx, global->mlx.img_w);
	mlx_destroy_image(global->mlx.mlx, global->mlx.img_e);
	mlx_destroy_image(global->mlx.mlx, global->mlx.img_s);
	mlx_destroy_window(global->mlx.mlx, global->mlx.win);
	mlx_destroy_display(global->mlx.mlx);

	free(global->mlx.mlx);
	exit(0);
}

int get_color(int r, int g, int b)
{
	return (256 * 256 * r + 256 * g + b);
}

int	keypress(int keycode, t_mlx *mlx)
{
	if (keycode % 1000 < 512)
		mlx->tab[keycode % 1000] = 1;
	return (0);
}

int keyrelease(int keycode, t_mlx *mlx)
{
	if (keycode % 1000 < 512)
		mlx->tab[keycode % 1000] = 0;
	return (0);
}
