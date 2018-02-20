/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 18:18:02 by vkuksa            #+#    #+#             */
/*   Updated: 2018/02/18 18:18:05 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key.h"
#include "wolf.h"
#include "mlx.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

t_mlx		mlx;
t_map		map;
t_player	player;

int		map_coord(int y, int x)
{
	return (y * map.width + x);
}

int		img_coord(int y, int x)
{
	t_image		*p;

	p = mlx.img;
	return (y * p->width + x);
}

void	map_init(void)
{
	map.width = 25;
	map.height = 25;
	map.arr = (int*)malloc(sizeof(int*) * map.height * map.width);
	for (int i = 0; i < map.height; i++)
	{
		for (int j = 0; j < map.width; j++)
		{
			map.arr[map_coord(i, j)] = 0;
			if (i == 0 || i == map.height - 1 || j == 0 || j == map.width - 1 || i == 2 * j)
				map.arr[map_coord(i, j)] = 1;
			if (i >= 2 && i <= 5 && j == 2)
				map.arr[map_coord(i, j)] = 1;
			if (i != 4 && j == 6)
				map.arr[map_coord(i, j)] = 1;
		}
	}
}

void	player_init(void)
{
	player.pos.x = (double)map.width / 2 * TS;
	player.pos.y = (double)map.height / 2 * TS;
	player.dir.x = 1;
	player.dir.y = 0;
	player.movespd = 10;
	player.turnspd = 5;
	player.d_move.x = player.movespd * player.dir.x;
	player.d_move.y = player.movespd * player.dir.y;
}

void	image_init(void)
{
	t_image		*p;

	p = (t_image*)malloc(sizeof(t_image));
	p->width = WNDW;
	p->height = WNDH;
	p->img = mlx_new_image(mlx.mlx, p->width, p->height);
	p->addr = (int*)mlx_get_data_addr(p->img, &p->bpp, &p->sl, &p->ed);
	p->sl /= 4;
	mlx.img = p;
}

void	rotate(double d, t_dpt *pt)
{
	t_dpt	tmp;

	tmp.x = pt->x;
	tmp.y = pt->y;
	pt->x = tmp.x * cos(DTR(d)) - tmp.y * sin(DTR(d));
	pt->y = tmp.y * cos(DTR(d)) + tmp.x * sin(DTR(d));
}

void	move_player(int d)
{
	t_dpt	tmp;

	tmp.x = player.pos.x + player.d_move.x * d;
	tmp.y = player.pos.y + player.d_move.y * d;

	// if (tmp.x > -WNDW_H + 40 && tmp.x < WNDW_H - 40)
		player.pos.x = tmp.x;
	// if (tmp.y > -WNDH_H + 40 && tmp.y < WNDH_H - 40)
		player.pos.y = tmp.y;
}

void	clear_image(t_image *img)
{
	int		i;
	int		len;

	len = img->width * img->height;
	i = -1;
	while (++i < len)
		img->addr[i] = 0;
}

int		intersect(int h, t_ray r)
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
	return (map.arr[map_coord(y, x)]);
}

void	find_len_x(t_ray *r)
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
	while (++i < 100 && !intersect(1, *r))
	{
		r->endx.x += dx;
		r->endx.y += dy;
	}
	dx = r->endx.x - r->start.x;
	dy = r->endx.y - r->start.y;
	r->len.x = sqrt(dx * dx + dy * dy);
	if (r->endx.y < 0 || r->endx.y > map.height * TS)
		r->len.x = -1;
	r->len.x *= r->distortion;
}

void	find_len_y(t_ray *r)
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
	while (++i < 100 && !intersect(0, *r))
	{
		r->endy.x += dx;
		r->endy.y += dy;
	}
	dx = r->endy.x - r->start.x;
	dy = r->endy.y - r->start.y;
	r->len.y = sqrt(dx * dx + dy * dy);
	if (r->endy.x < 0 || r->endy.x > map.width * TS)
		r->len.y = -1;
	r->len.y *= r->distortion;
}

void	cast(t_ray *r)
{
	r->distortion = cos(DTR(r->angle));
	if (r->dir.x)
		find_len_x(r);
	if (r->dir.y)
		find_len_y(r);
}

void	draw_wall(int j, double dist, int col)
{
	t_image		*p;
	int			height;
	int			i;

	p = mlx.img;
	height = (double)TS / dist * PPD + 0.5;
	i = -1;
	while (++i < WNDH)
	{
		if (i < WNDH_H - height / 2)
			p->addr[img_coord(i, j)] = DARKGREY;
		else if (i > WNDH_H + height / 2)
			p->addr[img_coord(i, j)] = DULLGREY;
		else
			p->addr[img_coord(i, j)] = col;
	}
}

void	render(void)
{
	t_image		*p;
	t_ray		r;
	int			i;

	p = mlx.img;
	clear_image(p);
	r.start.x = player.pos.x;
	r.start.y = player.pos.y;
	r.dir.x = player.dir.x;
	r.dir.y = player.dir.y;
	r.d_angle = (double)FOV / WNDW;
	r.angle = -30;
	rotate(-30, &r.dir);
	i = -1;
	while (++i < WNDW)
	{
		cast(&r);
		if ((r.len.x < r.len.y && r.len.x > 0) || (r.len.x > 0 && r.len.y < 0))
			draw_wall(i, r.len.x, DARKBLUE);
		else if (r.len.y > 0)
			draw_wall(i, r.len.y, DARKRED);
		r.angle += r.d_angle;
		rotate(r.d_angle, &r.dir);
	}
	mlx_put_image_to_window(mlx.mlx, mlx.wnd, mlx.img->img, 0, 0);
}

int		key_input(int key, void *null)
{
	if (key == R_ARROW)
	{
		rotate(player.turnspd, &player.dir);
		player.d_move.x = player.movespd * player.dir.x;
		player.d_move.y = player.movespd * player.dir.y;
	}
	else if (key == L_ARROW)
	{
		rotate(-player.turnspd, &player.dir);
		player.d_move.x = player.movespd * player.dir.x;
		player.d_move.y = player.movespd * player.dir.y;
	}
	else if (key == U_ARROW)
		move_player(1);
	else if (key == D_ARROW)
		move_player(-1);
	else
		return (0);
	render();
	return (0);
}

int		main(void)
{
	map_init();
	player_init();
	mlx.mlx = mlx_init();
	mlx.wnd = mlx_new_window(mlx.mlx, WNDW, WNDH, "Wolf3d");
	image_init();
	render();
	mlx_hook(mlx.wnd, 2, 5, key_input, NULL);
	mlx_loop(mlx.mlx);
	return (0);
}
