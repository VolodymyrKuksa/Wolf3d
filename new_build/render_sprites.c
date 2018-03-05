/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 11:48:51 by vkuksa            #+#    #+#             */
/*   Updated: 2018/02/26 11:48:53 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "mlx.h"
#include "colors.h"
#include <math.h>

void	find_dist(t_player p, t_sprite *spr, int nbspr)
{
	int		i;
	double	dx;
	double	dy;

	i = -1;
	while (++i < nbspr)
	{
		dx = spr[i].pos.x - p.pos.x;
		dy = spr[i].pos.y - p.pos.y;
		spr[i].dist = sqrt(dx * dx + dy * dy);
		spr[i].angle = (dx * p.dir.x + dy * p.dir.y) / spr[i].dist;
		spr[i].l_angle = (dx * p.l_dir.x + dy * p.l_dir.y) / spr[i].dist;
		spr[i].l_angle = RTD(acos(spr[i].l_angle));
		spr[i].angle = RTD(acos(spr[i].angle));
		spr[i].view = (spr[i].angle <= 40 ? 1 : 0);
		if (spr[i].view)
			spr[i].dist *= cos(DTR(spr[i].angle));
	}
}

void	sort_by_dist(t_sprite *spr, int *ind, int nbspr)
{
	int		i;
	int		tmp;

	i = -1;
	while (++i < nbspr - 1)
	{
		if (spr[ind[i]].dist < spr[ind[i + 1]].dist)
		{
			tmp = ind[i];
			ind[i] = ind[i + 1];
			ind[i + 1] = tmp;
			i = -1;
		}
	}
}

void	texture_sprite(int i, int maxi, t_mlx *mlx, t_sprite spr)
{
	t_dpt	sc;
	double	d;
	int		j;

	d = (double)TS / spr.dim;
	sc.x = 0;
	while (++i <= maxi)
	{
		if (i >= 0 && i < WNDW)
		{
			sc.y = 0;
			j = WNDH_H - spr.dim / 2 - 1;
			while (++j < WNDH_H + spr.dim / 2)
			{
				if (spr.dist < mlx->zbuff[i] && j >= 0 && j < WNDH
				&& mlx->sprites[spr.id].addr[img_coord(sc.x, sc.y,
				&mlx->sprites[spr.id])] != SPR_BACK)
					mlx->img->addr[img_coord(i, j, mlx->img)] =
					mlx->sprites[spr.id].addr[img_coord(sc.x,
					sc.y, &mlx->sprites[spr.id])] + spr.dark;
				sc.y += d;
			}
		}
		sc.x += d;
	}
}

void	draw_sprite(t_sprite spr, t_mlx *mlx)
{
	int		i;
	int		maxi;

	if (!spr.view || spr.dist < 20 || spr.collected)
		return ;
	spr.dim = (double)TS / spr.dist * PPD + 0.5;
	i = PPD * tan(DTR(spr.angle));
	i = WNDW_H + (spr.l_angle > 40 ? i : -i) - spr.dim / 2 - 0.5;
	maxi = i + spr.dim + 1;
	spr.dark = darken(spr.dist);
	texture_sprite(i, maxi, mlx, spr);
}

void	render_sprites(t_mlx *mlx)
{
	int		ind[mlx->map->nbspr];
	int		i;

	find_dist(*mlx->pl, mlx->map->spr, mlx->map->nbspr);
	i = -1;
	while (++i < mlx->map->nbspr)
		ind[i] = i;
	sort_by_dist(mlx->map->spr, ind, mlx->map->nbspr);
	i = -1;
	while (++i < mlx->map->nbspr)
	{
		if (mlx->map->spr[ind[i]].view)
			draw_sprite(mlx->map->spr[ind[i]], mlx);
	}
}
