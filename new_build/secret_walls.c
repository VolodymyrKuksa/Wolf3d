/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secret_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 11:38:23 by vkuksa            #+#    #+#             */
/*   Updated: 2018/03/05 11:38:25 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	uncover(int x, int y, t_map *m)
{
	m->arr[map_coord(x, y, m)] = 0;
	if (m->arr[map_coord(x + 1, y, m)] != m->scr[map_coord(x + 1, y, m)])
		uncover(x + 1, y, m);
	if (m->arr[map_coord(x - 1, y, m)] != m->scr[map_coord(x - 1, y, m)])
		uncover(x - 1, y, m);
	if (m->arr[map_coord(x, y + 1, m)] != m->scr[map_coord(x, y + 1, m)])
		uncover(x, y + 1, m);
	if (m->arr[map_coord(x, y - 1, m)] != m->scr[map_coord(x, y - 1, m)])
		uncover(x, y - 1, m);
}

void	check_secret(t_mlx *mlx)
{
	int		x;
	int		y;

	x = (mlx->pl->pos.x + mlx->pl->dir.x * TS) / TS;
	y = (mlx->pl->pos.y + mlx->pl->dir.y * TS) / TS;
	if (mlx->map->arr[map_coord(x, y, mlx->map)]
	!= mlx->map->scr[map_coord(x, y, mlx->map)])
		uncover(x, y, mlx->map);
}
