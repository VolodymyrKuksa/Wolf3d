/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 16:01:58 by vkuksa            #+#    #+#             */
/*   Updated: 2018/02/22 16:01:59 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	move_player(int d, t_player *pl, t_map *m)
{
	t_ipt	tmp;

	tmp.x = pl->pos.x + d * pl->d_move.x;
	tmp.y = pl->pos.y + d * pl->d_move.y;
	if (collision_check(tmp.x, pl->pos.y, m))
		pl->pos.x = tmp.x;
	if (collision_check(pl->pos.x, tmp.y, m))
		pl->pos.y = tmp.y;
}

void	turn_player(int left, t_player *pl)
{
	if (left)
	{
		rotate(-pl->turnspd, &pl->dir);
		rotate(-pl->turnspd, &pl->l_dir);
	}
	else
	{
		rotate(pl->turnspd, &pl->dir);
		rotate(pl->turnspd, &pl->l_dir);
	}
	pl->d_move.x = pl->dir.x * pl->movespd;
	pl->d_move.y = pl->dir.y * pl->movespd;
}

int		update(void *data)
{
	t_mlx	*mlx;

	mlx = (t_mlx*)data;
	if (!mlx->menu)
	{
		if (mlx->keys.l_arrow || mlx->keys.r_arrow)
			turn_player(mlx->keys.l_arrow, mlx->pl);
		if (mlx->keys.u_arrow || mlx->keys.d_arrow)
			move_player((mlx->keys.u_arrow == 1 ? 1 : -1), mlx->pl, mlx->map);
	}
	output(mlx);
	return (0);
}
