/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 23:28:37 by user42            #+#    #+#             */
/*   Updated: 2021/05/04 23:28:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (s1[i] != s2[i])
		return (1);
	return (0);
}

int		lst_size(t_file *lst, t_psing *psing)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (len(lst->line) > psing->parse.len_map)
			psing->parse.len_map = len(lst->line);
		lst = lst->next;
		i++;
	}
	return (i);
}

void	lstclear(t_file **lst)
{
	t_file	*now_lst;

	while (*lst)
	{
		free((*lst)->line);
		now_lst = *lst;
		*lst = now_lst->next;
		free(now_lst);
	}
	lst = 0;
}

t_file	*lstnew(char *content)
{
	t_file	*n;

	if (!(n = (t_file *)malloc(sizeof(*n))))
		return (0);
	if (content)
		n->line = content;
	else
		n->line = 0;
	n->next = 0;
	return (n);
}

void	lstadd_back(t_file **alst, t_file *new)
{
	t_file	*lst;

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
