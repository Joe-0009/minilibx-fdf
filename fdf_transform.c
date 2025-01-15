/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:15:41 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/14 23:48:01 by yrachidi         ###   ########.fr       */
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

void	move_map(t_point **points, t_map *map)
{
	int			i;
	int			j;
	t_bounds	bounds;

	find_map_boundaries(points, map, &bounds);
	map->center.x = (WIDTH - (bounds.max_x - bounds.min_x)) / 2;
	map->center.y = (HEIGHT - (bounds.max_y - bounds.min_y)) / 2;
	i = 0;
	while (i < map->dim.height)
	{
		j = 0;
		while (j < map->dim.width)
		{
			points[i][j].x += (map->center.x - bounds.min_x
					+ map->center.offset_x);
			points[i][j].y += (map->center.y - bounds.min_y
					+ map->center.offset_y);
			j++;
		}
		i++;
	}
}

void	update_zoom(t_vars *vars, float zoom_delta)
{
    t_bounds	bounds;
    int			i;
    int			j;
    float		new_zoom_factor;
    
    find_map_boundaries(vars->points, vars->map, &bounds);
    new_zoom_factor = vars->map->scale.zoom_factor * zoom_delta;
    if (new_zoom_factor < 0.1)
        new_zoom_factor = 0.1;
    if (new_zoom_factor > 10.0)
        new_zoom_factor = 10.0;
    float scale_factor = new_zoom_factor / vars->map->scale.zoom_factor;
    vars->map->scale.zoom_factor = new_zoom_factor;
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
    move_map(vars->points, vars->map);
}


void	iso_point(t_vars *vars)
{
	apply_rotation(vars, 0.785398, 'z');
	apply_rotation(vars, 0.95, 'x');
}
