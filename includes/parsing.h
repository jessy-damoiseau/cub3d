/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 16:09:14 by user42            #+#    #+#             */
/*   Updated: 2021/04/28 16:09:15 by user42           ###   ########.fr       */
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
	char	*r;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	char	*f;
	char	*c;
	char	**map;
	int		nb_param_fill;
}				t_parse;

typedef struct	s_value
{
	int		rx;
	int		ry;
	int		floor[3];
	int		sky[3];
}				t_value;

typedef struct	s_parsing
{
	t_value	value;
	t_parse	parse;
	t_file	*file;
}				t_parsing;

int				get_next_line(int fd, char **line);
char			*get_next_str(char *str);
char			*get_line_return(char *str);
int				ft_strlen(char *s);
void			*ft_memmove(void *dst, void *src, size_t len);
char			*ft_strjoin(char *s1, char *s2);
int				check_return(char *str);
int				parse(int ac, t_parsing *global, char **arg);
int				check_file(int ac, char **arg);
int				get_param(t_parsing *global);
int				fill_struct_param(char *param, t_parse *parse);
int				check_error(t_parsing *global);
int				check_args_texture(t_parsing *global);
void			parsing_rfc(t_parsing *global);
int				ft_atoi_fc(char *str);
int				ft_atoi_r(char *str);
int				check_r(char *r);
int				check_fc(char *str);
int				check_spawn(char **map);
int				check_is_param(char *line);
int				check_map(char **map);
char			**propagation(int x, int y, char **map, int stop);
int				check_hole(char **map);
char			*ft_strtrim(char *s, char *set);
t_file			*ft_lstnew(char *content);
void			ft_lstadd_back(t_file **alst, t_file *new);
int				ft_lstsize(t_file *lst);
void			ft_lstclear(t_file **lst);
char			*ft_strdup(char *str);
int				ft_strcmp(char *str1, char *str2);
void			clear_parse(t_parse *parse);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
char			**str_ds_dup(char **str);
void			free_ds(char **map);
int				find(char c);
void			init_parsing(t_parsing *parsing);
int				check_textures(t_parsing *global);

#endif
