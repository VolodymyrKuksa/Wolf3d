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
# define WNDW_Q			270
# define WNDH			720
# define WNDH_H			360
# define TS				64
# define PPD			930

# define FOV			60
# define FOV_H			30

# define RED			0xff0000
# define GREEN			0x00ff00
# define BLUE			0x0000ff
# define YELLOW			0xffff00
# define WHITE			0xffffff
# define DARKRED		0x7b0000
# define DARKGREEN		0x007b00
# define DARKBLUE		0x00007b
# define DARKYELLOW		0xabab00
# define GREY			0xababab
# define DARKGREY		0x6b6b6b
# define DULLGREY		0x333333
# define MENU_BACK		0x0e4038

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
	t_ipt		pos;
	t_ipt		d_move;
	t_dpt		dir;
	double		movespd;
	double		turnspd;
}				t_player;

typedef struct	s_map
{
	char		*name;
	int			width;
	int			height;
	int			*arr;
	t_ipt		p_pos;
	t_dpt		p_dir;
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

typedef struct	s_ray
{
	t_ipt		start;
	t_dpt		dir;
	t_dpt		endx;
	t_dpt		endy;
	t_dpt		len;
	double		angle;
	double		d_angle;
	double		distortion;
}				t_ray;

typedef struct	s_mlx
{
	void		*mlx;
	void		*wnd;
	t_image		*img;
	t_map		*map;
	t_map		**allmaps;
	int			mapcount;
	t_player	*pl;
	t_ray		r;

	int			menu;
}				t_mlx;

// typedef struct	s_thread
// {
// 	t_mlx		*mlx;
// 	t_ray		r;
// 	int			s;
// }				t_thread;

/*
**	main
*/

void			put_error(char *str);

/*
**	read_map
*/

t_map			**read_maps(int ac, char **av);

/*
**	map_utils
*/

void			strclear2d(char **str);
int				map_coord(int x, int y, t_map *map);
int				return_code(int c, char **str);
void			clear_map(t_map *m);
int				parse_player_direction(t_map *m, char **sp);

/*
**	utils
*/

int				is_all_digit(char *str);
void			rotate(double d, t_dpt *pt);
void			reset_player(t_mlx *mlx);

/*
**	output
*/

void			output(t_mlx *mlx);

/*
**	image_utils
*/

int				img_coord(int x, int y, t_image *img);
void			fill_image(t_image *img, int col);
void			fill_image_tex(t_image *img, t_image *tex);
void			image_grad_y(t_image *img, int bc, int ec);
void			image_grad_x(t_image *img, int bc, int ec);

/*
**	render
*/

void			draw_world(t_mlx *mlx);

/*
**	render_utils
*/

void			draw_wall(int j, double dist, int col, t_image *p);
int				intersect(int h, t_ray r, t_map *map);

/*
**	gradient
*/

int				grad(int bc, int ec, int step);

#endif
