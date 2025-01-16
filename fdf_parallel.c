/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parallel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:43:30 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/15 14:28:06 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	parallel_point_top(t_point *a)
{
	a->x = a->x;
	a->y = a->y;
}

void	parallel_point_front(t_point *a)
{
	a->x = a->x;
	a->y = -a->z;
}

void	parallel_point_side(t_point *a)
{
	a->x = -a->z;
	a->y = a->y;
}

void	project_point(t_point *a, t_map *map)
{
	if (map->scale.projection == PARALLEL_TOP)
		parallel_point_top(a);
	else if (map->scale.projection == PARALLEL_FRONT)
		parallel_point_front(a);
	else if (map->scale.projection == PARALLEL_SIDE)
		parallel_point_side(a);
}

void	apply_projection(t_vars *vars)
{
	int	i;
	int	j;

	if (!vars->points || !vars->map)
		return ;
	i = 0;
	while (i < vars->map->dim.height)
	{
		j = 0;
		while (j < vars->map->dim.width)
		{
			project_point(&vars->points[i][j], vars->map);
			j++;
		}
		i++;
	}
}
