/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 18:33:15 by vkuksa            #+#    #+#             */
/*   Updated: 2018/02/21 18:33:17 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "mlx.h"
#include <math.h>

void	find_len_x(t_ray *r, t_map *map)
{
	double	dy;
	double	dx;
	int		i;

	dx = (r->dir.x > 0 ? TS : 0) - (int)r->start.x % TS;
	dy = dx / r->dir.x * r->dir.y;
	r->endx.x = r->start.x + dx;
	r->endx.y = r->start.y + dy;
	dx = (r->dir.x > 0 ? TS : -TS);
	dy = dx / r->dir.x * r->dir.y;
	i = -1;
	while (++i < 100 && !intersect(1, *r, map))
	{
		r->endx.x += dx;
		r->endx.y += dy;
	}
	dx = r->endx.x - r->start.x;
	dy = r->endx.y - r->start.y;
	r->len.x = sqrt(dx * dx + dy * dy) * r->distortion;
	if (r->endx.y < 0 || r->endx.y > map->height * TS)
		r->len.x = -1;
	r->tex_id.x = get_texture_id(1, r, map);
	r->tex_row.x = (int)r->endx.y % TS;
	if (r->dir.x < 0)
		r->tex_row.x = TS - 1 - r->tex_row.x;
}

void	find_len_y(t_ray *r, t_map *map)
{
	double	dy;
	double	dx;
	int		i;

	dy = (r->dir.y > 0 ? TS : 0) - (int)r->start.y % TS;
	dx = dy / r->dir.y * r->dir.x;
	r->endy.x = r->start.x + dx;
	r->endy.y = r->start.y + dy;
	dy = (r->dir.y > 0 ? TS : -TS);
	dx = dy / r->dir.y * r->dir.x;
	i = -1;
	while (++i < 100 && !intersect(0, *r, map))
	{
		r->endy.x += dx;
		r->endy.y += dy;
	}
	dx = r->endy.x - r->start.x;
	dy = r->endy.y - r->start.y;
	r->len.y = sqrt(dx * dx + dy * dy) * r->distortion;
	if (r->endy.x < 0 || r->endy.x > map->width * TS)
		r->len.y = -1;
	r->tex_id.y = get_texture_id(0, r, map);
	r->tex_row.y = (int)r->endy.x % TS;
	if (r->dir.y > 0)
		r->tex_row.y = TS - 1 - r->tex_row.y;
}

void	cast(t_ray *r, t_map *map)
{
	r->distortion = cos(DTR(r->angle));
	if (r->dir.x)
		find_len_x(r, map);
	if (r->dir.y)
		find_len_y(r, map);
}

void	render(t_mlx *mlx, t_ray r)
{
	int		i;

	rotate(r.angle, &r.dir);
	i = -1;
	while (++i < WNDW)
	{
		cast(&r, mlx->map);
		floor_cast(i, mlx, r);
		if ((r.len.x < r.len.y && r.len.x > 3) || (r.len.x > 3 && r.len.y < 3))
		{
			mlx->zbuff[i] = r.len.x;
			draw_wall_x(i, &r, mlx->img, &mlx->textures[r.tex_id.x]);
		}
		else if (r.len.y > 3)
		{
			mlx->zbuff[i] = r.len.y;
			draw_wall_y(i, &r, mlx->img, &mlx->textures[r.tex_id.y]);
		}
		if (mlx->show_mm)
			mm_view(r, mlx->mm);
		r.angle += r.d_angle;
		rotate(r.d_angle, &r.dir);
	}
	mm_walls(mlx->pl->pos, mlx->map, mlx->mm);
	render_sprites(mlx);
}

void	draw_world(t_mlx *mlx)
{
	t_ray	r;

	r.start.x = mlx->pl->pos.x;
	r.start.y = mlx->pl->pos.y;
	r.dir.x = mlx->pl->dir.x;
	r.dir.y = mlx->pl->dir.y;
	r.d_angle = (double)FOV / WNDW;
	r.angle = -FOV_H;
	render(mlx, r);
}
