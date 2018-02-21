/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 10:49:21 by vkuksa            #+#    #+#             */
/*   Updated: 2018/01/24 10:49:24 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Splits the given color into rgb parts and returns the part specified by 'c'.
*/

int		ft_split_col(char c, unsigned int color)
{
	if (c == 'b' || c == 3)
		return ((color << 24) >> 24);
	if (c == 'g' || c == 2)
		return ((color << 16) >> 24);
	if (c == 'r' || c == 1)
		return ((color << 8) >> 24);
	return (-1);
}

/*
**	Creates a new color with specified rgb ratios.
*/

int		ft_create_col(int red, int green, int blue)
{
	unsigned int	color;

	color = 0;
	color = color | blue;
	color = color | (green << 8);
	color = color | (red << 16);
	color = (color << 8) >> 8;
	return ((int)color);
}

/*
**	Creates gradient by counting the change of rgb ratios
**	of begin color 'bc' to gradually convert it into end color 'ec' and
**	returns the next gradient color with each call if the step is set to 0.
*/

int		grad(int bc, int ec, int step)
{
	static double	d_rgb[3];
	static double	rgb[3];
	static int		iteration = 0;

	if (step)
	{
		rgb[0] = (double)ft_split_col(1, bc);
		rgb[1] = (double)ft_split_col(2, bc);
		rgb[2] = (double)ft_split_col(3, bc);
		d_rgb[0] = ((double)ft_split_col(1, ec) - rgb[0]) / (step + 1);
		d_rgb[1] = ((double)ft_split_col(2, ec) - rgb[1]) / (step + 1);
		d_rgb[2] = ((double)ft_split_col(3, ec) - rgb[2]) / (step + 1);
	}
	else
	{
		if (iteration)
		{
			rgb[0] += d_rgb[0];
			rgb[1] += d_rgb[1];
			rgb[2] += d_rgb[2];
		}
		iteration = 1;
		return (ft_create_col(rgb[0], rgb[1], rgb[2]));
	}
	return (0);
}
