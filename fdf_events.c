/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:14:08 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/15 13:01:18 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reset_shape(int keycode, t_vars *vars, int *total_offset_x,
		int *total_offset_y)
{
	if (keycode == KEY_SPACE)
	{
		*total_offset_x = 0;
		*total_offset_y = 0;
		vars->map->scale.zoom_factor = 1.1;
		calculate_scale(vars->map);
		parse_map(vars);
		iso_point(vars);
	}
}

void	change_projection(t_vars *vars)
{
	vars->map->scale.projection = (vars->map->scale.projection + 1) % 4;
	calculate_scale(vars->map);
	parse_map(vars);
	apply_projection(vars);
}

int	handle_movement(int keycode, t_vars *vars)
{
	static int	total_offset_x;
	static int	total_offset_y;

	if (keycode == KEY_UP)
		total_offset_y -= 20;
	else if (keycode == KEY_DOWN)
		total_offset_y += 20;
	else if (keycode == KEY_LEFT)
		total_offset_x -= 20;
	else if (keycode == KEY_RIGHT)
		total_offset_x += 20;
	else if (keycode == KEY_SPACE)
		reset_shape(keycode, vars, &total_offset_x, &total_offset_y);
	else if (keycode == KEY_P)
		change_projection(vars);
	if ((keycode >= KEY_LEFT && keycode <= KEY_DOWN) || keycode == KEY_SPACE
		|| keycode == KEY_P)
	{
		vars->map->center.offset_x = total_offset_x;
		vars->map->center.offset_y = total_offset_y;
		move_map(vars->points, vars->map);
		draw_new_image(vars);
	}
	return (0);
}

int	zoom_in_and_out(int keycode, t_vars *vars)
{
	float	zoom_factor;

	zoom_factor = 1.0;
	if (keycode == KEY_Z)
		zoom_factor = 1.1;
	else if (keycode == KEY_O)
		zoom_factor = 0.9;
	update_zoom(vars, zoom_factor);
	draw_new_image(vars);
	return (0);
}

int	rotate(int keycode, t_vars *vars)
{
	float	angle;
	char	axis;

	angle = 0.1;
	if (keycode == KEY_W || keycode == KEY_S)
	{
		axis = 'x';
		if (keycode == KEY_W)
			vars->current_rotation_angle = -angle;
		else
			vars->current_rotation_angle = angle;
	}
	else if (keycode == KEY_A || keycode == KEY_D)
	{
		axis = 'y';
		if (keycode == KEY_A)
			vars->current_rotation_angle = -angle;
		else
			vars->current_rotation_angle = angle;
	}
	else if (keycode == KEY_Q || keycode == KEY_E)
	{
		axis = 'z';
		if (keycode == KEY_Q)
			vars->current_rotation_angle = -angle;
		else
			vars->current_rotation_angle = angle;
	}
	else
		return (0);
	vars->current_rotation_axis = axis;
	apply_rotation(vars, vars->current_rotation_angle,
		vars->current_rotation_axis);
	draw_new_image(vars);
	return (0);
}
