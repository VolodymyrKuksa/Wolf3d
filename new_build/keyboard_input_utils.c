/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_input_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 14:05:15 by vkuksa            #+#    #+#             */
/*   Updated: 2018/03/05 14:07:21 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	enter_key(t_mlx *mlx)
{
	if (mlx->pl->endlvl && mlx->mapid < mlx->mapcount - 1)
	{
		mlx->mapid += 1;
		mlx->map = mlx->allmaps[mlx->mapid];
		mlx->pl->endlvl = 0;
	}
	mlx->menu = 0;
}
