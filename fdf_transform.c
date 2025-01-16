/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:15:41 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/16 17:45:50 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	find_map_boundaries(t_vars *vars)
{
	int	i;
	int	j;

	vars->bounds->min_x = INT_MAX;
	vars->bounds->max_x = INT_MIN;
	vars->bounds->min_y = INT_MAX;
	vars->bounds->max_y = INT_MIN;
	i = 0;
	while (i < vars->map->dim.height)
	{
		j = 0;
		while (j < vars->map->dim.width)
		{
			if (vars->points[i][j].x < vars->bounds->min_x)
				vars->bounds->min_x = vars->points[i][j].x;
			if (vars->points[i][j].x > vars->bounds->max_x)
				vars->bounds->max_x = vars->points[i][j].x;
			if (vars->points[i][j].y < vars->bounds->min_y)
				vars->bounds->min_y = vars->points[i][j].y;
			if (vars->points[i][j].y > vars->bounds->max_y)
				vars->bounds->max_y = vars->points[i][j].y;
			j++;
		}
		i++;
	}
}

void	move_map(t_vars *vars)
{
	int	i;
	int	j;

	find_map_boundaries(vars);
	vars->map->center.x = (WIDTH - (vars->bounds->max_x - vars->bounds->min_x))
		/ 2;
	vars->map->center.y = (HEIGHT - (vars->bounds->max_y - vars->bounds->min_y))
		/ 2;
	i = 0;
	while (i < vars->map->dim.height)
	{
		j = 0;
		while (j < vars->map->dim.width)
		{
			vars->points[i][j].x += (vars->map->center.x - vars->bounds->min_x
					+ vars->map->center.offset_x);
			vars->points[i][j].y += (vars->map->center.y - vars->bounds->min_y
					+ vars->map->center.offset_y);
			j++;
		}
		i++;
	}
}

static void	apply_zoom_to_points(t_vars *vars, float scale_factor)
{
	int	i;
	int	j;

	i = -1;
	while (++i < vars->map->dim.height)
	{
		j = -1;
		while (++j < vars->map->dim.width)
		{
			vars->points[i][j].x *= scale_factor;
			vars->points[i][j].y *= scale_factor;
			vars->points[i][j].z *= scale_factor;
		}
	}
}

void	update_zoom(t_vars *vars, float zoom_delta)
{
	float	new_zoom_factor;
	float	scale_factor;

	new_zoom_factor = vars->map->scale.zoom_factor * zoom_delta;
	if (new_zoom_factor < 0.1)
		new_zoom_factor = 0.1;
	if (new_zoom_factor > 10.0)
		new_zoom_factor = 10.0;
	scale_factor = new_zoom_factor / vars->map->scale.zoom_factor;
	vars->map->scale.zoom_factor = new_zoom_factor;
	apply_zoom_to_points(vars, scale_factor);
	move_map(vars);
}
