/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 13:57:39 by vkuksa            #+#    #+#             */
/*   Updated: 2018/02/21 13:57:41 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdlib.h>

void	strclear2d(char **str)
{
	int		i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

int		map_coord(int x, int y, t_map *map)
{
	return (y * map->width + x);
}

int		return_code(int c, char **str)
{
	strclear2d(str);
	return (c);
}

void	clear_map(t_map *m)
{
	free(m->name);
	free(m->arr);
	free(m);
}

int		parse_player_direction(t_map *m, char **sp)
{
	if (*(sp[2]) == 'n' || *(sp[2]) == 'N')
	{
		m->p_dir.x = 0;
		m->p_dir.y = -1;
	}
	else if (*(sp[2]) == 'e' || *(sp[2]) == 'E')
	{
		m->p_dir.x = 1;
		m->p_dir.y = 0;
	}
	else if (*(sp[2]) == 's' || *(sp[2]) == 'S')
	{
		m->p_dir.x = 0;
		m->p_dir.y = 1;
	}
	else if (*(sp[2]) == 'w' || *(sp[2]) == 'W')
	{
		m->p_dir.x = 0;
		m->p_dir.y = -1;
	}
	else
		return (0);
	return (1);
}
