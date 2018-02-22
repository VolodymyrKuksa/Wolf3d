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
#include <stdio.h>

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

void	draw_ceiling(int i, int j, t_image *p)
{
	int		k;

	k = -1;
	while (++k <= i)
		p->addr[img_coord(j, k, p)] = DULLGREY;
}

int		darken(int len)
{
	int		alpha;

	if (len < 150)
		return (0);
	else if (len > 1150)
		return (0xdd000000);
	len -= 150;
	alpha = len * 0xde / 2000;
	return (alpha << 24);
}

void	draw_wall_x(int j, t_ray *r, t_image *p, t_image *t)
{
	int			height;
	int			i;
	double		ty;
	double		d_ty;

	ty = 0;
	height = (double)TS / r->len.x * PPD + 0.5;
	d_ty = (double)TS / height;
	i = WNDH_H - height / 2 - 1;

	if (i > 0)
		draw_ceiling(i, j, p);
	while (++i < WNDH)
	{
		if (i >= WNDH_H + height / 2)
			p->addr[img_coord(j, i, p)] = DARKGREY;
		if (i > 0 && i < WNDH_H + height / 2)
		{
			p->addr[img_coord(j, i, p)] =
			t->addr[img_coord(r->tex_row.x, (int)ty, t)] + darken(r->len.x);
		}
		ty += d_ty;
	}
}

void	draw_wall_y(int j, t_ray *r, t_image *p, t_image *t)
{
	int			height;
	int			i;
	double		ty;
	double		d_ty;

	ty = 0;
	height = (double)TS / r->len.y * PPD + 0.5;
	d_ty = (double)TS / height;
	i = WNDH_H - height / 2 - 1;

	if (i > 0)
		draw_ceiling(i, j, p);
	while (++i < WNDH)
	{
		if (i >= WNDH_H + height / 2)
			p->addr[img_coord(j, i, p)] = DARKGREY;
		if (i > 0 && i < WNDH_H + height / 2)
		{
			p->addr[img_coord(j, i, p)] =
			t->addr[img_coord(r->tex_row.y, (int)ty, t)]  + darken(r->len.y);
		}
		ty += d_ty;
	}
}










// void	draw_wall(int j, double dist, int col, t_image *p)
// {
// 	int			height;
// 	int			i;

// 	height = (double)TS / dist * PPD + 0.5;
// 	i = -1;
// 	while (++i < WNDH)
// 	{
// 		if (i < WNDH_H - height / 2)
// 			p->addr[img_coord(j, i, p)] = DARKGREY;
// 		else if (i > WNDH_H + height / 2)
// 			p->addr[img_coord(j, i, p)] = DULLGREY;
// 		else
// 			p->addr[img_coord(j, i, p)] = col;
// 	}
// }
