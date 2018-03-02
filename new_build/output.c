/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 16:06:47 by vkuksa            #+#    #+#             */
/*   Updated: 2018/02/21 16:06:49 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "mlx.h"
#include "colors.h"
#include <stdlib.h>
#include <time.h>

void	timeframe(void)
{
	static clock_t	prev_frame = 0;
	clock_t			t;

	t = clock();
	while (t - prev_frame < 30000)
		t = clock();
	prev_frame = clock();
}

void	display_menu(t_mlx *mlx)
{
	int		i;
	int		y;

	image_grad_y(mlx->img, MENU_BACK, 0);
	y = 100;
	i = -1;
	mlx_put_image_to_window(mlx->mlx, mlx->wnd, mlx->img->img, 0, 0);
	while (++i < mlx->mapcount)
	{
		mlx_string_put(mlx->mlx, mlx->wnd, 490, y,
		(mlx->map == mlx->allmaps[i] ? WHITE : GREY), mlx->allmaps[i]->name);
		y += 20;
	}
	mlx_string_put(mlx->mlx, mlx->wnd, 890, 698,
		DARKGREY, "Press Esc to exit.");
}

void	output(t_mlx *mlx)
{
	static t_map	*s_map = NULL;

	if (mlx->menu)
		display_menu(mlx);
	else
	{
		if (mlx->map != s_map)
		{
			reset_player(mlx);
			s_map = mlx->map;
		}
		mlx_clear_window(mlx->mlx, mlx->wnd);
		fill_image(mlx->img, 0);
		fill_image(mlx->mm, MM_BACK);
		draw_world(mlx);
		timeframe();
		mlx_put_image_to_window(mlx->mlx, mlx->wnd, mlx->img->img, 0, 0);
		mlx_put_image_to_window(mlx->mlx, mlx->wnd, mlx->mm->img, MM_PX, MM_PY);
	}
}
