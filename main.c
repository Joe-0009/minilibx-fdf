/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:11:18 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/10 14:42:38 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;

	p = (unsigned char *)b;
	while (len > 0)
	{
		p[len - 1] = c;
		len--;
	}
	return (b);
}

int	main(int ac, char **av)
{
	t_vars	vars;
	t_map	map;

	if (ac != 2)
	{
		return (0);
	}
	vars.window_name = av[1];
	map = map_dimension(vars.window_name);
	vars.map = &map;
	vars.points = points_init(&map);
	if (!vars.points)
		return (0);
	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (0);
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, vars.window_name);
	if (!vars.win)
		return (0);
	init_fdf(&vars);
	mlx_loop(vars.mlx);
	return (0);
}
