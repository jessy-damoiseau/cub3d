/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_sprite_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 22:20:12 by user42            #+#    #+#             */
/*   Updated: 2021/04/28 22:34:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_sprite    *lst_sprite(t_global *global)
{
    t_sprite *lst;
    if (!(lst = malloc(sizeof(t_sprite))))
        return (0);
    lst->mapx_sprite = global->calcul.mapX;
    lst->mapy_sprite = global->calcul.mapY;
    lst->sidedistx_sprite = global->calcul.sideDistX;
    lst->sidedisty_sprite = global->calcul.sideDistY;
    if (global->calcul.side)
        lst->spritedist = fabs(lst->mapx_sprite - global->constante.posX);
    else
        lst->spritedist = fabs(lst->mapx_sprite - global->constante.posX);
    lst->next = 0;
    return (lst);
}

void    lst_sprite_addfront(t_sprite **alst, t_sprite *new)
{
    new->next = *alst;
    *alst = new;
}