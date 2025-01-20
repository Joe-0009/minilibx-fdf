/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:27:40 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/20 11:09:14 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	check_fdf(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i--;
	if (str[i] != 'f' || str[i - 1] != 'd' || str[i - 2] != 'f')
		ft_error();
}

static void	init_vars(t_vars **vars)
{
	(*vars) = malloc(sizeof(t_vars));
	if (!(*vars))
		ft_error();
	(*vars)->bounds = malloc(sizeof(t_bounds));
	if ((*vars)->bounds == NULL)
	{
		cleanup_all(*vars);
		ft_error();
	}
	(*vars)->map = malloc(sizeof(t_map));
	if (!(*vars)->map)
	{
		cleanup_all(*vars);
		ft_error();
	}
	(*vars)->img = NULL;
	(*vars)->win = NULL;
	(*vars)->mlx = NULL;
}

int	main(int ac, char **av)
{
	t_vars	*vars;

	if (ac != 2)
		ft_error();
	check_fdf(av[1]);
	vars = NULL;
	init_vars(&vars);
	vars->window_name = av[1];
	map_dimension(vars);
	points_init(vars);
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (cleanup_all(vars), 1);
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, vars->window_name);
	if (!vars->win)
		return (cleanup_all(vars), 1);
	init_fdf(vars);
	mlx_loop(vars->mlx);
	return (0);
}
