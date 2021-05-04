/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:31:21 by user42            #+#    #+#             */
/*   Updated: 2021/05/04 20:00:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "parsing.h"
# include "../minilibx-linux/mlx.h"

# define FOV 0.9
# define UDIV 1
# define VDIV 1
# define VMOVE 0.0
# define MOVESPEED 0.05
# define ROTSPEED 0.03
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_RIGTHROT 39
# define KEY_LEFTROT 59

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

typedef struct	s_const
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	int		nsprites;
}				t_const;

typedef struct	s_mlx
{
	char	tab[512];
	void	*mlx;
	void	*win;
	void	*img;
	int		*addr;
	int		bpp;
	int		len_line;
	int		endian;
}				t_mlx;

typedef struct	s_textures
{
	double	texpos;
	double	step;
	int		texx;
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

typedef struct	s_xpm
{
	void	*img;
	int		*addr;
	int		w;
	int		h;
}				t_xpm;

typedef struct	s_csprite
{
	double	*zbuffer;
	int		*spriteorder;
	double	*spritedistance;
	double	spritex;
	double	spritey;
	double	invdet;
	double	transformx;
	double	transformy;
	int		spritescreenx;
	int		vmovescreen;
	int		spriteheight;
	int		drawstarty;
	int		drawendy;
	int		spritewidth;
	int		drawstartx;
	int		drawendx;
	int		texx;
	int		d;
	int		texy;
}				t_csprite;

typedef struct	s_sprite
{
	double	x;
	double	y;
}				t_sprite;

typedef struct	s_pair
{
	double	first;
	int		second;
}				t_pair;


typedef struct	s_global
{
	t_calcul	calcul;
	t_mlx		mlx;
	t_nb_wpixel pixel;
	t_const		constante;
	t_psing		psing;
	t_textures	textures;
	t_xpm		xpm[5];
	t_sprite	*sprite;
	t_csprite	csprite;
}				t_global;

void			value_windows_size(t_global *global);
int				init_textures(t_global *global);
int				init_mlx(t_global *global);
void			init_strut_next(t_global *global);
void			init_struct(t_global *global);
void			init_constante(t_global *global);
void			get_dir2(t_global *global, char c);
void			get_dir(t_global *global);
void			check_hit(t_global *global, t_psing *psing);
void			calcul_perpandlentext(t_global *global, t_psing *psing);
void			calculfortex(t_global *global, t_psing *psing);
int				my_mlx_loop2(t_global *global);
int				my_mlx_loop(t_global *global);
void			check_move4(t_global *global);
void			check_move3(t_global *global);
void			check_move2(t_global *global, t_psing *psing);
void			check_move(t_global *global, t_psing *psing);
void			take_raystepsidedist(t_global *global);
void			first_part_sprite(t_global *global);
void			calcul_sprite(t_global *global, t_psing *psing, int i);
void			calcul_lensprite(t_global *global, t_psing *psing);
void			fill_addr(t_global *global, t_psing *psing);
void			print_sprite(t_global *global, t_psing *psing);
int				close_mlx(t_global *global);
int				get_color(int r, int g, int b);
int				keypress(int keycode, t_mlx *mlx);
int				keyrelease(int keycode, t_mlx *mlx);
void			free_sprite(t_global *global);
void			init_calcul(t_global *global, int x);
void			get_texnum(t_global *global);
void			sort_order(t_pair *orders, int amount);
void			sortsprites(t_global *global);
int				malloc_sprite(t_global *global, t_psing *psing);
void			print_col(t_global *global, t_psing *psing, int x);
int				get_spawn(char **map, int i);
void			check_sprite2(t_global *global);
void			check_sprite(t_global *global);
void			fill_bmp(t_global *global);
char 			**fill_space_map(t_psing *gbal);
char			*fill_space(char *str, int len);
int check_error_r(char *line, int *c, t_global *global);
int check_error_fc(char *line, int *param, t_global *global, int c);
int check_error_texture(char *line, t_global *global, int c);
int check_error_sprite(char *line, t_global *global);
int check_char_map(t_global *global);
int check_error_map(t_global *global);
int check_spawn(t_global *global);
void    init_struct(t_global *global);
int fill_and_checkerror(t_global *global, t_psing *psing);
int parse(int ac, char **av, t_global *global, t_psing *psing);
void    init_parse(t_global *global);
int fill_map(t_psing *psing);

#endif
