/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 13:05:29 by vkuksa            #+#    #+#             */
/*   Updated: 2018/02/22 13:05:32 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "key.h"
#include <stdio.h>//

// void	keypress_event(int key, t_mlx *mlx)
// {
// 	int silence_error;

// 	silence_error = mlx->mapcount;
// 	printf("key: %d\n", key);
// }

int		key_down(int key, void *data)
{
	// printf("key: %d\n", key);
	if (key == U_ARROW && !((t_mlx*)data)->keys.d_arrow)
		((t_mlx*)data)->keys.u_arrow = 1;
	else if (key == D_ARROW && !((t_mlx*)data)->keys.u_arrow)
		((t_mlx*)data)->keys.d_arrow = 1;
	else if (key == L_ARROW)
		((t_mlx*)data)->keys.l_arrow = 1;
	else if (key == R_ARROW)
		((t_mlx*)data)->keys.r_arrow = 1;
	else if (key == SP)
		((t_mlx*)data)->keys.sp = 1;
	// else
	// 	keypress_event(key, ((t_mlx*)data));
	return (0);
}

int		key_up(int key, void *data)
{
	if (key == U_ARROW)
		((t_mlx*)data)->keys.u_arrow = 0;
	else if (key == D_ARROW)
		((t_mlx*)data)->keys.d_arrow = 0;
	else if (key == L_ARROW)
		((t_mlx*)data)->keys.l_arrow = 0;
	else if (key == R_ARROW)
		((t_mlx*)data)->keys.r_arrow = 0;
	else if (key == SP)
		((t_mlx*)data)->keys.sp = 0;
	return (0);
}
