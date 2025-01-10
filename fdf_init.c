/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:15:07 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/10 14:55:57 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	cleanup_mlx(t_vars *vars)
{
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		vars->mlx = NULL;
	}
}

void	cleanup_image(t_vars *vars)
{
	if (vars->img)
	{
		if (vars->img->img && vars->mlx)
		{
			mlx_destroy_image(vars->mlx, vars->img->img);
			vars->img->img = NULL;
			vars->img->addr = NULL;
		}
		free(vars->img);
		vars->img = NULL;
	}
}

void	cleanup_window(t_vars *vars)
{
	cleanup_image(vars);
	if (vars->win)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		vars->win = NULL;
	}
	cleanup_mlx(vars);
}

void	init_fdf(t_vars *vars)
{
	parse_map(vars->points, vars->window_name, vars->map);
	calculate_scale(vars->map);
	apply_projection(vars->points, vars->map);
	move_map(vars->points, vars->map, 0, 0);
	mlx_hooks(vars, vars->window_name);
	create_image(vars);
	main_draw(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}

void	create_image(t_vars *vars)
{
	vars->img = malloc(sizeof(t_image));
	if (!vars->img)
	{
		cleanup_window(vars);
		free_points(vars->map->dim.height, vars->points);
		exit(EXIT_FAILURE);
	}
	vars->img->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!vars->img->img)
	{
		cleanup_window(vars);
		free_points(vars->map->dim.height, vars->points);
		exit(EXIT_FAILURE);
	}
	vars->img->addr = mlx_get_data_addr(vars->img->img,
			&vars->img->bits_per_pixel, &vars->img->line_length,
			&vars->img->endian);
	if (!vars->img->addr)
	{
		cleanup_window(vars);
		free_points(vars->map->dim.height, vars->points);
		exit(EXIT_FAILURE);
	}
}
