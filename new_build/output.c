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

void	display_menu(t_mlx *mlx)
{
	int				i;
	int				y;

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

void	display_stats(t_mlx *mlx)
{
	char	*s1;
	char	*s2;
	char	*tmp;

	mlx->menu = 1;
	image_grad_y(mlx->img, MENU_BACK, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->wnd, mlx->img->img, 0, 0);
	mlx_string_put(mlx->mlx, mlx->wnd, 490, 200, RED, "LEVEL COMPLETE!");
	mlx_string_put(mlx->mlx, mlx->wnd, 490, 240, WHITE, "LEVEL SCORE:");
	s1 = ft_itoa(mlx->pl->gold);
	tmp = ft_strjoin(s1, " / ");
	free(s1);
	s1 = ft_itoa(mlx->map->ts);
	s2 = ft_strjoin(tmp, s1);
	free(s1);
	free(tmp);
	mlx_string_put(mlx->mlx, mlx->wnd, 490, 280, WHITE, s2);
	free(s2);
	mlx_string_put(mlx->mlx, mlx->wnd, 790, 698,
		DARKGREY, "Press Esc to go to main menu.");
	if (mlx->mapid < mlx->mapcount - 1)
		mlx_string_put(mlx->mlx, mlx->wnd, 5, 698,
			DARKGREY, "Pess Enter to play next level.");
}

void	put_gold(t_mlx *mlx)
{
	char	*str;

	str = ft_itoa(mlx->pl->gold);
	mlx_string_put(mlx->mlx, mlx->wnd, 20, 690, RED, str);
	free(str);
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
		put_gold(mlx);
		if (mlx->show_mm)
			mlx_put_image_to_window(mlx->mlx, mlx->wnd, mlx->mm->img,
			MM_PX, MM_PY);
	}
}
