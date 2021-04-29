#ifndef CUB3D_H
#define CUB3D_H

# include <math.h>
# include "parsing.h"
# include "../minilibx-linux/mlx.h"

# define FOV 0.9

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
	double	texpos;
	double	step;
	int 	texx;
	int		texy;
	double	wallx;
}				t_csprite;

typedef struct	s_sprite
{
	double			mapx_sprite;
	double			mapy_sprite;
	double			sidedistx_sprite;
	double			sidedisty_sprite;
	int 			draws_start;
	int				draws_end;
	int				lineheight;
	double			spritedist;
	int				side;

	struct s_sprite	*next;
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
