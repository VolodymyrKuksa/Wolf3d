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
#include <math.h>

int		darken(int len)
{
	int		alpha;

	alpha = len * 227.0 / 1250;
	if (alpha > 227)
		return (0xe3000000);
	return (alpha << 24);
}

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
	if (y < 0 || x < 0 || y >= map->height || x >= map->width)
		return (1);
	return (map->arr[map_coord(x, y, map)]);
}

void	floor_cast(int j, t_mlx *mlx, t_ray r)
{
	int			i;
	double		dist;
	t_ipt		tc;
	t_image		*texf;
	t_image		*texc;

	texf = &mlx->textures[mlx->map->floor];
	texc = &mlx->textures[mlx->map->ceiling];
	if ((r.len.x < r.len.y && r.len.x > 3) || (r.len.x > 3 && r.len.y < 3))
		i = WNDH_H + ((double)TS / r.len.x * PPD + 0.5) / 2 - 1;
	else if (r.len.y > 3)
		i = WNDH_H + ((double)TS / r.len.y * PPD + 0.5) / 2 - 1;
	else
		return ;
	while (++i < WNDH)
	{
		dist = (double)TS_H / (i - WNDH_H) * PPD / cos(DTR(r.angle));
		tc.x = (int)(r.dir.x * dist + mlx->pl->pos.x) % TS + 0.5;
		tc.y = (int)(r.dir.y * dist + mlx->pl->pos.y) % TS + 0.5;
		mlx->img->addr[img_coord(j, i, mlx->img)] =
		texf->addr[img_coord(tc.x, tc.y, texf)] + darken(dist);
		mlx->img->addr[img_coord(j, ABS(i - WNDH), mlx->img)] =
		texc->addr[img_coord(tc.x, tc.y, texc)] + darken(dist);
	}
}

void	draw_wall_x(int j, t_ray *r, t_image *p, t_image *t)
{
	int			height;
	int			i;
	double		ty;
	double		d_ty;
	int			dark;

	ty = 0;
	height = (double)TS / r->len.x * PPD + 0.5;
	d_ty = (double)TS / height;
	dark = darken(r->len.x);
	i = WNDH_H - height / 2 - 1;
	while (++i < WNDH)
	{
		if (i > 0 && i < WNDH_H + height / 2)
		{
			p->addr[img_coord(j, i, p)] =
			t->addr[img_coord(r->tex_row.x, (int)ty, t)] + dark;
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
	int			dark;

	ty = 0;
	height = (double)TS / r->len.y * PPD + 0.5;
	d_ty = (double)TS / height;
	dark = darken(r->len.y);
	i = WNDH_H - height / 2 - 1;
	while (++i < WNDH)
	{
		if (i > 0 && i < WNDH_H + height / 2)
		{
			p->addr[img_coord(j, i, p)] =
			t->addr[img_coord(r->tex_row.y, (int)ty, t)] + dark;
		}
		ty += d_ty;
	}
}
