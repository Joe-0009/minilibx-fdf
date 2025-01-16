/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:11:18 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/16 11:37:58 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
void init_vars(t_vars *vars)
{
    vars->points = NULL;
    vars->map = NULL;
    vars->img = NULL;
    vars->win = NULL;
    vars->mlx = NULL;
}
int	main(int ac, char **av)
{
	t_vars	vars;
	t_map	map;

	if (ac != 2)
		ft_error();
	
	 init_vars(&vars);
	vars.window_name = av[1];
	map = map_dimension(&vars);
	vars.map = &map;
	points_init(&vars);
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
