#ifndef CUB3D_H
#define CUB3D_H

# include <math.h>
# include "parsing.h"
# include "../minilibx-linux/mlx.h"

# define FOV 0.9

typedef struct	s_calcul
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
}				t_calcul;

typedef struct  s_const
{
        double  posX;
        double  posY;
        double  dirX;
        double  dirY;
        double  planeX;
        double  planeY;
}               t_const;

typedef struct	s_mlx
{
	char	tab[512];
	void	*mlx;
	void	*win;
	void	*img;
	void	*img_n;
	void	*img_so;
	void	*img_s;
	void	*img_w;
	void	*img_e;
	int	    *addr;
	int		*addr_n;
	int		*addr_so;
	int		*addr_w;
	int		*addr_e;
	int		*addr_s;
}				t_mlx;

typedef struct	s_textures
{
	int		xn;
	int		yn;
	int		xso;
	int		yso;
	int		xw;
	int		yw;
	int		xe;
	int		ye;
	int		xs;
	int		ys;
	double texPos;
	double step;
	int texX;
	int texY;
	double wallX;
}				t_textures;


typedef struct	s_nb_wpixel
{
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	
}				t_nb_wpixel;

typedef struct	s_global
{
	t_calcul	calcul;
	t_mlx		mlx;
	t_nb_wpixel pixel;
    t_const     constante;
	t_parsing 	parsing;
	t_textures	textures;
}				t_global;

void	value_windows_size(t_global *global);
int		close_mlx(t_global *global);
int		get_color(int r, int g, int b);
int		keypress(int keycode, t_mlx *mlx);
int		keyrelease(int keycode, t_mlx *mlx);
int 	my_mlx_loop(t_global *global);
void	init_mlx(t_global *global);
void	print_minimap(t_global *global);

#endif
