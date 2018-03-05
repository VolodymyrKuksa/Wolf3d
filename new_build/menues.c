/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menues.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 14:41:33 by vkuksa            #+#    #+#             */
/*   Updated: 2018/03/05 14:41:35 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "mlx.h"
#include "libft.h"
#include "colors.h"
#include <stdlib.h>

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

void	display_controls(t_mlx *mlx)
{
	mlx_string_put(mlx->mlx, mlx->wnd, 20, 20, YELLOW,
		"Arrows ......... move and look around.");
	mlx_string_put(mlx->mlx, mlx->wnd, 20, 40, YELLOW,
		"L_Shift ........ run.");
	mlx_string_put(mlx->mlx, mlx->wnd, 20, 60, YELLOW,
		"~ .............. slow walk.");
	mlx_string_put(mlx->mlx, mlx->wnd, 20, 80, YELLOW,
		"Z + Arrows ..... strafe.");
	mlx_string_put(mlx->mlx, mlx->wnd, 20, 100, YELLOW,
		"X / Space ...... activate hidden walls.");
	mlx_string_put(mlx->mlx, mlx->wnd, 20, 120, YELLOW,
		"M .............. show / hide minimap.");
	mlx_string_put(mlx->mlx, mlx->wnd, 20, 140, YELLOW,
		"Esc ............ go to main menu.");
	mlx_string_put(mlx->mlx, mlx->wnd, 20, 160, YELLOW,
		"H .............. show / hide controls.");
}
