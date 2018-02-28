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
#include <stdio.h>

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
		if (!ft_isdigit(*str))
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
}
