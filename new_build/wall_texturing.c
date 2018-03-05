/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_texturing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 18:10:44 by vkuksa            #+#    #+#             */
/*   Updated: 2018/03/05 18:10:47 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		get_texture_id(int h, t_ray *r, t_map *m)
{
	int		id;

	if ((id = intersect(h, *r, m)) != 10)
		return (id);
	else if (h && r->dir.x > 0)
		return (1);
	else if (h && r->dir.x < 0)
		return (2);
	else if (!h && r->dir.y > 0)
		return (3);
	else
		return (4);
}
