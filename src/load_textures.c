/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 19:32:55 by vkuksa            #+#    #+#             */
/*   Updated: 2018/02/22 19:32:56 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "mlx.h"
#include <stdlib.h>

void		get_texture_data(t_image *t)
{
	int		i;

	i = 0;
	while (++i < TEX_COUNT)
	{
		t[i].width = TS;
		t[i].height = TS;
		t[i].addr =
		(int*)mlx_get_data_addr(t[i].img, &t[i].bpp, &t[i].sl, &t[i].ed);
		t[i].sl /= 4;
	}
}

t_image		*load_textures(t_mlx *m)
{
	t_image		*t;
	int			w;
	int			h;

	w = TS;
	h = TS;
	if (!(t = (t_image*)malloc(sizeof(t_image) * (TEX_COUNT + 1))))
		put_error("load_textures");
	t[1].img = mlx_xpm_file_to_image(m->mlx, "./textures/b_stone.XPM", &w, &h);
	t[2].img = mlx_xpm_file_to_image(m->mlx, "./textures/cave.XPM", &w, &h);
	t[3].img = mlx_xpm_file_to_image(m->mlx, "./textures/g_brick.XPM", &w, &h);
	t[4].img = mlx_xpm_file_to_image(m->mlx, "./textures/metal.XPM", &w, &h);
	t[5].img = mlx_xpm_file_to_image(m->mlx, "./textures/r_brick.XPM", &w, &h);
	t[6].img = mlx_xpm_file_to_image(m->mlx, "./textures/stone.XPM", &w, &h);
	t[7].img = mlx_xpm_file_to_image(m->mlx, "./textures/wood.XPM", &w, &h);
	t[8].img = mlx_xpm_file_to_image(m->mlx, "./textures/floor.XPM", &w, &h);
	t[9].img = mlx_xpm_file_to_image(m->mlx, "./textures/concrete.XPM", &w, &h);
	get_texture_data(t);
	return (t);
}
