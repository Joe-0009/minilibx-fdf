/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:15:41 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/09 21:09:46 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	find_map_boundaries(t_point **points, t_map *map, t_bounds *bounds)
{
	int	i;
	int	j;

	bounds->min_x = INT_MAX;
	bounds->max_x = INT_MIN;
	bounds->min_y = INT_MAX;
	bounds->max_y = INT_MIN;
	i = 0;
	while (i < map->dim.height)
	{
		j = 0;
		while (j < map->dim.width)
		{
			if (points[i][j].x < bounds->min_x)
				bounds->min_x = points[i][j].x;
			if (points[i][j].x > bounds->max_x)
				bounds->max_x = points[i][j].x;
			if (points[i][j].y < bounds->min_y)
				bounds->min_y = points[i][j].y;
			if (points[i][j].y > bounds->max_y)
				bounds->max_y = points[i][j].y;
			j++;
		}
		i++;
	}
}

void	move_map(t_point **points, t_map *map, int new_offset_x, int new_offset_y)
{
	int			i;
	int			j;
	t_bounds	bounds;

	map->center.offset_x += new_offset_x;
    map->center.offset_y += new_offset_y;
	find_map_boundaries(points, map, &bounds);
	map->center.x = (WIDTH - (bounds.max_x - bounds.min_x)) / 2 ;
	map->center.y = (HEIGHT - (bounds.max_y - bounds.min_y)) / 2 ;
	i = 0;
	while (i < map->dim.height)
	{
		j = 0;
		while (j < map->dim.width)
		{
			points[i][j].x += (map->center.x - bounds.min_x + map->center.offset_x);
			points[i][j].y += (map->center.y - bounds.min_y + map->center.offset_y);
			j++;
		}
		i++;
	}
}

void    update_zoom(t_vars *vars, float zoom_delta)
{
    int base_offset_x;
    int base_offset_y;

	base_offset_x = vars->map->center.offset_x / vars->map->scale.zoom_factor;
	base_offset_y = vars->map->center.offset_y / vars->map->scale.zoom_factor;
    vars->map->scale.zoom_factor *= zoom_delta;
    if (vars->map->scale.zoom_factor < 0.1)
        vars->map->scale.zoom_factor = 0.1;
    if (vars->map->scale.zoom_factor > 10.0)
        vars->map->scale.zoom_factor = 10.0;
    vars->map->center.offset_x = base_offset_x * vars->map->scale.zoom_factor;
    vars->map->center.offset_y = base_offset_y * vars->map->scale.zoom_factor;
    calculate_scale(vars->map);
    parse_map(vars->points, vars->window_name, vars->map);
    apply_projection(vars->points, vars->map);
    move_map(vars->points, vars->map, 0, 0);
}

void iso_point(t_point *a, float angle)
{
    int prev_x;
    int prev_y;

    prev_x = a->x;
    prev_y = a->y;
    a->x = (prev_x - prev_y) * cos(angle);
    a->y = -a->z + (prev_x + prev_y) * sin(angle);
}

void    iso_points(t_vars *vars)
{
    if (vars->map->scale.zoom_factor == 0)
        vars->map->scale.zoom_factor = 1.1;
    vars->map->center.offset_x = 0;
    vars->map->center.offset_y = 0;
    apply_projection(vars->points, vars->map);
    move_map(vars->points, vars->map, 0, 0);
}