#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <X11/X.h>
#include <stdlib.h>

# define HEIGHT 800
# define WIDTH  800


#define XK_Escape                        0xff1b



typedef struct s_image {
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
}   t_image;


typedef struct s_fdf
{
    char * name;
    void *mlx_connection;
    void *mlx_window; 
    t_image img;

}   t_fdf;

void fdf_init(t_fdf *fdf)
{
    fdf->mlx_connection = mlx_init();
    fdf->mlx_window = mlx_new_window(fdf->mlx_connection, WIDTH, HEIGHT, fdf->name);
}

void fdf_render(t_fdf *fdf)
{

}

int close_window_esc(int keycode, t_fdf *win)
{
    if (keycode == XK_Escape){
        mlx_destroy_window(win->mlx_connection, win->mlx_window);
        printf("esc pressed \n");
        exit(EXIT_SUCCESS);
    }
    printf("%d\n", keycode);
    return (EXIT_SUCCESS);
}
int close_window_x(t_fdf *win)
{
        mlx_destroy_window(win->mlx_connection, win->mlx_window);
        printf("x pressed\n");
        exit(EXIT_SUCCESS);
    return (EXIT_SUCCESS);
}

int main()
{
    t_fdf fdf;

    fdf.name = "window";
    fdf_init(&fdf);
    
    fdf_render(&fdf);

    mlx_loop(fdf.mlx_connection);

    return (0);
}
