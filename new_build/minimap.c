/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 09:18:05 by vkuksa            #+#    #+#             */
/*   Updated: 2018/03/02 09:18:07 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "colors.h"

void	mm_view(int i, t_ray r, t_image *m)
{
	static t_dpt	prev;
	t_dpt			pt;

	if ((r.len.x < r.len.y && r.len.x > 3) || (r.len.x > 3 && r.len.y < 3))
	{
		pt.x = (r.endx.x - r.start.x) / MM_MAGN + MM_SIZE_H;
		pt.y = (r.endx.y - r.start.y) / MM_MAGN + MM_SIZE_H;
	}
	else
	{
		pt.x = (r.endy.x - r.start.x) / MM_MAGN + MM_SIZE_H;
		pt.y = (r.endy.y - r.start.y) / MM_MAGN + MM_SIZE_H;
	}
	if (i == 0 || i == WNDW - 1)
	{
		pt.x = MM_SIZE_H;
		pt.y = MM_SIZE_H;
		draw_line_img(prev, pt, YELLOW, m);
	}
	else
		draw_line_img(prev, pt, YELLOW, m);
	prev.x = pt.x;
	prev.y = pt.y;
}

void	mm_walls(t_ipt pl, t_map *map, t_image *m)
{
	t_ipt	ic;
	t_ipt	mc;

	ic.y = -1;
	while (++ic.y < m->height)
	{
		ic.x = -1;
		while (++ic.x < m->width)
		{
			mc.x = (int)(pl.x + (-MM_SIZE_H + ic.x) * MM_MAGN) / TS;
			mc.y = (int)(pl.y + (-MM_SIZE_H + ic.y) * MM_MAGN) / TS;
			if (mc.x >= 0 && mc.x < map->width && mc.y >= 0
			&& mc.y < map->height && map->arr[map_coord(mc.x, mc.y, map)])
				m->addr[img_coord(ic.x, ic.y, m)] = MM_WALLCOL;
			if (mc.x < 0 || mc.x >= map->width || mc.y < 0
			|| mc.y >= map->height)
				m->addr[img_coord(ic.x, ic.y, m)] = MM_WALLCOL;
			if (ic.x == 0 || ic.x == m->width - 1 ||
			ic.y == 0 || ic.y == m->height - 1)
				m->addr[img_coord(ic.x, ic.y, m)] = WHITE;
			if (ic.x >= MM_SIZE_H - 2 && ic.x <= MM_SIZE_H + 2
			&& ic.y >= MM_SIZE_H - 2 && ic.y <= MM_SIZE_H + 2)
				put_dot_i(ic, YELLOW, m);
		}
	}
}
