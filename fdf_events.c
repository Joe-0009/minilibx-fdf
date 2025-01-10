/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:14:08 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/10 14:31:04 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void draw_new_image(t_vars *vars)
{
    cleanup_image(vars);
    create_image(vars);
    main_draw(vars);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}

int close_window_x(t_vars *vars)
{
    cleanup_image(vars);
    cleanup_window(vars);
    free_points(vars->map->dim.height, vars->points);
    exit(0);
    return (0);
}

int close_window_esc(int keycode, t_vars *vars)
{
    if (keycode == KEY_ESC)
    {
        cleanup_image(vars);
        cleanup_window(vars);
        free_points(vars->map->dim.height, vars->points);
        exit(0);
    }
    return (0);
}

int handle_movement(int keycode, t_vars *vars)
{
    static int total_offset_x = 0;
    static int total_offset_y = 0;

    if (keycode == KEY_UP) 
        total_offset_y -= 20;
    else if (keycode == KEY_DOWN) 
        total_offset_y += 20;
    else if (keycode == KEY_LEFT) 
        total_offset_x -= 20;
    else if (keycode == KEY_RIGHT) 
        total_offset_x += 20;
    else if (keycode == KEY_SPACE) 
    {
        total_offset_x = 0;
        total_offset_y = 0;
        vars->map->scale.zoom_factor = 1.1;
        vars->map->scale.projection = ISO;
        calculate_scale(vars->map);
        parse_map(vars->points, vars->window_name, vars->map);
        iso_points(vars);
    }
    else if (keycode == KEY_P) 
    {
        vars->map->scale.projection = (vars->map->scale.projection + 1) % 4;
        calculate_scale(vars->map);
        parse_map(vars->points, vars->window_name, vars->map);
        apply_projection(vars->points, vars->map);
    }
    if ((keycode >= 65361 && keycode <= 65364) || keycode == 32 || keycode == 112)
    {
        vars->map->center.offset_x = total_offset_x;
        vars->map->center.offset_y = total_offset_y;
        move_map(vars->points, vars->map, total_offset_x, total_offset_y);
        draw_new_image(vars);
    }
    return (0);
}

int zoom_in_and_out(int keycode, t_vars *vars)
{
    float zoom_factor;

    zoom_factor = 1.0;
    if (keycode == KEY_Z)
        zoom_factor = 1.1;
    else if (keycode == KEY_O)
        zoom_factor = 0.9;
    update_zoom(vars, zoom_factor);
    draw_new_image(vars);
    return (0);
}

int rotate(int keycode, t_vars *vars)
{
    float angle;

    angle = 0.1;
    if (keycode == KEY_W)  
        apply_rotation(vars, -angle, 'x');
    else if (keycode == KEY_S)
        apply_rotation(vars, angle, 'x');
    else if (keycode == KEY_A)  
        apply_rotation(vars, -angle, 'y');
    else if (keycode == KEY_D)  
        apply_rotation(vars, angle, 'y');
    else if (keycode == KEY_Q)  
        apply_rotation(vars, -angle, 'z');
    else if (keycode == KEY_E) 
        apply_rotation(vars, angle, 'z');
    if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A || 
        keycode == KEY_D || keycode == KEY_Q || keycode == KEY_E)
        draw_new_image(vars);
    return (0);
}

int key_handler(int keycode, t_vars *vars)
{
    if (keycode == KEY_ESC)
        close_window_esc(keycode, vars);
    else if ((keycode >= 65361 && keycode <= 65364) || keycode == 32 || keycode == 112)
        handle_movement(keycode, vars);
    else if (keycode == 122 || keycode == 111)
        zoom_in_and_out(keycode, vars);
    else if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A || 
             keycode == KEY_D || keycode == KEY_Q || keycode == KEY_E || keycode == KEY_I)
        rotate(keycode, vars);
    return (0);
}

void mlx_hooks(t_vars *vars, char *str)
{
    vars->window_name = str;
    mlx_hook(vars->win, 2, 1L << 0, key_handler, vars);
    mlx_hook(vars->win, 17, 0, close_window_x, vars);
}