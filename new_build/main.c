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
#include <fcntl.h>
#include <math.h>

void	put_error(char *str)
{
	perror(str);
	exit(1);
}

void	initialise_keys(t_mlx *mlx)
{
	mlx->keys.u_arrow = 0;
	mlx->keys.d_arrow = 0;
	mlx->keys.l_arrow = 0;
	mlx->keys.r_arrow = 0;
	mlx->keys.enter = 0;
	mlx->keys.sp = 0;
	mlx->keys.esc = 0;
}

void	initialise_mlx(t_mlx *mlx, int ac)
{
	mlx->mlx = mlx_init();
	mlx->wnd = mlx_new_window(mlx->mlx, WNDW, WNDH, "Wolf3d");
	mlx->img = image_init(WNDW, WNDH, mlx);
	mlx->mm = image_init(MM_SIZE, MM_SIZE, mlx);
	if (!(mlx->pl = (t_player*)malloc(sizeof(t_player))))
		put_error("initialise_mlx");
	mlx->pl->movespd = P_MOVESPD;
	mlx->pl->turnspd = P_TURNSPD;
	mlx->mapcount = ac - 1;
	mlx->menu = 1;
	mlx->mapid = 0;
	mlx->map = mlx->allmaps[mlx->mapid];
	mlx->textures = load_textures(mlx);
	mlx->sprites = load_sprites(mlx);
	mlx->show_mm = 1;
}

t_map	**read_maps(int ac, char **av)
{
	int		fd[ac];
	int		i;
	t_map	**inp;

	ac--;
	av++;
	if (!(inp = (t_map**)malloc(sizeof(t_map*) * (ac + 1))))
		put_error("read_maps");
	inp[ac] = NULL;
	i = -1;
	while (++i < ac)
	{
		fd[i] = open(av[i], O_RDONLY);
		inp[i] = get_map_data(fd[i]);
		if (!inp[i])
		{
			ft_putstr("Invalid map: ");
			ft_putendl(av[i]);
			exit(0);
		}
	}
	i = -1;
	while (++i < ac)
		close(fd[i]);
	return (inp);
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
	mlx_do_key_autorepeatoff(mlx->mlx);
	mlx_hook(mlx->wnd, 2, 1L << 0, key_down, mlx);
	mlx_hook(mlx->wnd, 3, 1L << 1, key_up, mlx);
	mlx_loop_hook(mlx->mlx, update, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
