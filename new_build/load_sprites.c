/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 11:47:57 by vkuksa            #+#    #+#             */
/*   Updated: 2018/02/26 11:47:59 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "mlx.h"
#include <stdlib.h>
#include "get_next_line.h"
#include "libft.h"
#include <stdio.h>

void		get_sprite_data(t_image *t)
{
	int		i;

	i = -1;
	while (++i < SPR_COUNT)
	{
		t[i].width = TS;
		t[i].height = TS;
		t[i].addr =
		(int*)mlx_get_data_addr(t[i].img, &t[i].bpp, &t[i].sl, &t[i].ed);
		t[i].sl /= 4;
	}
}

t_image		*load_sprites(t_mlx *m)
{
	t_image		*t;
	int			w;
	int			h;

	w = TS;
	h = TS;
	if (!(t = (t_image*)malloc(sizeof(t_image) * (SPR_COUNT))))
		put_error("load_sprites");
	t[0].img = mlx_xpm_file_to_image(m->mlx, "./sprites/barrel.XPM", &w, &h);
	t[1].img = mlx_xpm_file_to_image(m->mlx, "./sprites/pillar.XPM", &w, &h);
	t[2].img = mlx_xpm_file_to_image(m->mlx, "./sprites/table.XPM", &w, &h);
	t[3].img = mlx_xpm_file_to_image(m->mlx, "./sprites/cage.XPM", &w, &h);
	t[4].img = mlx_xpm_file_to_image(m->mlx, "./sprites/s_cage.XPM", &w, &h);
	t[5].img = mlx_xpm_file_to_image(m->mlx, "./sprites/knight.XPM", &w, &h);
	t[6].img = mlx_xpm_file_to_image(m->mlx, "./sprites/skeleton.XPM", &w, &h);
	t[7].img = mlx_xpm_file_to_image(m->mlx, "./sprites/g_barrel.XPM", &w, &h);
	t[8].img = mlx_xpm_file_to_image(m->mlx, "./sprites/brush.XPM", &w, &h);
	t[9].img = mlx_xpm_file_to_image(m->mlx, "./sprites/vase.XPM", &w, &h);
	t[10].img = mlx_xpm_file_to_image(m->mlx, "./sprites/gold1.XPM", &w, &h);
	t[11].img = mlx_xpm_file_to_image(m->mlx, "./sprites/gold2.XPM", &w, &h);
	t[12].img = mlx_xpm_file_to_image(m->mlx, "./sprites/gold3.XPM", &w, &h);
	t[13].img = mlx_xpm_file_to_image(m->mlx, "./sprites/gold4.XPM", &w, &h);
	get_sprite_data(t);
	return (t);
}

int			get_sprite_line(t_map *m, int fd, int i)
{
	char	*line;
	char	**sp;

	if (get_next_line(fd, &line) != 1 || !ft_strlen(line)
		|| !(sp = ft_strsplit(line, ' ')))
		return (0);
	free(line);
	if (!is_all_digit(sp[0]) || !is_all_digit(sp[1]) || !is_all_digit(sp[2]))
		return (0);
	m->spr[i].id = ft_atoi(sp[0]);
	m->spr[i].pos.x = (ft_atoi(sp[1]) + 1) * TS + TS_H;
	m->spr[i].pos.y = (ft_atoi(sp[2]) + 1) * TS + TS_H;
	if ((sp[3] && *sp[3] == 'w') || m->spr[i].id >= 10)
		m->spr[i].walkable = 1;
	else
		m->spr[i].walkable = 0;
	strclear2d(sp);
	if (m->spr[i].id < 0 || m->spr[i].id >= SPR_COUNT)
		return (0);
	if (m->spr[i].pos.x < 0 || m->spr[i].pos.x >= m->width * TS
		|| m->spr[i].pos.y < 0 || m->spr[i].pos.y >= m->height * TS)
		return (0);
	if (m->spr[i].pos.x / TS == m->p_pos.x
		&& m->spr[i].pos.y / TS == m->p_pos.y)
		return (0);
	return (1);
}

int			get_sprites(t_map *m, int fd)
{
	char	*line;
	char	**sp;
	int		i;

	if (get_next_line(fd, &line) != 1 || !ft_strlen(line))
	{
		m->nbspr = 0;
		return (1);
	}
	sp = ft_strsplit(line, ' ');
	free(line);
	if (!is_all_digit(sp[0]) || sp[1])
		return (0);
	m->nbspr = ft_atoi(sp[0]);
	strclear2d(sp);
	m->spr = (t_sprite*)malloc(sizeof(t_sprite) * m->nbspr);
	i = -1;
	while (++i < m->nbspr)
		if (!get_sprite_line(m, fd, i))
			return (0);
	return (1);
}
