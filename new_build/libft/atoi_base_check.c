/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_base_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 16:30:04 by vkuksa            #+#    #+#             */
/*   Updated: 2018/01/30 16:32:06 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"
#include <stdio.h>
#include <stdlib.h>

int		main(void)
{
	printf("%d\n", ft_atoi_base("ff", 16));
	system("leaks ll");
	return (0);
}
