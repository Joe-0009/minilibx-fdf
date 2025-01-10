/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_events2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:55:17 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/10 15:00:33 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_new_image(t_vars *vars)
{
	cleanup_image(vars);
	create_image(vars);
	main_draw(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}

int	close_window_x(t_vars *vars)
{
	cleanup_image(vars);
	cleanup_window(vars);
	free_points(vars->map->dim.height, vars->points);
	exit(0);
	return (0);
}

int	close_window_esc(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
	{
		cleanup_image(vars);
		cleanup_window(vars);
		free_points(vars->map->dim.height, vars->points);
		exit(0);
	}
	return (0);
}

int	key_handler(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
		close_window_esc(keycode, vars);
	else if ((keycode >= 65361 && keycode <= 65364) || keycode == 32
		|| keycode == 112)
		handle_movement(keycode, vars);
	else if (keycode == 122 || keycode == 111)
		zoom_in_and_out(keycode, vars);
	else if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A
		|| keycode == KEY_D || keycode == KEY_Q || keycode == KEY_E
		|| keycode == KEY_I)
		rotate(keycode, vars);
	return (0);
}

void	mlx_hooks(t_vars *vars, char *str)
{
	vars->window_name = str;
	mlx_hook(vars->win, 2, 1L << 0, key_handler, vars);
	mlx_hook(vars->win, 17, 0, close_window_x, vars);
}
