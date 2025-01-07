/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:14:08 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/07 18:02:02 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window_esc(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{
		cleanup_image(vars);
		cleanup_window(vars);
		free_points(vars->dim.height, vars->points);
		exit(0);
	}
	return (0);
}

int	close_window_x(t_vars *vars)
{
	cleanup_image(vars);
	cleanup_window(vars);
	free_points(vars->dim.height, vars->points);
	exit(0);
	return (0);
}

void	mlx_hooks(t_vars *vars, char *str)
{
	vars->window_name = str;
	mlx_hook(vars->win, 2, 1L << 0, close_window_esc, vars);
	mlx_hook(vars->win, 17, 0, close_window_x, vars);
	create_image(vars);
}
