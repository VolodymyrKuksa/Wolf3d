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
// #include <pthread.h>
#include <math.h>
#include <stdio.h>//

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
	r->len.x = sqrt(dx * dx + dy * dy);
	if (r->endx.y < 0 || r->endx.y > map->height * TS)
		r->len.x = -1;
	r->len.x *= r->distortion;
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
	r->len.y = sqrt(dx * dx + dy * dy);
	if (r->endy.x < 0 || r->endy.x > map->width * TS)
		r->len.y = -1;
	r->len.y *= r->distortion;
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
		if ((r.len.x < r.len.y && r.len.x > 0) || (r.len.x > 0 && r.len.y < 0))
			draw_wall(i, r.len.x, DARKBLUE, mlx->img);
		else if (r.len.y > 0)
			draw_wall(i, r.len.y, DARKRED, mlx->img);
		r.angle += r.d_angle;
		rotate(r.d_angle, &r.dir);
	}
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

// void	*render(void *t)
// {
// 	t_mlx	*mlx;
// 	t_ray	r;
// 	int		i;

// 	mlx = ((t_thread*)t)->mlx;
// 	r = ((t_thread*)t)->r;
// 	rotate(r.angle, &r.dir);
// 	i = -1;
// 	while (++i < WNDW_Q)
// 	{
// 		cast(&r, mlx->map);
// 		if ((r.len.x < r.len.y && r.len.x > 0) || (r.len.x > 0 && r.len.y < 0))
// 		{
// 			printf("yo1\n");
// 			draw_wall(((t_thread*)t)->s + i, r.len.x, DARKBLUE, mlx->img);
// 		}
// 		else if (r.len.y > 0)
// 		{
// 			printf("yo2\n");
// 			draw_wall(((t_thread*)t)->s + i, r.len.y, DARKRED, mlx->img);
// 		}
// 		r.angle += r.d_angle;
// 		rotate(r.d_angle, &r.dir);
// 	}
// 	pthread_exit(0);
// }

// void	draw_world(t_mlx *mlx)
// {
// 	pthread_t	tid[4];
// 	t_thread	trd[4];
// 	int			angle;
// 	int			i;
// 	int			s;

// 	angle = -30;
// 	s = 0;
// 	i = -1;
// 	while (++i < 4)
// 	{
// 		trd[i].mlx = mlx;
// 		trd[i].r.start.x = mlx->pl->pos.x;
// 		trd[i].r.start.y = mlx->pl->pos.y;
// 		trd[i].r.dir.x = mlx->pl->dir.x;
// 		trd[i].r.dir.y = mlx->pl->dir.y;
// 		trd[i].r.d_angle = (double)FOV / WNDW;
// 		trd[i].r.angle = angle;
// 		trd[i].s = s;
// 		s += WNDW_Q;
// 		angle += 15;
// 		pthread_create(&tid[i], NULL, render, &trd[i]);
// 	}
// 	while (--i >= 0)
// 		pthread_join(tid[i], NULL);
// }
