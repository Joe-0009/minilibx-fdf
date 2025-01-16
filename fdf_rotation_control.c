/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotation_control.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:22:36 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/16 14:24:36 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_x_control(int keycode, float *angle, char *axis, t_vars *vars)
{
	if (keycode == KEY_W)
	{
		*axis = 'x';
		vars->current_rotation_angle = -*angle;
	}
	else if (keycode == KEY_S)
	{
		*axis = 'x';
		vars->current_rotation_angle = *angle;
	}
}

static void	set_y_control(int keycode, float *angle, char *axis, t_vars *vars)
{
	if (keycode == KEY_A)
	{
		*axis = 'y';
		vars->current_rotation_angle = -*angle;
	}
	else if (keycode == KEY_D)
	{
		*axis = 'y';
		vars->current_rotation_angle = *angle;
	}
}

static void	set_z_control(int keycode, float *angle, char *axis, t_vars *vars)
{
	if (keycode == KEY_Q)
	{
		*axis = 'z';
		vars->current_rotation_angle = -*angle;
	}
	else if (keycode == KEY_E)
	{
		*axis = 'z';
		vars->current_rotation_angle = *angle;
	}
}

void	determine_rotation_control(int keycode, t_vars *vars, float *angle,
		char *axis)
{
	*angle = 0.1;
	*axis = '\0';
	set_x_control(keycode, angle, axis, vars);
	set_y_control(keycode, angle, axis, vars);
	set_z_control(keycode, angle, axis, vars);
}

int	handle_rotation(int keycode, t_vars *vars)
{
	float	angle;
	char	axis;

	determine_rotation_control(keycode, vars, &angle, &axis);
	if (axis == '\0')
		return (0);
	vars->current_rotation_axis = axis;
	apply_rotation(vars, vars->current_rotation_angle,
		vars->current_rotation_axis);
	draw_new_image(vars);
	return (0);
}
