/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 15:39:13 by user42            #+#    #+#             */
/*   Updated: 2021/04/28 15:40:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	init_parsing(t_parsing *parsing)
{
	int i;

	i = 0;
	parsing->parse.c = 0;
	parsing->parse.ea = 0;
	parsing->parse.f = 0;
	parsing->parse.map = 0;
	parsing->parse.nb_param_fill = 0;
	parsing->parse.no = 0;
	parsing->parse.r = 0;
	parsing->parse.s = 0;
	parsing->parse.so = 0;
	parsing->parse.we = 0;
	parsing->value.rx = 0;
	parsing->value.ry = 0;
	while (i < 3)
	{
		parsing->value.floor[i] = 0;
		parsing->value.sky[i++] = 0;
	}
}
