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
# define TS_H			32
# define PPD			935

# define MM_SIZE		160
# define MM_SIZE_H		80
# define MM_PX			910
# define MM_PY			550
# define MM_MAGN		5.0

# define FOV			60
# define FOV_H			30

# define TEX_COUNT		10
# define SPR_COUNT		15

# define P_SLOWSPD		5.0
# define P_MOVESPD		8.0
# define P_RUNSPD		12.0
# define P_TURNSPD		4.5

# define DTR(x)			((double)x * (M_PI / 180))
# define ABS(a)			((a) < 0 ? -(a) : (a))
# define RTD(b)			((b) * 180 / M_PI)

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
	t_dpt		l_dir;
	double		movespd;
	double		turnspd;
	int			gold;
	int			endlvl;
}				t_player;

typedef struct	s_sprite
{
	t_ipt		pos;
	int			id;
	int			collectable;
	int			collected;
	int			walkable;
	int			gold;
	double		dist;
	double		angle;
	double		l_angle;
	int			view;
	int			dim;
	int			dark;
}				t_sprite;

typedef struct	s_map
{
	char		*name;
	int			width;
	int			height;
	int			*orig;
	int			*arr;
	int			*scr;
	t_ipt		p_pos;
	t_dpt		p_dir;
	int			floor;
	int			ceiling;
	int			nbspr;
	t_sprite	*spr;
	int			ts;
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
	t_ipt		tex_id;
	t_ipt		tex_row;
}				t_ray;

typedef struct	s_keys
{
	int			u_arrow;
	int			d_arrow;
	int			l_arrow;
	int			r_arrow;
	int			l_shift;
	int			tilde;
	int			z_key;
	int			h_key;
}				t_keys;

typedef struct	s_mlx
{
	void		*mlx;
	void		*wnd;
	t_image		*img;
	t_map		*map;
	t_map		**allmaps;
	int			mapcount;
	int			mapid;
	t_player	*pl;
	t_ray		r;
	t_keys		keys;

	t_image		*mm;

	double		zbuff[WNDW];
	t_image		*textures;
	t_image		*sprites;

	int			menu;
	int			show_mm;
}				t_mlx;

/*
**	main
*/

void			put_error(char *str);

/*
**	keyboard_input
*/

int				key_down(int key, t_mlx *mlx);
int				key_up(int key, t_mlx *mlx);
int				check_update(t_mlx *mlx);

/*
**	keyboard_input_utils
*/

void			enter_key(t_mlx *mlx);

/*
**	read_map
*/

t_map			*get_map_data(int fd);

/*
**	map_utils
*/

void			strclear2d(char **str);
int				map_coord(int x, int y, t_map *map);
int				return_code(int c, char **str);
int				parse_player_direction(t_map *m, char **sp);
int				*new_map_array(t_map *map);

/*
**	utils
*/

int				is_all_digit(char *str);
void			rotate(double d, t_dpt *pt);
void			reset_player(t_mlx *mlx);
void			reset_sprites(t_mlx *mlx);
void			reset_map(t_map *map);

/*
**	output
*/

void			output(t_mlx *mlx);

/*
**	update
*/

int				update(void *data);

/*
**	image_utils
*/

t_image			*image_init(int width, int height, t_mlx *mlx);
int				img_coord(int x, int y, t_image *img);
void			fill_image(t_image *img, unsigned int col);
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

int				darken(int len);
void			draw_wall_x(int j, t_ray *r, t_image *p, t_image *t);
void			draw_wall_y(int j, t_ray *r, t_image *p, t_image *t);
void			floor_cast(int j, t_mlx *mlx, t_ray r);
int				intersect(int h, t_ray r, t_map *map);

/*
**	gradient
*/

int				grad(int bc, int ec, int step);

/*
**	load_textures
*/

t_image			*load_textures(t_mlx *m);

/*
**	load_sprites
*/

t_image			*load_sprites(t_mlx *m);
int				get_sprites(t_map *m, int fd);

/*
**	load_sprites
*/

void			render_sprites(t_mlx *mlx);

/*
**	collisions
*/

int				collision_check(int x, int y, t_map *m, t_player *pl);

/*
**	minimap
*/

void			mm_view(t_ray r, t_image *mm);
void			mm_walls(t_ipt pl, t_map *map, t_image *m);

/*
**	draw_line
*/

void			draw_line_img(t_dpt a, t_dpt b, int col, t_image *m);
void			put_dot_d(t_dpt pt, int col, t_image *m);
void			put_dot_i(t_ipt pt, int col, t_image *m);

/*
**	secret_walls
*/

void			check_secret(t_mlx *mlx);

/*
**	menues
*/

void			display_menu(t_mlx *mlx);
void			display_stats(t_mlx *mlx);
void			display_controls(t_mlx *mlx);

/*
**	wall_texturing
*/

int				get_texture_id(int h, t_ray *r, t_map *m);

#endif
