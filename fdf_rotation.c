/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:54:05 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/16 18:08:54 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

static void	rotate_x_axis(float *y, float *z, float angle)
{
	float	temp;

	temp = *y;
	*y = temp * cos(angle) - *z * sin(angle);
	*z = temp * sin(angle) + *z * cos(angle);
}

static void	rotate_y_axis(float *x, float *z, float angle)
{
	float	temp;

	temp = *x;
	*x = temp * cos(angle) + *z * sin(angle);
	*z = -temp * sin(angle) + *z * cos(angle);
}

static void	rotate_z_axis(float *x, float *y, float angle)
{
	float	temp;

	temp = *x;
	*x = temp * cos(angle) - *y * sin(angle);
	*y = temp * sin(angle) + *y * cos(angle);
}

void	rotate_point(t_point *point, float angle, char axis)
{
	float	x;
	float	y;
	float	z;

	x = point->x;
	y = point->y;
	z = point->z;
	if (axis == 'x')
		rotate_x_axis(&y, &z, angle);
	else if (axis == 'y')
		rotate_y_axis(&x, &z, angle);
	else
		rotate_z_axis(&x, &y, angle);
	point->x = (x);
	point->y = (y);
	point->z = z;
}

void	apply_rotation(t_vars *vars, float angle, char axis)
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
			rotate_point(&vars->points[i][j], angle, axis);
			j++;
		}
		i++;
	}
	move_map(vars);
}
