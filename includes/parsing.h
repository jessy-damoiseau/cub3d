/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 01:56:23 by user42            #+#    #+#             */
/*   Updated: 2021/05/05 01:57:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct	s_file
{
	char	*line;
	void	*next;
}				t_file;

typedef struct	s_parse
{
	int		r;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	int		f;
	int		c;
	char	**map;
	int		nb_pfill;
	int		len_map;
}				t_parse;

typedef struct	s_value
{
	int		rx;
	int		ry;
	int		floor[3];
	int		sky[3];
	int		save;
	int		x;
	int		y;
}				t_value;

typedef struct	s_psing
{
	t_parse	parse;
	t_value	value;
	t_file	*file;
}				t_psing;

size_t			ft_strlen(const char *s);
void			*ft_memmove(void *dst, const void *src, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
int				check_return(char *str);
char			*get_next_str(char *str);
char			*get_line_return(char *str);
int				gnl(int fd, char **line);
int				check_hole(char **map);
int				propagation(int x, int y, char **map, int stop);
int				fill_xy(char *str, t_psing *psing, int *c);
void			fill_f(char *str, t_psing *psing);
void			fill_c(char *str, t_psing *psing);
void			fill_fc(char *str, t_psing *psing, int *param, int c);
void			fill_texture(char *str, t_psing *psing, int c);
int				check_file2(char *arg);
int				check_file(int ac, char **av, int *i, t_psing *psing);
int				clear_parse(t_parse *parse);
int				cmp(char *s1, char *s2);
void			lstadd_back(t_file **alst, t_file *new);
int				lst_size(t_file *lst, t_psing *psing);
void			lstclear(t_file **lst);
t_file			*lstnew(char *str);
int				len(char *str);
int				nb_virgule(char *str);
int				trim_cmp(char s, char *set);
void			trim(char **dest, char *s, char *set);
char			**str_ds_dup(char **str);
void			free_ds(char **map);
int				find(int c);
int				check_if_map(char *line);
int				check_virgule(char *str);
int				find_spawn(int c);

#endif
