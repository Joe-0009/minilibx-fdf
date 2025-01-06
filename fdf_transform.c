/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:15:41 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/06 14:17:29 by yrachidi         ###   ########.fr       */
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

void	iso_point(t_point *a, t_map *map)
{
	int	prev_x;
	int	prev_y;

	prev_x = a->x;
	prev_y = a->y;
	a->x = (prev_x - prev_y) * cos(map->scale.iso_angle);
	a->y = -a->z + (prev_x + prev_y) * sin(map->scale.iso_angle);
}

void	apply_iso_projection(t_point **points, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->dim.height)
	{
		j = 0;
		while (j < map->dim.width)
		{
			iso_point(&points[i][j], map);
			j++;
		}
		i++;
	}
}

void	center_map(t_point **points, t_map *map)
{
	int			i;
	int			j;
	t_bounds	bounds;
	int			center_x;
	int			center_y;

	find_map_boundaries(points, map, &bounds);
	center_x = (WIDTH - (bounds.max_x - bounds.min_x)) / 2;
	center_y = (HEIGHT - (bounds.max_y - bounds.min_y)) / 2;
	i = 0;
	while (i < map->dim.height)
	{
		j = 0;
		while (j < map->dim.width)
		{
			points[i][j].x += center_x - bounds.min_x;
			points[i][j].y += center_y - bounds.min_y;
			j++;
		}
		i++;
	}
}

void	iso_points(t_point **points, t_map *map)
{
	apply_iso_projection(points, map);
	center_map(points, map);
}
