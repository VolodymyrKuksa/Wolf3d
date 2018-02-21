/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 18:30:51 by vkuksa            #+#    #+#             */
/*   Updated: 2018/02/21 18:30:52 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		intersect(int h, t_ray r, t_map *map)
{
	int		x;
	int		y;

	if (h)
	{
		y = (int)(r.endx.y) / TS;
		x = (int)(r.endx.x + (r.dir.x > 0 ? 1 : -1)) / TS;
	}
	else
	{
		y = (int)(r.endy.y + (r.dir.y > 0 ? 1 : -1)) / TS;
		x = (int)(r.endy.x) / TS;
	}
	if (y < 0 || x < 0)
		return (1);
	return (map->arr[map_coord(x, y, map)]);
}

void	draw_wall(int j, double dist, int col, t_image *p)
{
	int			height;
	int			i;

	height = (double)TS / dist * PPD + 0.5;
	i = -1;
	while (++i < WNDH)
	{
		if (i < WNDH_H - height / 2)
			p->addr[img_coord(j, i, p)] = DARKGREY;
		else if (i > WNDH_H + height / 2)
			p->addr[img_coord(j, i, p)] = DULLGREY;
		else
			p->addr[img_coord(j, i, p)] = col;
	}
}
