
#include "fdf.h"

static void rotate_x_axis(float *y, float *z, float angle)
{
    float temp;

    temp = *y;
    *y = temp * cos(angle) - *z * sin(angle);
    *z = temp * sin(angle) + *z * cos(angle);
}

static void rotate_y_axis(float *x, float *z, float angle)
{
    float temp;

    temp = *x;
    *x = temp * cos(angle) + *z * sin(angle);
    *z = -temp * sin(angle) + *z * cos(angle);
}

static void rotate_z_axis(float *x, float *y, float angle)
{
    float temp;

    temp = *x;
    *x = temp * cos(angle) - *y * sin(angle);
    *y = temp * sin(angle) + *y * cos(angle);
}

void rotate_point(t_point *point, float angle, char axis, t_bounds *bounds)
{
    float x;
    float y;
    float z;
    float center_x;
    float center_y;

    x = point->x;
    y = point->y;
    z = point->z;
    center_x = (bounds->max_x + bounds->min_x) / 2.0f;
    center_y = (bounds->max_y + bounds->min_y) / 2.0f;
    x = x - center_x;
    y = y - center_y;
    if (axis == 'x')
        rotate_x_axis(&y, &z, angle);
    else if (axis == 'y')
        rotate_y_axis(&x, &z, angle);
    else
        rotate_z_axis(&x, &y, angle);
    point->x = (int)(x + center_x);
    point->y = (int)(y + center_y);
    point->z = (int)z;
}

void apply_rotation(t_vars *vars, float angle, char axis)
{
    t_bounds bounds;
    int i, j;

    if (!vars->points || !vars->map)
        return;
    find_map_boundaries(vars->points, vars->map, &bounds);
    i = 0;
    while (i < vars->map->dim.height)
    {
        j = 0;
        while (j < vars->map->dim.width)
        {
            rotate_point(&vars->points[i][j], angle, axis, &bounds);
            j++;
        }
        i++;
    }
    move_map(vars->points, vars->map, 0, 0);
}
