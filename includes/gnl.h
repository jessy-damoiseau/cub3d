/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 17:39:36 by jessy             #+#    #+#             */
/*   Updated: 2020/12/01 17:48:01 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>


typedef struct  s_gnl
{
    int     c;
    void    *next;
}               t_gnl;

int         gnl(int fd, char **line);
size_t		ft_strlen(const char *s);
void		*ft_memmove(void *dst, const void *src, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
int			check_return(char *str);
char	    *get_next_str(char *str);
char	    *get_line_return(char *str);

#endif
