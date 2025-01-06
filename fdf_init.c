/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:15:07 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/06 14:15:11 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	cleanup_mlx(t_vars *vars)
{
	if (vars->mlx)
	{
		free(vars->mlx);
		vars->mlx = NULL;
	}
}

static void	cleanup_window(t_vars *vars)
{
	if (vars->win)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		vars->win = NULL;
	}
	cleanup_mlx(vars);
}

static void	handle_init_error(void)
{
	exit(EXIT_FAILURE);
}

void	init_fdf(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		handle_init_error();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, vars->window_name);
	if (!vars->win)
	{
		cleanup_mlx(vars);
		handle_init_error();
	}
}

void	create_image(t_vars *vars)
{
	vars->img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!vars->img.img)
	{
		cleanup_window(vars);
		handle_init_error();
	}
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel,
			&vars->img.line_length, &vars->img.endian);
	if (!vars->img.addr)
	{
		mlx_destroy_image(vars->mlx, vars->img.img);
		cleanup_window(vars);
		handle_init_error();
	}
}
