/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:23:39 by vkuksa            #+#    #+#             */
/*   Updated: 2018/03/02 16:23:41 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>

void	put_dot_d(t_dpt pt, int col, t_image *m)
{
	if (pt.x > 0 && pt.x < m->width - 1 && pt.y > 0 && pt.y < m->height - 1)
		m->addr[img_coord(pt.x, pt.y, m)] = col;
}

void	put_dot_i(t_ipt pt, int col, t_image *m)
{
	if (pt.x > 0 && pt.x < m->width - 1 && pt.y > 0 && pt.y < m->height - 1)
		m->addr[img_coord(pt.x, pt.y, m)] = col;
}

void	plot_line_x(t_dpt a, t_dpt b, int col, t_image *m)
{
	t_dpt	pt;
	double	diffy;

	pt.x = a.x;
	pt.y = a.y;
	diffy = ((b.y - a.y) / (b.x - a.x));
	diffy = (b.x - a.x > 0 ? diffy : -diffy);
	while (floor(pt.x) != floor(b.x))
	{
		put_dot_d(pt, col, m);
		pt.x += (a.x < b.x ? 1 : -1);
		pt.y += diffy;
	}
	put_dot_d(b, col, m);
}

void	plot_line_y(t_dpt a, t_dpt b, int col, t_image *m)
{
	t_dpt	pt;
	double	diffx;

	pt.x = a.x;
	pt.y = a.y;
	diffx = ((b.x - a.x) / (b.y - a.y));
	diffx = (b.y - a.y > 0 ? diffx : -diffx);
	while (floor(pt.y) != floor(b.y))
	{
		put_dot_d(pt, col, m);
		pt.y += (a.y < b.y ? 1 : -1);
		pt.x += diffx;
	}
	put_dot_d(b, col, m);
}

void	draw_line_img(t_dpt a, t_dpt b, int col, t_image *m)
{
	double	dx;
	double	dy;

	dx = ABS(b.x - a.x);
	dy = ABS(b.y - a.y);
	if (dx < 1 && dy < 1)
	{
		put_dot_d(a, col, m);
		put_dot_d(b, col, m);
	}
	else if (dx > dy)
		plot_line_x(a, b, col, m);
	else
		plot_line_y(a, b, col, m);
}
