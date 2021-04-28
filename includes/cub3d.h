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
	int	    *addr;
}				t_mlx;

typedef struct	s_textures
{
	double	texPos;
	double	step;
	int 	texX;
	int		texY;
	double	wallX;
	int		texnum;
}				t_textures;


typedef struct	s_nb_wpixel
{
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
}				t_nb_wpixel;

typedef struct        s_xpm
{
    void            *img;
    int             *addr;
    int                w;
    int                h;
}                    t_xpm;

typedef struct	s_sprite
{
	
	int		mapx_sprite;
	int		mapy_sprite;
	double	sidedistx_sprite;
	double	sidedisty_sprite;
	double	spritedist;
	
	void	*next;
}				t_sprite;


typedef struct	s_global
{
	t_calcul	calcul;
	t_mlx		mlx;
	t_nb_wpixel pixel;
    t_const     constante;
	t_parsing 	parsing;
	t_textures	textures;
	t_xpm		xpm[5];
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
