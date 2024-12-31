#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 800

typedef struct s_image {
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_image;

typedef struct s_vars {
    void *mlx;
    void *win;
    char *window_name;
    t_image img;
} t_vars;

void init_fdf(t_vars *vars)
{
    vars->mlx = mlx_init();
    vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, vars->window_name);
}

int close_window_esc(int keycode, t_vars *vars)
{
    if (keycode == 53)
    {
        mlx_destroy_window(vars->mlx, vars->win);
        free(vars->mlx);
        exit (0);
    }
    return (0);
}
int close_window_x(t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
    free(vars->mlx);
    exit(0);
    return 0;
}
void create_image (t_vars *vars)
{
    vars->img.img = mlx_new_image(vars->mlx, 700, 700);
    vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
}

void put_pixel(t_vars *vars, int x, int y, int color)
{
    char *dst;

    dst = vars->img.addr + (y * vars->img.line_length + x * (vars->img.bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int main(int argc, char **argv) {
    
    t_vars vars;
    char *window_name;

    vars.window_name = "window";
    
    init_fdf(&vars);
    mlx_hook(vars.win, 2, 1L<<0, close_window_esc, &vars);
    mlx_hook(vars.win, 17, 0, close_window_x, &vars);

    // image
    create_image(&vars);
    int i = 0;
    int j = 50;
    while (i < 100)
    {
        
       
        
            put_pixel(&vars, i, j, 0xff0000);
            j++;
       
        i = i + 2;
    }
    i = 50;
    j = 0;
     while (i < 150)
    {
        
       
        
            put_pixel(&vars, i, j, 0xff0000);
            j++;
       
        i = i + 2;
    }
    i = 50;
    j = 0;
    while (i >= 0)
    {
        
       
        
            put_pixel(&vars, i, j, 0xff0000);
            j++;
       
        i--;;
    }
    i = 150;
    j = 50;
     while (i >= 100)
    {
        
       
        
            put_pixel(&vars, i, j, 0xff0000);
            j++;
       
        i--;;
    }
    
    mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 50, 50);
    mlx_loop(vars.mlx);

    return EXIT_SUCCESS;
}

