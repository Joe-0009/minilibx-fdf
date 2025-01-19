/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:27:40 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/19 13:13:45 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	cleanup_gnl(int fd)
{
	char	*dummy;

	dummy = get_next_line(fd);
	while (dummy)
	{
		free(dummy);
		dummy = get_next_line(fd);
	}
}

static void	init_vars(t_vars *vars)
{
	vars->points = NULL;
	vars->map = NULL;
	vars->img = NULL;
	vars->win = NULL;
	vars->mlx = NULL;
	vars->bounds = malloc(sizeof(t_bounds));
	if (vars->bounds == NULL)
		ft_error();
}

int	main(int ac, char **av)
{
	t_vars	vars;
	t_map	*map;

	if (ac != 2)
		ft_error();
	init_vars(&vars);
	vars.window_name = av[1];
	map = malloc(sizeof(t_map));
	if (!map)
		ft_error();
	*map = map_dimension(&vars);
	vars.map = map;
	points_init(&vars);
	if (!vars.points)
		return (cleanup_all(&vars), 1);
	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (cleanup_all(&vars), 1);
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, vars.window_name);
	if (!vars.win)
		return (cleanup_all(&vars), 1);
	init_fdf(&vars);
	mlx_loop(vars.mlx);
	return (0);
}
