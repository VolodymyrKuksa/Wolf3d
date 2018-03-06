/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 16:19:06 by vkuksa            #+#    #+#             */
/*   Updated: 2018/02/21 16:19:09 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "mlx.h"
#include <stdlib.h>

int		img_coord(int x, int y, t_image *img)
{
	return (y * img->width + x);
}

void	fill_image(t_image *img, unsigned int col)
{
	int		i;
	int		j;

	i = -1;
	while (++i < img->height)
	{
		j = -1;
		while (++j < img->width)
			img->addr[img_coord(j, i, img)] = col;
	}
}

t_image	*image_init(int width, int height, t_mlx *mlx)
{
	t_image		*p;

	if (!(p = (t_image*)malloc(sizeof(t_image))))
		put_error("initialise_mlx");
	p->img = mlx_new_image(mlx->mlx, width, height);
	p->width = width;
	p->height = height;
	p->addr = (int*)mlx_get_data_addr(p->img, &p->bpp, &p->sl, &p->ed);
	return (p);
}

/*
**void	fill_image_tex(t_image *img, t_image *tex)
**{
**	int		i;
**	int		j;
**	int		jj;
**	int		ii;
**
**	i = -1;
**	while (++i < img->height)
**	{
**		ii = i % (tex->height + 1);
**		j = -1;
**		while (++j < img->width)
**		{
**			jj = j % (tex->width + 1);
**			img->addr[img_coord(j, i, img)] = tex->addr[img_coord(jj, ii, tex)];
**		}
**	}
**}
*/

void	image_grad_y(t_image *img, int bc, int ec)
{
	int		i;
	int		j;
	int		col;

	grad(bc, ec, img->height);
	i = -1;
	while (++i < img->height)
	{
		col = grad(bc, ec, 0);
		j = -1;
		while (++j < img->width)
			img->addr[img_coord(j, i, img)] = col;
	}
}

/*
**void	image_grad_x(t_image *img, int bc, int ec)
**{
**	int		i;
**	int		j;
**	int		col;
**
**	grad(bc, ec, img->width);
**	j = -1;
**	while (++j < img->width)
**	{
**		col = grad(bc, ec, 0);
**		i = -1;
**		while (++i < img->height)
**			img->addr[img_coord(j, i, img)] = col;
**	}
**}
*/
