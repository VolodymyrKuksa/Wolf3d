/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 18:18:37 by vkuksa            #+#    #+#             */
/*   Updated: 2018/02/28 18:18:38 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>

int		diagonal_collision_check(int x, int y, t_map *m)
{
	t_ipt	mc;

	mc.x = (x + 7) / TS;
	mc.y = (y + 7) / TS;
	if (m->arr[map_coord(mc.x, mc.y, m)])
		return (0);
	mc.x = (x + 7) / TS;
	mc.y = (y - 7) / TS;
	if (m->arr[map_coord(mc.x, mc.y, m)])
		return (0);
	mc.x = (x - 7) / TS;
	mc.y = (y - 7) / TS;
	if (m->arr[map_coord(mc.x, mc.y, m)])
		return (0);
	mc.x = (x - 7) / TS;
	mc.y = (y + 7) / TS;
	if (m->arr[map_coord(mc.x, mc.y, m)])
		return (0);
	return (1);
}

void	collect_sprite(t_player *pl, t_sprite *spr)
{
	if (spr->collected)
		return ;
	pl->gold += spr->gold;
	spr->collected = 1;
}

int		sprite_collision_check(int x, int y, t_map *m, t_player *pl)
{
	t_dpt	vec;
	int		j;

	j = -1;
	while (++j < m->nbspr)
	{
		vec.x = m->spr[j].pos.x - x;
		vec.y = m->spr[j].pos.y - y;
		if (ABS(vec.x) < 25 && ABS(vec.y) < 25 && !m->spr[j].walkable)
			return (0);
		else if (ABS(vec.x) < 25 && ABS(vec.y) < 25 && m->spr[j].collectable)
			collect_sprite(pl, &(m->spr[j]));
	}
	return (1);
}

int		collision_check(int x, int y, t_map *m, t_player *pl)
{
	t_ipt	mc;

	mc.x = (x + 10) / TS;
	mc.y = y / TS;
	if (m->arr[map_coord(mc.x, mc.y, m)])
		return (0);
	mc.x = (x - 10) / TS;
	mc.y = y / TS;
	if (m->arr[map_coord(mc.x, mc.y, m)])
		return (0);
	mc.x = x / TS;
	mc.y = (y + 10) / TS;
	if (m->arr[map_coord(mc.x, mc.y, m)])
		return (0);
	mc.x = x / TS;
	mc.y = (y - 10) / TS;
	if (m->arr[map_coord(mc.x, mc.y, m)])
		return (0);
	if (diagonal_collision_check(x, y, m))
		return (sprite_collision_check(x, y, m, pl));
	return (0);
}
