/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdamoise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:47:11 by jdamoise          #+#    #+#             */
/*   Updated: 2021/02/23 19:42:42 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_file	*ft_lstnew(char *content)
{
	t_file	*n;
	int		i;

	i = 0;
	if (!(n = (t_file *)malloc(sizeof(*n))))
		return (0);
	if (content)
	{
		while (content[i])
			i++;
		n->line = content;
	}
	else
		n->line = 0;
	n->next = 0;
	return (n);
}

void	ft_lstadd_back(t_file **alst, t_file *new)
{
	t_file *lst;

	if (alst)
	{
		if (*alst == 0)
			*alst = new;
		else
		{
			lst = *alst;
			while (lst->next)
				lst = lst->next;
			lst->next = new;
		}
	}
}

int		ft_lstsize(t_file *lst)
{
	unsigned int i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	ft_lstclear(t_file **lst)
{
	t_file *now_list;

	while (*lst)
	{
		free((*lst)->line);
		now_list = *lst;
		*lst = now_list->next;
		free(now_list);
	}
	lst = 0;
}
