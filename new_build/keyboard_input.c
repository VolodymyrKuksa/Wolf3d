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
#include <stdlib.h>

void	menu_controls(int key, t_mlx *mlx)
{
	if (key == ESC && mlx->pl->endlvl)
	{
		mlx->pl->endlvl = 0;
		reset_player(mlx);
		reset_sprites(mlx);
		reset_map(mlx->map);
	}
	else if (key == ESC && !mlx->menu)
		mlx->menu = 1;
	else if (key == ESC)
		exit(1);
	else if (key == ENTER && mlx->menu)
		enter_key(mlx);
	else if (mlx->menu && key == U_ARROW)
	{
		mlx->mapid -= 1;
		if (mlx->mapid < 0)
			mlx->mapid += mlx->mapcount;
		mlx->map = mlx->allmaps[mlx->mapid];
	}
	else if (mlx->menu && key == D_ARROW)
	{
		mlx->mapid = (mlx->mapid + 1) % mlx->mapcount;
		mlx->map = mlx->allmaps[mlx->mapid];
	}
}

void	keypress_event(int key, t_mlx *mlx)
{
	if (key == L_SHIFT && !mlx->keys.tilde)
	{
		mlx->pl->movespd = P_RUNSPD;
		mlx->pl->d_move.x = mlx->pl->dir.x * mlx->pl->movespd;
		mlx->pl->d_move.y = mlx->pl->dir.y * mlx->pl->movespd;
		mlx->keys.l_shift = 1;
	}
	else if (key == TILDE && !mlx->keys.l_shift)
	{
		mlx->pl->movespd = P_SLOWSPD;
		mlx->pl->d_move.x = mlx->pl->dir.x * mlx->pl->movespd;
		mlx->pl->d_move.y = mlx->pl->dir.y * mlx->pl->movespd;
		mlx->keys.tilde = 1;
	}
	else if (key == SP || key == X_KEY)
		check_secret(mlx);
	else
		menu_controls(key, mlx);
}

int		key_down(int key, t_mlx *mlx)
{
	if (key == U_ARROW && !mlx->keys.d_arrow
		&& !mlx->menu)
		mlx->keys.u_arrow = 1;
	else if (key == D_ARROW && !mlx->keys.u_arrow
		&& !mlx->menu)
		mlx->keys.d_arrow = 1;
	else if (key == L_ARROW)
		mlx->keys.l_arrow = 1;
	else if (key == R_ARROW)
		mlx->keys.r_arrow = 1;
	else if (key == M_KEY)
		mlx->show_mm = !mlx->show_mm;
	else if (key == Z_KEY)
		mlx->keys.z_key = 1;
	else if (key == H_KEY)
		mlx->keys.h_key = !mlx->keys.h_key;
	else
		keypress_event(key, mlx);
	return (0);
}

void	keyrelease_event(int key, t_mlx *mlx)
{
	if (key == L_SHIFT || key == TILDE)
	{
		mlx->pl->movespd = P_MOVESPD;
		mlx->pl->d_move.x = mlx->pl->dir.x * mlx->pl->movespd;
		mlx->pl->d_move.y = mlx->pl->dir.y * mlx->pl->movespd;
		mlx->keys.l_shift = 0;
		mlx->keys.tilde = 0;
	}
}

int		key_up(int key, t_mlx *mlx)
{
	if (key == U_ARROW)
		mlx->keys.u_arrow = 0;
	else if (key == D_ARROW)
		mlx->keys.d_arrow = 0;
	else if (key == L_ARROW)
		mlx->keys.l_arrow = 0;
	else if (key == R_ARROW)
		mlx->keys.r_arrow = 0;
	else if (key == Z_KEY)
		mlx->keys.z_key = 0;
	else
		keyrelease_event(key, mlx);
	return (0);
}
