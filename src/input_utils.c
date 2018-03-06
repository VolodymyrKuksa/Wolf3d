/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 10:50:45 by vkuksa            #+#    #+#             */
/*   Updated: 2018/03/06 10:50:50 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdlib.h>

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

int		mouse_kill(void)
{
	exit(0);
}
