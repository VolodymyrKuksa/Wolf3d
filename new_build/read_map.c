/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 08:57:51 by vkuksa            #+#    #+#             */
/*   Updated: 2018/02/21 08:57:53 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>

/*
**	map file format:
**
**	0	line: map name (any string, delimited by \n).
**
**	1st line: map dimensions as positive ints delimited by spaces
**	(first x, then y).
**
**	2nd line: player start coordinates as positive ints delimited by spaces
**		and a letter corresponding to the player view direction
**		(n - north, e - east, w - west, s - south, ex: px, py, n).
**
**	Other y lines: must contain x positive ints delimites by spaces, that
**		define texture's id (for defining walls and their textues) or 0.
*/

int		get_definition(t_map *m, int fd)
{
	char	*line;
	char	**sp;

	if (get_next_line(fd, &m->name) != 1 || !ft_strlen(m->name))
		return (0);
	if (get_next_line(fd, &line) != 1 || !ft_strlen(line)
		|| !(sp = ft_strsplit(line, ' ')))
		return (0);
	free(line);
	if (!is_all_digit(sp[0]) || !is_all_digit(sp[1]) || sp[2])
		return (return_code(0, sp));
	m->width = ft_atoi(sp[0]) + 2;
	m->height = ft_atoi(sp[1]) + 2;
	strclear2d(sp);
	if (get_next_line(fd, &line) != 1 || !ft_strlen(line)
		|| !(sp = ft_strsplit(line, ' ')))
		return (0);
	free(line);
	if (!is_all_digit(sp[0]) || !is_all_digit(sp[1]) || ft_strlen(sp[2]) != 1
		|| sp[3] || !parse_player_direction(m, sp))
		return (return_code(0, sp));
	m->p_pos.x = ft_atoi(sp[0]) + 1;
	m->p_pos.y = ft_atoi(sp[1]) + 1;
	return (return_code((m->p_pos.x > 0 && m->p_pos.y > 0 ? 1 : 0), sp));
}

int		get_wall_row(t_map *m, int fd, int i)
{
	int		j;
	int		gnlret;
	int		id;
	char	*line;
	char	**sp;

	gnlret = get_next_line(fd, &line);
	if (gnlret == -1)
		put_error("get_wall_row");
	if (!gnlret)
		return (0);
	sp = ft_strsplit(line, ' ');
	free(line);
	j = -1;
	while (++j < m->width)
	{
		if (j == 0 || j == m->width - 1)
			id = 1;
		else if (!sp[j - 1] || !is_all_digit(sp[j - 1])
			|| (id = atoi(sp[j - 1]) % (TEX_COUNT + 1)) < 0)
			return (0);
		m->arr[map_coord(j, i, m)] = id;
	}
	strclear2d(sp);
	return (j == m->width ? 1 : 0);
}

int		get_walls(t_map *m, int fd)
{
	int		i;
	int		j;

	if (!(m->arr = (int*)malloc(sizeof(int) * m->width * m->height)))
		put_error("get_walls");
	i = -1;
	while (++i < m->height)
	{
		if (i == 0 || i == m->height - 1)
		{
			j = -1;
			while (++j < m->width)
				m->arr[map_coord(j, i, m)] = 1;
		}
		else if (!get_wall_row(m, fd, i))
			return (0);
	}
	if (i != m->height || m->arr[map_coord(m->p_pos.x, m->p_pos.y, m)])
		return (0);
	return (1);
}

int		get_floor(t_map *m, int fd)
{
	char	*line;
	char	**sp;
	int		gnlret;

	gnlret = get_next_line(fd, &line);
	if (!gnlret)
		return (0);
	sp = ft_strsplit(line, ' ');
	free(line);
	m->floor = ft_atoi(sp[0]) % (TEX_COUNT + 1);
	m->ceiling = ft_atoi(sp[1]) % (TEX_COUNT + 1);
	strclear2d(sp);
	if (m->floor <= 0 || m->ceiling <= 0 || sp[2])
		return (0);
	return (1);
}

t_map	*get_map_data(int fd)
{
	t_map	*m;

	m = NULL;
	if (read(fd, NULL, 0) != 0 || !(m = (t_map*)malloc(sizeof(t_map))))
		put_error("get_map_data");
	if (!get_definition(m, fd) || !get_floor(m, fd) || !get_walls(m, fd)
		|| !get_sprites(m, fd))
	{
		clear_map(m);
		return (NULL);
	}
	return (m);
}

/*
**		printf("map[%d]:\nname: %s\nwidth:   %d\nheight:  %d\np_pos.x:
**	%d\np_pos.y: %d\np_dir.x: %f\np_dir.y: %f\n", i, inp[i]->name,
**	inp[i]->width, inp[i]->height, inp[i]->p_pos.x, inp[i]->p_pos.y,
**	inp[i]->p_dir.x, inp[i]->p_dir.y);
**
**		for (int h = 0; h < inp[i]->height; h++)
**		{
**			for (int w = 0; w < inp[i]->width; w++)
**				printf("%d", inp[i]->arr[map_coord(w, h, inp[i])]);
**			printf("\n");
**		}
*/
