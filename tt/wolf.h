/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 18:18:14 by vkuksa            #+#    #+#             */
/*   Updated: 2018/02/18 18:18:21 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# define WNDW			1080
# define WNDW_H			540
# define WNDH			720
# define WNDH_H			360
# define TS				64
# define PPD			930

# define FOV			60
# define FOV_H			30
# define P_FOV			1.0471975
# define P_FOV_H		0.5235987

# define RED			0xff0000
# define GREEN			0x00ff00
# define BLUE			0x0000ff
# define YELLOW			0xffff00
# define WHITE			0xffffff
# define DARKRED		0xab0000
# define DARKGREEN		0x00ab00
# define DARKBLUE		0x0000ab
# define DARKYELLOW		0xabab00
# define GREY			0xababab
# define DARKGREY		0x6b6b6b

# define DTR(x)			((double)x * (M_PI / 180))
# define ABS(a)			((a) < 0 ? -(a) : (a))

typedef struct	s_ipt
{
	int			x;
	int			y;
}				t_ipt;

typedef struct	s_dpt
{
	double		x;
	double		y;
}				t_dpt;

typedef struct	s_player
{
	t_dpt		pos;
	t_dpt		dir;
	double		movespd;
	double		turnspd;
}				t_player;

typedef struct	s_map
{
	int			width;
	int			height;
	int			*arr;
}				t_map;

typedef struct	s_image
{
	int			width;
	int			height;
	void		*img;
	int			*addr;
	int			bpp;
	int			sl;
	int			ed;
}				t_image;

typedef struct	s_mlx
{
	void		*mlx;
	void		*wnd;
	t_image		*img;
}				t_mlx;

typedef struct	s_ray
{
	t_dpt		start;
	t_dpt		dir;
	t_dpt		endx;
	t_dpt		endy;
	t_dpt		len;
	double		d_dir;
}				t_ray;

#endif
