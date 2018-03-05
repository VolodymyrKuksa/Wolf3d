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
#include "libft.h"
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

void	put_gold(t_mlx *mlx)
{
	char	*str;

	str = ft_itoa(mlx->pl->gold);
	mlx_string_put(mlx->mlx, mlx->wnd, 20, 690, RED, str);
	free(str);
}

void	draw_hud(t_mlx *mlx)
{
	put_gold(mlx);
	if (mlx->show_mm)
		mlx_put_image_to_window(mlx->mlx, mlx->wnd, mlx->mm->img,
		MM_PX, MM_PY);
	if (mlx->keys.h_key)
		display_controls(mlx);
}

void	output(t_mlx *mlx)
{
	static t_map	*s_map = NULL;

	if (mlx->pl->endlvl)
		display_stats(mlx);
	else if (mlx->menu)
		display_menu(mlx);
	else
	{
		if (mlx->map != s_map)
		{
			reset_player(mlx);
			reset_sprites(mlx);
			reset_map(mlx->map);
			s_map = mlx->map;
		}
		mlx_clear_window(mlx->mlx, mlx->wnd);
		fill_image(mlx->mm, MM_BACK);
		draw_world(mlx);
		timeframe();
		mlx_put_image_to_window(mlx->mlx, mlx->wnd, mlx->img->img, 0, 0);
		draw_hud(mlx);
	}
}
