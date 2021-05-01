/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_sprite_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 22:20:12 by user42            #+#    #+#             */
/*   Updated: 2021/05/01 02:56:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_sprite    *lst_sprite(t_global *global)
{
    t_sprite *lst;
    
    if (!(lst = malloc(sizeof(t_sprite))))
        return (0);
    lst->mapx_sprite = global->calcul.mapx + 0.5;
    lst->mapy_sprite = global->calcul.mapy + 0.5;
    lst->sidedistx_sprite = global->calcul.sidedistx;
    lst->sidedisty_sprite = global->calcul.sidedisty;
    lst->side = global->calcul.side;
    lst->nbhit = 0;
    lst->spritedist = sqrt(pow((global->constante.posx - lst->mapx_sprite), 2) + pow((global->constante.posy - lst->mapy_sprite), 2));
    lst->lineheight = (int)(global->parsing.value.ry / lst->spritedist);
	lst->draws_start = -lst->lineheight / 2 + global->parsing.value.ry / 2;
	if(lst->draws_start < 0)
		lst->draws_start = 0;
	lst->draws_end = lst->lineheight / 2 + global->parsing.value.ry / 2;
	if(lst->draws_end >= global->parsing.value.ry)
		lst->draws_end = global->parsing.value.ry - 1;
    lst->next = 0;
    return (lst);
}

void    lst_sprite_addfront(t_sprite **alst, t_sprite *new)
{
    new->next = *alst;
    *alst = new;
}

void    lst_sclear(t_sprite **lst)
{ 
    t_sprite *now_list;

	while (*lst)
	{
		now_list = *lst;
		*lst = now_list->next;
		free(now_list);
	}
	lst = 0;  
}