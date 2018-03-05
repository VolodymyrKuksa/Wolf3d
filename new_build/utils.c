/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:03:13 by vkuksa            #+#    #+#             */
/*   Updated: 2018/02/21 14:03:15 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf.h"
#include <math.h>

void	rotate(double d, t_dpt *pt)
{
	t_dpt	tmp;

	tmp.x = pt->x;
	tmp.y = pt->y;
	pt->x = tmp.x * cos(DTR(d)) - tmp.y * sin(DTR(d));
	pt->y = tmp.y * cos(DTR(d)) + tmp.x * sin(DTR(d));
}

int		is_all_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != '-')
			return (0);
		str++;
	}
	return (1);
}

void	reset_player(t_mlx *mlx)
{
	mlx->pl->pos.x = mlx->map->p_pos.x * TS + TS / 2;
	mlx->pl->pos.y = mlx->map->p_pos.y * TS + TS / 2;
	mlx->pl->dir.x = mlx->map->p_dir.x;
	mlx->pl->dir.y = mlx->map->p_dir.y;
	mlx->pl->l_dir.x = mlx->map->p_dir.x;
	mlx->pl->l_dir.y = mlx->map->p_dir.y;
	rotate(-40, &mlx->pl->l_dir);
	mlx->pl->d_move.x = mlx->pl->dir.x * mlx->pl->movespd;
	mlx->pl->d_move.y = mlx->pl->dir.y * mlx->pl->movespd;
	mlx->pl->gold = 0;
	mlx->pl->endlvl = 0;
}

void	reset_sprites(t_mlx *mlx)
{
	int			i;
	t_sprite	*tmp;

	mlx->map->ts = 0;
	i = -1;
	while (++i < mlx->map->nbspr)
	{
		tmp = &(mlx->map->spr[i]);
		tmp->collectable = (tmp->id < 10 ? 0 : 1);
		if (tmp->collectable && tmp->id < 14)
		{
			tmp->gold = tmp->id % 9 * 10;
			mlx->map->ts += tmp->gold;
		}
		tmp->collected = 0;
	}
}

void	reset_map(t_map *map)
{
	int		i;
	int		maxi;

	if (map->arr)
		free(map->arr);
	if (map->scr)
		free(map->scr);
	map->arr = new_map_array(map);
	map->scr = new_map_array(map);
	maxi = map->height * map->width;
	i = -1;
	while (++i < maxi)
	{
		map->arr[i] = ABS(map->orig[i]);
		map->scr[i] = (map->orig[i] > 0 ? map->orig[i] : 0);
	}
}
