#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "parsing.h"
# include "../minilibx-linux/mlx.h"

# define FOV 0.9
# define uDiv 1
# define vDiv 1
# define vMove 0.0
# define MOVESPEED 0.05
# define ROTSPEED 0.03
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100

typedef struct	s_calcul
{
	double	camerax;
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
}				t_calcul;

typedef struct  s_const
{
        double  posx;
        double  posy;
        double  dirx;
        double  diry;
        double  planex;
        double  planey;
		int 	nsprites;
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
	double	texpos;
	double	step;
	int 	texx;
	int		texy;
	double	wallx;
	int		texnum;
}				t_textures;


typedef struct	s_nb_wpixel
{
	int		lineheight;
	int		drawstart;
	int		drawend;
}				t_nb_wpixel;

typedef struct        s_xpm
{
    void            *img;
    int             *addr;
    int                w;
    int                h;
}                    t_xpm;


typedef struct	s_csprite
{
	double *zbuffer;
	int *spriteorder;
	double *spritedistance;
	double spritex;
	double spritey;
	double invdet;
	double transformx;
	double transformy;
	int spritescreenx;
	int vmovescreen;
	int spriteheight;
	int drawstarty;
	int drawendy;
	int spritewidth;
	int drawstartx;
	int drawendx;
	int texx;
	int d;
	int texy;
}				t_csprite;


typedef struct s_sprite
{
  double x;
  double y;
}				t_sprite;

typedef struct		s_pair
{
	double	first;
	int		second;
}					t_pair;


typedef struct	s_global
{
	t_calcul	calcul;
	t_mlx		mlx;
	t_nb_wpixel pixel;
    t_const     constante;
	t_parsing 	parsing;
	t_textures	textures;
	t_xpm		xpm[5];
	t_sprite	*sprite;
	t_csprite	csprite;
}				t_global;

void			value_windows_size(t_global *global);
int				close_mlx(t_global *global);
int				get_color(int r, int g, int b);
int				keypress(int keycode, t_mlx *mlx);
int				keyrelease(int keycode, t_mlx *mlx);
int 			my_mlx_loop(t_global *global);
void			init_mlx(t_global *global);
void			print_minimap(t_global *global);
t_sprite    	*lst_sprite(t_global *global);
void    		lst_sprite_addfront(t_sprite **alst, t_sprite *new);
void    		lst_sclear(t_sprite **lst);

#endif
