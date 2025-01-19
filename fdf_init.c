/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:15:07 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/19 13:40:44 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	cleanup_image(t_vars *vars)
{
	if (!vars || !vars->img)
		return ;
	if (vars->img->img && vars->mlx)
	{
		mlx_destroy_image(vars->mlx, vars->img->img);
		vars->img->img = NULL;
		vars->img->addr = NULL;
	}
	free(vars->img);
	vars->img = NULL;
}

void	cleanup_all(t_vars *vars)
{
	if (!vars)
		return ;
	if (vars->points && vars->map)
	{
		free_points(vars->map->dim.height, vars->points);
		free(vars->bounds);
		vars->points = NULL;
	}
	cleanup_image(vars);
	if (vars->win && vars->mlx)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		vars->win = NULL;
	}
	if (vars->map)
	{
		free(vars->map);
		vars->map = NULL;
	}
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		vars->mlx = NULL;
	}
}

void	create_image(t_vars *vars)
{
	vars->img = malloc(sizeof(t_image));
	if (!vars->img)
	{
		cleanup_all(vars);
		exit(EXIT_FAILURE);
	}
	vars->img->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!vars->img->img)
	{
		cleanup_all(vars);
		exit(EXIT_FAILURE);
	}
	vars->img->addr = mlx_get_data_addr(vars->img->img,
			&vars->img->bits_per_pixel, &vars->img->line_length,
			&vars->img->endian);
	if (!vars->img->addr)
	{
		cleanup_all(vars);
		exit(EXIT_FAILURE);
	}
}

void	init_fdf(t_vars *vars)
{
	parse_map(vars);
	iso_point(vars);
	move_map(vars);
	mlx_hooks(vars, vars->window_name);
	create_image(vars);
	main_draw(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}
