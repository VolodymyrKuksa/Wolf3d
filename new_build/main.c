/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 08:57:33 by vkuksa            #+#    #+#             */
/*   Updated: 2018/02/21 08:57:36 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	put_error(char *str)
{
	perror(str);
	exit(1);
}

void	initialise_mlx(t_mlx *mlx, int ac)
{
	t_image		*m;
	t_player	*p;

	mlx->mlx = mlx_init();
	mlx->wnd = mlx_new_window(mlx->mlx, WNDW, WNDH, "Wolf3d");
	if (!(m = (t_image*)malloc(sizeof(t_image))))
		put_error("initialise_mlx");
	m->img = mlx_new_image(mlx->mlx, WNDW, WNDH);
	m->width = WNDW;
	m->height = WNDH;
	m->addr = (int*)mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->ed);
	m->sl /= sizeof(int);
	mlx->img = m;
	if (!(p = (t_player*)malloc(sizeof(t_player))))
		put_error("initialise_mlx");
	p->movespd = 10.0;
	p->turnspd = 5.0;
	mlx->pl = p;
	mlx->mapcount = ac - 1;
	mlx->menu = 0;
	mlx->map = mlx->allmaps[0];
}

int		main(int ac, char **av)
{
	t_mlx	*mlx;

	if (ac < 2 || ac > 11 || ft_strequ(av[1], "-help"))
	{
		ft_putstr("Usage: ./Wolf3d [filepath1] [filepath2] ...");
		ft_putendl(" up to 10 files.");
		return (0);
	}
	if (!(mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		put_error("main");
	mlx->allmaps = read_maps(ac, av);
	initialise_mlx(mlx, ac);
	output(mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
